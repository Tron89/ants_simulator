#pragma once
#include "../Food.hpp"
#include "../Pheromone.hpp"
#include "../Nest.hpp"
#include "../Rock.hpp"

struct AntCollider{
    
    static void onCollisionEnter(Ant &ant, Food &collision)
    {
        ant.vMovment = -ant.vMovment;
        while (std::sqrt(std::pow(ant.getPosition().x - collision.getPosition().x, 2) + std::pow(ant.getPosition().y - collision.getPosition().y, 2)) < (ant.getRadius() + collision.getRadius())){
            ant.move(ant.vMovment * config::dt);
        }
        ant.hasFood = true;
        ant.clock.restart();
        ant.setFillColor(sf::Color(0, 255, 0));
    }

    static void onCollisionEnter(Ant &ant, Rock &collision){
        ant.vMovment = -ant.vMovment;
        ant.move(ant.vMovment);
    }

    static void onCollisionEnter(Ant &ant, Nest &collision){
        ant.vMovment = -ant.vMovment;
        while (std::sqrt(std::pow(ant.getPosition().x - collision.getPosition().x, 2) + std::pow(ant.getPosition().y - collision.getPosition().y, 2)) < (ant.getRadius() + collision.getRadius())){
            ant.move(ant.vMovment * config::dt);
        }
        if(ant.hasFood){
            collision.foodCount ++;
            ant.hasFood = false;
            ant.clock.restart();
            ant.setFillColor(sf::Color(255, 255, 255));
        }
    }

    static void onCollisionEnter(Ant* ant, Ant* collision){
        ant->vMovment = -ant->vMovment;
        int preDestruction = 10;
        bool destruction = false;
        while (std::sqrt(std::pow(ant->getPosition().x - collision->getPosition().x, 2) + std::pow(ant->getPosition().y - collision->getPosition().y, 2)) < (ant->getRadius() + collision->getRadius()) || destruction){
            ant->move(ant->vMovment * config::dt);
            if (0 <= preDestruction){
                break;
            }
            preDestruction--;
        }
    }
};