#include <SFML/Graphics.hpp>
#include "./System.hpp"
#include "../Entity.hpp"
#include "../components/Position.hpp"
#include "../components/Movement.hpp"

#pragma once

// TODO: Burn this

/**
 * @brief Naaa, only for tests
 * 
 */
class Gravity : public System{
    public:
    void Update(std::vector<Entity*>& entities, float dt) {
        for (auto& entity : entities) {
            
            if (auto* movementComponent = entity->GetComponent<MovementComponent>()) {
                sf::Vector2f* movementV = &movementComponent->movementVector;
                movementV->y += 9.81;
            }
        }
    };
    virtual ~Gravity() = default;
};