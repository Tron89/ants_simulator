#include <iostream>
#include <SFML/Graphics.hpp>

#ifndef PHEROMONE_HPP
#define PHEROMONE_HPP


class Pheromone : public sf::CircleShape
{

    public:
    sf::Clock clock;
    sf::Time timeToDisappear;
    std::string type;
    bool disappear = false;
    float power;
    float startingPower;

    float radius;
    // searching or finded

    Pheromone(int x = 0, int y = 0, std::string type = "searching", float startingPower = 1, float radius = config::pheromoneRadius) : sf::CircleShape(radius){
        this->setPosition(x, y);
        timeToDisappear = sf::seconds(config::pheromoneTimeToDisappear);
        this->type = type;
        if (type == "searching"){
            this->setFillColor(sf::Color::Cyan);
        } else if (type == "finded"){
            this->setFillColor(sf::Color::Magenta);
        }

        this->radius = radius;
        this->startingPower = startingPower;
        
        timeToDisappear = timeToDisappear * startingPower;
    }

    bool operator==(const Pheromone &other) const {
        // Comparar todos los atributos relevantes
        return (this->getPosition() == other.getPosition());
    }
    void update(float dt)
    {
        power = ((timeToDisappear.asSeconds() - clock.getElapsedTime().asSeconds()) / timeToDisappear.asSeconds()) * startingPower;
        this->setRadius(radius * power);

        if (clock.getElapsedTime() >= timeToDisappear){
            disappear = true;
        }
    }

    // void onCollisionEnter(Ant &collision)
    // {

    // }
    private:
};

#endif // PHEROMONE_HPP

