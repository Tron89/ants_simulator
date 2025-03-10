#include <SFML/Graphics.hpp>
#include "./System.hpp"
#include "../Entity.hpp"
#include "../components/Transform.hpp"
#include "../components/Shape.hpp"

#pragma once

// TODO: changeit to draw other objects instead of circles

/**
 * @brief It draws the enititis using the window
 * 
 */
class Draw : public System{
    public:
    /**
     * @brief It draws the entities who have the position and circle shape components
     * 
     * @param entities The entities to draw
     * @param window The window to draw on
     */

    void Update(std::vector<Entity*>& entities, sf::RenderWindow& window) {
        for (auto& entity : entities) {
            auto* shapeComponent = entity->GetComponent<ShapeComponent>();
            auto* transform = entity->GetComponent<TransformComponent>();
            if (shapeComponent && transform){
                auto* shape = shapeComponent->getShape();
                
                shape->setPosition(transform->getPosition());
                shape->setRotation(transform->getRotation());
                shape->setScale(transform->getScale());

                window.draw(*shape);
            }
        }
    };
    virtual ~Draw() = default;
};