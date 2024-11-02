#include <iostream>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <cmath>

#include "../config.hpp"
#include "../math/Vectors.hpp"

#pragma once

class Pheromone;
class ant_collider;


class Ant : public sf::CircleShape
{
public:
    sf::Vector2f vMovment;
    bool hasFood = false;

    sf::Vector2f vRotation;
    sf::Vector2f vPheromones;
    sf::Vector2f vFood;
    sf::Vector2f vNest;

    sf::Clock clock;
    sf::Clock pheromoneClock;
    sf::Time timeToLost = sf::seconds(config::timeToLost);
    sf::Time timeToPheromone = sf::seconds(config::timeToCreatePheromone);
    std::vector<Pheromone*> &allPheromones;

    ant_collider collider();

    Ant(std::vector<Pheromone*> pheromones, int posX = 0, int posY = 0, float radius = config::antRadius) : sf::CircleShape(radius), allPheromones(pheromones)
    {
        this->setOrigin(sf::Vector2f(this->getRadius(), this->getRadius()));
        this->setPosition(posX, posY);

        this->vMovment.x = 0;
        this->vMovment.y = 0;
    }

private:

};

