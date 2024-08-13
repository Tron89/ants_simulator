#include <iostream>
#include <SFML/Graphics.hpp>
#include "Ant.hpp"

#ifndef FOOD_HPP
#define FOOD_HPP

class Food : public sf::CircleShape
{
    public:
    Food() : sf::CircleShape(){

    }

    void update(float dt)
    {

    }

    void onCollisionEnter(Ant &collision)
    {

    }
    private:
};

#endif // FOOD_HPP

