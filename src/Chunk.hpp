#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <iostream>

#include "config.hpp"

class Chunk :  public sf::RectangleShape
{
    public:
    std::vector<sf::Shape*> content;

    Chunk(int posx = 0, int posy = 0, float size = config::chunkSize) : sf::RectangleShape(sf::Vector2f(size, size)){
        setPosition(posx, posy);
        setFillColor(sf::Color::Transparent);
        setOutlineThickness(0.5);
        setOutlineColor(config::chunkOutlineColor);
    }

    void add(sf::Shape* object){
        content.push_back(object);
    }
    std::vector<Shape*> getContent(){
        return content;
    }
    void clear(){
        content.clear();
    }

    private:

};