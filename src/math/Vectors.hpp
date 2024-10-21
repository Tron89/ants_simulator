#include <SFML/Graphics.hpp>
#include <cmath>
#pragma once
namespace math
{
    sf::Vector2f normalize(sf::Vector2f toNormalize){
        float x = toNormalize.x;
        float y = toNormalize.y;
        float magnitude = sqrt(pow(x, 2) + pow(y, 2));
        sf::Vector2f normalized(x/magnitude, y/magnitude);
        return normalized;
    }

    float getMagnitude(sf::Vector2f toMagnitude){
        float x = toMagnitude.x;
        float y = toMagnitude.y;
        float magnitude = sqrt(pow(x, 2) + pow(y, 2));
        return magnitude;
    }

    float dotProduct(sf::Vector2f a, sf::Vector2f b){
        float r = a.x*b.x+a.y*b.y;
        return r;
    }
}