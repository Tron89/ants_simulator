#include <SFML/Graphics.hpp>
#include "./Component.hpp"

#pragma once

/**
 * @brief Storage the position, rotation and scale. The getters are for reference.
 * 
 */
 
class TransformComponent : public Component{
    public:

    TransformComponent(float posx = 0.f, float posy = 0.f, float rotation = 0.f, float scalex = 1.f, float scaley = 1.f) : 
    position(sf::Vector2f(posx, posy)),
    scale(sf::Vector2f(scalex, scaley)) {
        this->rotation = rotation;
    }

    void setPosition(sf::Vector2f& position) {
        this->position = position;
    }

    void setRotation(int degrees) {
        this->rotation = degrees;
    }

    void setScale(sf::Vector2f& scale) {
        this->scale = scale;
    }

    sf::Vector2f& getPosition() {
        return this->position;
    }

    float& getRotation() {
        return this->rotation;
    }

    sf::Vector2f& getScale() {
        return this->scale;
    }

    private:
        sf::Vector2f position;
        float rotation;
        sf::Vector2f scale;
};
