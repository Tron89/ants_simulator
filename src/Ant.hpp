#include <iostream>
#include <SFML/Graphics.hpp>
#include <random>
#include <chrono>
#include <cmath>

#ifndef ANT_HPP
#define ANT_HPP

#include "config.hpp"
#include "Pheromone.hpp"

class Rock;
class Food;
class Nest;

sf::Vector2f normalize(sf::Vector2f toNormalize){
    float x = toNormalize.x;
    float y = toNormalize.y;
    float magnitude = sqrt(pow(x, 2) + pow(y, 2));
    sf::Vector2f normalized(x/magnitude, y/magnitude);
    return normalized;
}

class Ant : public sf::CircleShape
{
public:
    sf::Vector2f vMovment;
    bool hasFood = false;
    sf::Vector2f vDesired;

    Ant(int x = 0, int y = 0, float radius = config::antRadius) : sf::CircleShape(radius)
    {
        this->setOrigin(sf::Vector2f(this->getRadius(), this->getRadius()));
        this->setPosition(x, y);
        // the movment vector, I have to create it like a part of the ant
        vMovment.x = 0;
        vMovment.y = 0;
    }

    void update(float dt, float rotate)
    {
        // change a litle bit randomly the rotation
        float rotation = this->getRotation();
        this->setRotation(rotation + rotate * config::antRotation * dt);

        vMovment.x = std::cos(rotation * 3.141592 / 180);
        vMovment.y = std::sin(rotation * 3.141592 / 180);

        // move the ant
        this->move(vMovment * dt * config::antSpeed);

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
    }

    // collisions action

    void onCollisionEnter(Food &collision)
    {
        this->setRotation(this->getRotation() + 180);
        this->hasFood = true;
        this->setFillColor(sf::Color(0, 255, 0));
    }

    void onCollisionEnter(Rock &collision){
        this->setRotation(this->getRotation() + 180);
    }

    void onCollisionEnter(Nest &collision){
    }

    // pheromones vector

    void GetVDesired(std::vector<Pheromone> &pheromones){
        if (pheromones.size() > 0){
            for (auto &pheromone : pheromones){
                sf::Vector2f antPosition = this->getPosition();
                sf::Vector2f pheromonePosition = pheromone.getPosition();

                sf::Vector2f vectorToPheromone = pheromonePosition - antPosition;
                vectorToPheromone = normalize(vectorToPheromone);
                
                std::cout << "Vector to pheromones: " << vectorToPheromone.x << " y "<< vectorToPheromone.y << std::endl;

                std::cout << "Vector movment: " << this->vMovment.x << " y "<< this->vMovment.y << std::endl;
                std::cout << "Rotation: " << this->getRotation() << std::endl;

                float dotProduct = this->vMovment.x * vectorToPheromone.x + this->vMovment.y * vectorToPheromone.y;
                
                std::cout << dotProduct << std::endl;

                if (dotProduct > 0){
                    this->vDesired = vectorToPheromone;
                }
            }
        }
    }



private:

};


#endif // ANT_HPP
