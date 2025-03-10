#include <SFML/Graphics.hpp>
#include "./Component.hpp"

#pragma once

// TODO: Maybe add the weight, angular drag...

/**
 * @brief Storage a movement vector
 * 
 */
class PhysicBodyComponent : public Component{
    public:
    void setMovement(int x, int y) {
        this->movementVector = sf::Vector2f(x, y);
    }

    sf::Vector2f& getMovement() {
        return this->movementVector;
    }

    private:
    sf::Vector2f movementVector = sf::Vector2f(0, 0);
};
