#include <SFML/Graphics.hpp>
#include <memory>
#include "./Component.hpp"

#pragma once

// TODO: maybe use a unic component for every shape?

/**
 * @brief A shape, circle, rectangle or some custom
 * 
 * @param type The shape type, it only uses their shape arguments
 * @param width The width of the rectangle or the radius of the circle
 * @param height The height of the rectangle
 */
class ShapeComponent : public Component{
    public:

    ShapeComponent(const std::string& type = "circle", float width = 0.f, float height = 0.f){
        if (type == "circle"){
            shape = std::make_unique<sf::CircleShape>(width);
            shape->setOrigin(width/2, width/2);
        } else if (type == "rectangle")
        {
            shape = std::make_unique<sf::RectangleShape>(sf::Vector2f(width, height));
        } else{
            throw std::invalid_argument("That's not a valid shape for the ShapeComponent");
        }
    }
    
    /**
     * @brief Get the Shape object
     * 
     * @return sf::Shape* (is a pointer because we don't know if is a rectangle, circle or other)
     */
    sf::Shape* getShape() {
        return shape.get();
    }

    private:
    std::unique_ptr<sf::Shape> shape;
};
