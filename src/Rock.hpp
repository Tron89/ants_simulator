#include <iostream>
#include <SFML/Graphics.hpp>


#ifndef ROCK_HPP
#define ROCK_HPP

#include "Ant.hpp"
#include "config.hpp"

class Rock : public sf::RectangleShape
{
    public:
    Rock(int posx = 0, int posy = 0, int x = config::rockSizeX, int y = config::rockSizeY) : sf::RectangleShape(sf::Vector2f(x, y)){
        this->setOrigin(x/2, y/2);
        this->setPosition(posx, posy);
        this->setFillColor(config::rockColor);

    }

    void update(float dt)
    {

    }

    void onCollisionEnter(Ant &collision)
    {

    }
    private:
};

#endif // ROCK_HPP

