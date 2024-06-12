#include <iostream>
#include <SFML/Graphics.hpp>
#include <random>
#include <chrono>
#include <cmath>

class Ant : public sf::CircleShape
{
public:
    sf::Vector2f vmovment;

    Ant(float x, float y, float radius = 1.f) : sf::CircleShape(radius)
    {
        this->setOrigin(sf::Vector2f(this->getRadius(), this->getRadius()));
        this->setPosition(x, y);
        // the movment vector, I have to create it like a part of the ant
        vmovment.x = 0;
        vmovment.y = 0;
    }

    void update(float dt, float rotate)
    {
        // change a litle bit randomly the rotation
        float rotation = this->getRotation();
        rotate += rotation;
        this->setRotation(rotate);

        vmovment.x = std::cos(rotation * 3.141592 / 180);
        vmovment.y = std::sin(rotation * 3.141592 / 180);

        // move the ant
        this->move(vmovment * dt * 50.f);

        // so they don't go off the screen
        if (this->getPosition().x >= 1500.f)
        {
            this->setPosition(0.f + this->getRadius(), getPosition().y);
        }
        if (this->getPosition().x <= 0.f)
        {
            this->setPosition(1000.f - this->getRadius(), getPosition().y);
        }
        if (this->getPosition().y >= 1000.f)
        {
            this->setPosition(getPosition().x, 0.f + this->getRadius());
        }
        if (this->getPosition().y <= 0.f)
        {
            this->setPosition(getPosition().x, 600.f - this->getRadius());
        }
    }

    // collision action
    void onCollisionEnter(auto collision)
    {
        this->setRotation(this->getRotation() + 180);
        this->setFillColor(sf::Color(255, 0, 0));
    }

private:
};