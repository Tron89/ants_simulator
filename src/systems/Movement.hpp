#include <SFML/Graphics.hpp>
#include "./System.hpp"
#include "../Entity.hpp"
#include "../components/Transform.hpp"
#include "../components/PhysicBody.hpp"
#include "../math/Vectors.hpp"
#include "../config.hpp"

#pragma once

class Movement : public System{
    public:
    void Update(std::vector<Entity*>& entities, float dt) {
        for (auto& entity : entities) {
            auto* transformComponent = entity->GetComponent<TransformComponent>();
            auto* physicBodyComponent = entity->GetComponent<PhysicBodyComponent>();
            if (transformComponent && physicBodyComponent) {
                sf::Vector2f* movementV = &physicBodyComponent->getMovement();
                sf::Vector2f* position = &transformComponent->getPosition();
                // *movementV = math::normalize(*movementV) * config::antSpeed;
                /*
                float max = 25;
                if(math::getMagnitude(*movementV)>max) {
                    *movementV = math::normalize(*movementV)*max;
                }
                */
                *position += (*movementV * dt);
                std::cout << position->x << " " << position->y << std::endl;
            }
        }
    };
    virtual ~Movement() = default;
};