#include <SFML/Graphics.hpp>
#include "./System.hpp"
#include "../Entity.hpp"
#include "../components/Position.hpp"
#include "../components/CircleShape.hpp"

#pragma once

class Draw : public System{
    public:
    void Update(std::vector<Entity*>& entities, sf::RenderWindow& window) {
        for (auto& entity : entities) {
            auto* circleShapeComponent = entity->GetComponent<CircleShapeComponent>();
            auto* positionComponent = entity->GetComponent<PositionComponent>();
            
            if (circleShapeComponent && positionComponent){
                    circleShapeComponent->shape.setPosition(positionComponent->position);
                    window.draw(circleShapeComponent->shape);

            }
        }
    };
    virtual ~Draw() = default;
};