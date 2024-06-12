#include <iostream>
#include <SFML/Graphics.hpp>


class Tile
{

    public:
        sf::CircleShape oneTile;
        float side = 80;

        Tile() {
            
            float radius = side/1.4142;

            oneTile.setRadius(radius);
            oneTile.setPointCount(4);
            oneTile.setOrigin(radius, radius);
            oneTile.setPosition(100, 100);
            oneTile.rotate(45);
            oneTile.setFillColor(sf::Color::Blue);
        }

        sf::CircleShape& getTile(){
            return this->oneTile;
        }

};



