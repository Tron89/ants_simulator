#include <SFML/Graphics.hpp>
#include "./Component.hpp"

#pragma once


class CircleShapeComponent : public Component{
    public:
    sf::CircleShape shape;
    CircleShapeComponent(float radius = 1.f) : shape(radius){}

};
