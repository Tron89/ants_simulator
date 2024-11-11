#include <SFML/Graphics.hpp>
#include "./System.hpp"
#include "../Entity.hpp"
#include "../components/Position.hpp"

#pragma once

class Gravity : public System{
    public:
    void Update(std::vector<Entity*>& entities, float dt) {
        for (auto& entity : entities) {
            
            if (auto* positionComponent = entity->GetComponent<PositionComponent>()) {
                sf::Vector2f* position = &positionComponent->position;
                position->y += 1*dt;
                std::cout << position->x << " " << position->y << std::endl;
            }
        }
    };
    virtual ~Gravity() = default;
};