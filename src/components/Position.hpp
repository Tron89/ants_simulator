#include <SFML/Graphics.hpp>
#include "./Component.hpp"

#pragma once

class PositionComponent : public Component{
    public:
    sf::Vector2f position = sf::Vector2f(0, 0);
};
