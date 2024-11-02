#include <random>
#pragma once
#include "../Food.hpp"
#include "../Pheromone.hpp"
#include "../Nest.hpp"

struct AntUpdater{
    
    static void update(Ant &ant, float rotate)
    {
        GetVMovment(ant, rotate);

        ant.move(ant.vMovment * config::dt);

        StayInScreen(ant);

        // CheckPheromones(ant);
    }

    static void GetVMovment(Ant &ant, float rotate){
        float rotation = rotate * 180;

        ant.vRotation.x = std::cos(rotation * 3.141592 / 180);
        ant.vRotation.y = std::sin(rotation * 3.141592 / 180);

        ant.vMovment = ant.vMovment * config::movmentWeight + ant.vPheromones * config::pheromonesWeight + ant.vRotation * config::rotationWeight + ant.vFood * config::foodWeight + ant.vNest * config::nestsWeight;
        
        if (math::getMagnitude(ant.vMovment) >= config::antSpeed){
            ant.vMovment = math::normalize(ant.vMovment) * config::antSpeed;
        }

        ant.vPheromones = sf::Vector2f(0,0);
        ant.vFood = sf::Vector2f(0,0);
        ant.vNest = sf::Vector2f(0,0);
    }

    static void CheckPheromones(Ant &ant){
        if (ant.pheromoneClock.getElapsedTime() >= ant.timeToPheromone){
            ant.pheromoneClock.restart();

            std::string type;
            if (ant.hasFood) {
                type = "finded";
            } else {
                type = "searching";
            }

            float power = (ant.timeToLost.asSeconds() - ant.clock.getElapsedTime().asSeconds()) / ant.timeToLost.asSeconds();
            if (power > 0){
                ant.allPheromones.push_back(new Pheromone(ant.getPosition().x, ant.getPosition().y, type, power));
            }
        }
    }

    static void StayInScreen(Ant &ant){
        if (ant.getPosition().x >= config::screenX)
        {
            ant.setPosition(0.f + ant.getRadius(), ant.getPosition().y);
        }
        if (ant.getPosition().x <= 0.f)
        {
            ant.setPosition(config::screenX - ant.getRadius(), ant.getPosition().y);
        }
        if (ant.getPosition().y >= config::screenY)
        {
            ant.setPosition(ant.getPosition().x, 0.f + ant.getRadius());
        }
        if (ant.getPosition().y <= 0.f)
        {
            ant.setPosition(ant.getPosition().x, config::screenY - ant.getRadius());
        }
    }

    static void GetVPheromones(Ant &ant, std::vector<Pheromone> &pheromones){
        
        if (pheromones.size() > 0){
            sf::Vector2f vNormal;
            for (auto &pheromone : pheromones){
                
                sf::Vector2f vectorToPheromone = math::normalize(pheromone.getPosition() - ant.getPosition());

                sf::Vector2f vMovmentNormalized = math::normalize(ant.vMovment);

                float dotProduct = vMovmentNormalized.x * vectorToPheromone.x + vMovmentNormalized.y * vectorToPheromone.y;
                if (dotProduct > 0){
                    vNormal = vNormal + vectorToPheromone;
                } else if (dotProduct <= 0){
                    vNormal = vNormal + vectorToPheromone * 0.1f;
                }
                
            }
            if (vNormal != sf::Vector2f(0,0)){
                ant.vPheromones = math::normalize(vNormal);
            }
        }
    }

    static void GetVFood(Ant &ant, std::vector<Food> &foods){
        
        if (foods.size() > 0){
            sf::Vector2f vNormal;
            for (auto &food : foods){
                
                sf::Vector2f vectorToFood = math::normalize(food.getPosition() - ant.getPosition());

                float dotProduct = ant.vMovment.x * vectorToFood.x + ant.vMovment.y * vectorToFood.y;
                
                vNormal = vNormal + vectorToFood;
            }
            ant.vFood = math::normalize(vNormal);
        }
    }

    static void GetVNests(Ant &ant, std::vector<Nest> &nests){
        
        if (nests.size() > 0){
            sf::Vector2f vNormal;
            for (auto &nest : nests){
                
                sf::Vector2f vectorToNests = math::normalize(nest.getPosition() - ant.getPosition());

                float dotProduct = ant.vMovment.x * vectorToNests.x + ant.vMovment.y * vectorToNests.y;
                
                vNormal = vNormal + vectorToNests;
            }
            ant.vNest = math::normalize(vNormal);
        }
    }

};
