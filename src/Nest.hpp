#include <iostream>
#include <SFML/Graphics.hpp>

#pragma once

#include "ant/Ant.hpp"

class Nest : public sf::CircleShape
{
    public:
    int foodCount = 0;
    Nest(int posx = 0, int posy = 0, int radius = config::nestRadius) : sf::CircleShape(radius){
        this->setOrigin(radius, radius);
        this->setPosition(posx, posy);
        this->setFillColor(config::nestColor);
    }

    void update(float dt)
    {

    }

    void onCollisionEnter(Ant &collision)
    {
        if (collision.hasFood){
            collision.hasFood = false;
            foodCount ++;
            collision.setFillColor(sf::Color(255, 255, 255));
        }
    }
    private:
};

