#include <iostream>
#include <SFML/Graphics.hpp>
#include <random>
#include <chrono>
#include <cmath>
#include "config.hpp"

class Ant : public sf::CircleShape
{
public:
    sf::Vector2f vMovment;

    Ant(float x = 0.f, float y = 0.f, float radius = config::antRadius) : sf::CircleShape(radius)
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
        this->setRotation(rotation + rotate * config::antRotation);

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

    // ant
    void onCollisionEnter(Ant &collision)
    {

    }

    // a rectangle
    void onCollisionEnter(sf::RectangleShape &collision){
        this->setRotation(this->getRotation() + 180);
        this->setFillColor(sf::Color(255, 0, 0));
    }


private:
};