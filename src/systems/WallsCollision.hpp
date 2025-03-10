#include <SFML/Graphics.hpp>
#include "./System.hpp"
#include "../Entity.hpp"
#include "../components/Position.hpp"
#include "../components/Movement.hpp"
#include "../config.hpp"

#pragma once

// TODO: In proces

/**
 * @brief In proces
 * 
 */
class WallsCollision : public System{
    public:
    void Update(std::vector<Entity*>& entities, float dt) {
        
        for (auto& entity : entities) {
            auto* positionComponent = entity->GetComponent<PositionComponent>();
            auto* movementComponent = entity->GetComponent<MovementComponent>();

            if (positionComponent && movementComponent) {
                sf::Vector2f* position = &positionComponent->position;
                sf::Vector2f* movementV = &movementComponent->movementVector;
                if(position->x<0) {
                    *movementV = sf::Vector2f(-movementV->x, movementV->y);
                    *position = sf::Vector2f(0, position->y);
                }
                if(position->y<0) {
                    *movementV = sf::Vector2f(movementV->x, -movementV->y);
                    *position = sf::Vector2f(position->x, 0);
                }
                if(position->x>config::screenX) {
                    *movementV = sf::Vector2f(-movementV->x, movementV->y);
                    *position = sf::Vector2f(config::screenX, position->y);
                }
                if(position->y>config::screenY) {
                    *movementV = sf::Vector2f(movementV->x, -movementV->y);
                    *position = sf::Vector2f(position->x, config::screenY);
                }
            }
        }
    };
    virtual ~WallsCollision() = default;
};