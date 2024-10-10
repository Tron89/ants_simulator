#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <iostream>

#include "config.hpp"

class Chunk :  public sf::RectangleShape
{
    public:
    std::vector<Ant*> content;

    Chunk(int posx = 0, int posy = 0, float size = config::chunkSize) : sf::RectangleShape(sf::Vector2f(size, size)){
        setPosition(posx, posy);
        setFillColor(sf::Color::Transparent);
        setOutlineThickness(0.5);
        setOutlineColor(config::chunkOutlineColor);
    }

    template <typename T>
    void add(T &object){
        content.push_back(&object);
    }
    std::vector<Ant*> getContent(){
        return content;
    }
    void clear(){
        content.clear();
    }

    private:

};