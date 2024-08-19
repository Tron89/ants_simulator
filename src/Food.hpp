#include <iostream>
#include <SFML/Graphics.hpp>

#ifndef FOOD_HPP
#define FOOD_HPP


class Food : public sf::CircleShape
{
    public:
    Food(int posx = 0, int posy = 0, int radius = config::foodRadius) : sf::CircleShape(radius){
        this->setOrigin(radius, radius);
        this->setPosition(posx, posy);
        this->setFillColor(config::foodColor);
    }

    void update(float dt)
    {

    }

    // void onCollisionEnter(Ant &collision)
    // {

    // }
    private:
};

#endif // FOOD_HPP

