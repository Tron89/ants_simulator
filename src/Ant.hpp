#include <iostream>
#include <SFML/Graphics.hpp>
#include <random>
#include <chrono>
#include <cmath>

#ifndef ANT_HPP
#define ANT_HPP

#include "config.hpp"
#include "Food.hpp"
#include "Pheromone.hpp"
#include "Nest.hpp"

class Rock;

sf::Vector2f normalize(sf::Vector2f toNormalize){
    float x = toNormalize.x;
    float y = toNormalize.y;
    float magnitude = sqrt(pow(x, 2) + pow(y, 2));
    sf::Vector2f normalized(x/magnitude, y/magnitude);
    return normalized;
}

float getMagnitude(sf::Vector2f toMagnitude){
    float x = toMagnitude.x;
    float y = toMagnitude.y;
    float magnitude = sqrt(pow(x, 2) + pow(y, 2));
    return magnitude;
}

class Ant : public sf::CircleShape
{
public:
    sf::Vector2f vMovment;
    sf::Vector2f vRotation;
    bool hasFood = false;
    sf::Vector2f vPheromones;
    sf::Vector2f vFood;
    sf::Vector2f vNest;

    sf::Clock clock;
    sf::Clock pheromoneClock;
    sf::Time timeToLost;
    sf::Time timeToPheromone;
    std::vector<Pheromone>& allPheromones;

    float dt;

    Ant(std::vector<Pheromone>& pheromones, int x = 0, int y = 0, float radius = config::antRadius) : sf::CircleShape(radius), allPheromones(pheromones)
    {
        this->setOrigin(sf::Vector2f(this->getRadius(), this->getRadius()));
        this->setPosition(x, y);
        // the movment vector, I have to create it like a part of the ant
        vMovment.x = 0;
        vMovment.y = 0;

        timeToLost = sf::seconds(config::timeToLost);

        timeToPheromone = sf::seconds(config::timeToCreatePheromone);
    }

    void update(float dt, float rotate)
    {
        // change a litle bit randomly the rotation

        // float rotation = this->getRotation();
        // this->setRotation(rotation + rotate * config::antRotation * dt);

        // vMovment.x = std::cos(rotation * 3.141592 / 180);
        // vMovment.y = std::sin(rotation * 3.141592 / 180);

        // this->setRotation(rotation + rotate * config::antRotation * dt);

        this->dt = dt;

        float rotation = rotate * 180;

        vRotation.x = std::cos(rotation * 3.141592 / 180);
        vRotation.y = std::sin(rotation * 3.141592 / 180);

        vMovment = vMovment * config::movmentWeight + vPheromones * config::pheromonesWeight + vRotation * config::rotationWeight + vFood * config::foodWeight + vNest * config::nestsWeight;
        
        if (getMagnitude(vMovment) >= config::antSpeed){
            vMovment = normalize(vMovment) * config::antSpeed;
        }

        // move the ant
        this->move(vMovment * dt);

        // so they don't go off the screen
        if (this->getPosition().x >= config::screenX)
        {
            this->setPosition(0.f + this->getRadius(), getPosition().y);
        }
        if (this->getPosition().x <= 0.f)
        {
            this->setPosition(config::screenX - this->getRadius(), getPosition().y);
        }
        if (this->getPosition().y >= config::screenY)
        {
            this->setPosition(getPosition().x, 0.f + this->getRadius());
        }
        if (this->getPosition().y <= 0.f)
        {
            this->setPosition(getPosition().x, config::screenY - this->getRadius());
        }

        if (pheromoneClock.getElapsedTime() >= timeToPheromone){
            pheromoneClock.restart();

            std::string type;
            if (this->hasFood) {
                type = "finded";
            } else {
                type = "searching";
            }

            float power = (timeToLost.asSeconds() - clock.getElapsedTime().asSeconds()) / timeToLost.asSeconds();
            if (power > 0){
                Pheromone pheromone(this->getPosition().x, this->getPosition().y, type, power);
                allPheromones.push_back(pheromone);
            }
        }
        this->vPheromones = sf::Vector2f(0,0);
        this->vFood = sf::Vector2f(0,0);
        this->vNest = sf::Vector2f(0,0);
    }

    // collisions action

    void onCollisionEnter(Food &collision)
    {
        this->vMovment = -this->vMovment;
        while (std::sqrt(std::pow(this->getPosition().x - collision.getPosition().x, 2) + std::pow(this->getPosition().y - collision.getPosition().y, 2)) < (this->getRadius() + collision.getRadius())){
            this->move(vMovment * this->dt);
        }
        this->hasFood = true;
        clock.restart();
        this->setFillColor(sf::Color(0, 255, 0));
    }

    void onCollisionEnter(Rock &collision){
        this->vMovment = -this->vMovment;
        this->move(vMovment);
    }

    void onCollisionEnter(Nest &collision){
        this->vMovment = -this->vMovment;
        while (std::sqrt(std::pow(this->getPosition().x - collision.getPosition().x, 2) + std::pow(this->getPosition().y - collision.getPosition().y, 2)) < (this->getRadius() + collision.getRadius())){
            this->move(vMovment * this->dt);
        }
        if(hasFood){
            collision.foodCount ++;
            this->hasFood = false;
            clock.restart();
            this->setFillColor(sf::Color(255, 255, 255));
        }
        
    }

    // pheromones vector
    

    void GetVPheromones(std::vector<Pheromone> &pheromones){
        
        if (pheromones.size() > 0){
            sf::Vector2f vNormal;
            for (auto &pheromone : pheromones){
                
                sf::Vector2f vectorToPheromone = normalize(pheromone.getPosition() - this->getPosition());

                sf::Vector2f vMovmentNormalized = normalize(vMovment);

                float dotProduct = vMovmentNormalized.x * vectorToPheromone.x + vMovmentNormalized.y * vectorToPheromone.y;
                if (dotProduct > 0){
                    vNormal = vNormal + vectorToPheromone;
                } else if (dotProduct <= 0){
                    vNormal = vNormal + vectorToPheromone * 0.5f;
                }
                
            }
            if (vNormal != sf::Vector2f(0,0)){
                this->vPheromones = normalize(vNormal);
            }
        }
    }

    void GetVFood(std::vector<Food> &foods){
        
        if (foods.size() > 0){
            sf::Vector2f vNormal;
            for (auto &food : foods){
                
                sf::Vector2f vectorToFood = normalize(food.getPosition() - this->getPosition());

                float dotProduct = this->vMovment.x * vectorToFood.x + this->vMovment.y * vectorToFood.y;
                
                vNormal = vNormal + vectorToFood;
            }
            this->vFood = normalize(vNormal);
        }
    }

    void GetVNests(std::vector<Nest> &nests){
        
        if (nests.size() > 0){
            sf::Vector2f vNormal;
            for (auto &nest : nests){
                
                sf::Vector2f vectorToNests = normalize(nest.getPosition() - this->getPosition());

                float dotProduct = this->vMovment.x * vectorToNests.x + this->vMovment.y * vectorToNests.y;
                
                vNormal = vNormal + vectorToNests;
            }
            this->vNest = normalize(vNormal);
        }
    }



private:

};


#endif // ANT_HPP
