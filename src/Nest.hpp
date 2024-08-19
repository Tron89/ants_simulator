#include <iostream>
#include <SFML/Graphics.hpp>
#include "Ant.hpp"

#ifndef NEST_HPP
#define NEST_HPP

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

    // void onCollisionEnter(Ant &collision)
    // {
    //     if (collision.hasFood){
    //         collision.hasFood = false;
    //         foodCount ++;
    //         collision.setFillColor(sf::Color(255, 255, 255));
    //     }
    // }
    private:
};

#endif // NEST_HPP

