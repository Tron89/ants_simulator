#include <SFML/Graphics.hpp>
#include "./Component.hpp"

class MovementComponent : public Component{
    public:
    sf::Vector2f movementVector;
};
