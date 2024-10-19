#include <iostream>
#include <SFML/Graphics.hpp>
#include <chrono>

#include "config.hpp"
#include "math/Vectors.hpp"

#pragma once

class Collisions
{
public:

static void getColision(sf::Shape &collision1, sf::Shape &collision2){

    // Get vertices
    std::vector<sf::Vector2f> points1;
    for (size_t i = 0; i < collision1.getPointCount(); i++)
    {
        // FIXME: This will not allow the resize

        // How the "collision1.getPoint(i)" it give the local position of the point(without the position, rotation, or size)
        // I have to get the global position

        sf::Vector2f localPoint = collision1.getPoint(i);
        sf::Vector2f globalPosition = collision1.getPosition();
        sf::Vector2f origin = collision1.getOrigin();
        float rotation = collision1.getRotation();

        sf::Vector2f fromCenterPosition = localPoint - origin;
        sf::Vector2f fromCenterPositionNormalized = math::normalize(fromCenterPosition);
        float pointAngle = atan2(-fromCenterPositionNormalized.y, fromCenterPositionNormalized.x) * 180 / M_PI;

        float pointAngelObjetive = pointAngle + rotation;

        float magnitude = math::getMagnitude(fromCenterPosition);
        sf::Vector2f fromCenterPointRotated(cos(pointAngelObjetive * (M_PI / 180.0)) * magnitude, -sin(pointAngelObjetive * (M_PI / 180.0)) * magnitude);


        sf::Vector2f pointRotated(fromCenterPointRotated.x + origin.x, fromCenterPointRotated.y + origin.y);

        points1.push_back(pointRotated + (globalPosition - origin));
    }

    std::vector<sf::Vector2f> points2;
    for (size_t i = 0; i < collision2.getPointCount(); i++)
    {
        // FIXME: This will not allow the resize

        // How the "collision1.getPoint(i)" it give the local position of the point(without the position, rotation, or size)
        // I have to get the global position

        sf::Vector2f localPoint = collision2.getPoint(i);
        sf::Vector2f globalPosition = collision2.getPosition();
        sf::Vector2f origin = collision2.getOrigin();
        float rotation = collision2.getRotation();

        sf::Vector2f fromCenterPosition = localPoint - origin;
        sf::Vector2f fromCenterPositionNormalized = math::normalize(fromCenterPosition);
        float pointAngle = atan2(-fromCenterPositionNormalized.y, fromCenterPositionNormalized.x) * 180 / M_PI;

        float pointAngelObjetive = pointAngle + rotation;

        float magnitude = math::getMagnitude(fromCenterPosition);
        sf::Vector2f fromCenterPointRotated(cos(pointAngelObjetive * (M_PI / 180.0)) * magnitude, -sin(pointAngelObjetive * (M_PI / 180.0)) * magnitude);


        sf::Vector2f pointRotated(fromCenterPointRotated.x + origin.x, fromCenterPointRotated.y + origin.y);

        points2.push_back(pointRotated + (globalPosition - origin));
    }

    //
    // Get the separatingAxises
    //

    // Get side
    std::vector<sf::Vector2f> sides1;
    for (size_t i = 0; i < collision1.getPointCount(); i++)
    {
        if (i+1 < collision1.getPointCount())
        {
            sf::Vector2f side = points1[i] - points1[i+1];
            sides1.push_back(side);
        } else{
            sf::Vector2f side = points1[i] - points1[0];
            sides1.push_back(side);
        }
    }


    std::vector<sf::Vector2f> sides2;
    for (size_t i = 0; i < collision2.getPointCount(); i++)
    {
        if (i+1 < collision2.getPointCount())
        {
            sf::Vector2f side = points2[i] - points2[i+1];
            sides1.push_back(side);
        } else{
            sf::Vector2f side = points2[i] - points2[0];
            sides1.push_back(side);
        }
    }

    // Get the normals

    std::vector<sf::Vector2f> normals1;
    for (auto side : sides1)
    {
        sf::Vector2f normal(-side.y, side.x);
        normals1.push_back(math::normalize(normal));
    }

    std::vector<sf::Vector2f> normals2;
    for (auto side : sides2)
    {
        sf::Vector2f normal(-side.y, side.x);
        normals2.push_back(math::normalize(normal));
    }

    // Discount the duplicated


    // Get the separating axis?
    std::vector<sf::Vector2f> separatingAxises1;
    for (auto normal : normals1)
    {
        sf::Vector2f separatingAxis(-normal.y, normal.x);
        separatingAxises1.push_back(normal);
    }
    
    std::vector<sf::Vector2f> separatingAxises2;
    for (auto normal : normals2)
    {
        sf::Vector2f separatingAxis(-normal.y, normal.x);
        separatingAxises2.push_back(normal);
    }

    //
    // First AABB colision sistem
    //

    float minx1 = INT64_MAX;
    float miny1 = INT64_MAX;
    float maxx1 = INT64_MIN;
    float maxy1 = INT64_MIN;
    for (auto point : points1){
        /*
    std::cout << " ----------- " << std::endl;
    std::cout << point.x << std::endl;
    std::cout << point.y << std::endl;
*/
        if (point.x < minx1)
        {
            minx1 = point.x;
        }
        if (point.x > maxx1)
        {
            maxx1 = point.x;
        }
        if (point.y < miny1)
        {
            miny1 = point.y;
        }
        if (point.y > maxy1)
        {
            maxy1 = point.y;
        }
    }


    float minx2 = INT64_MAX;
    float miny2 = INT64_MAX;
    float maxx2 = INT64_MIN;
    float maxy2 = INT64_MIN;
    for (auto point : points2){
        if (point.x < minx2)
        {
            minx2 = point.x;
        }
        if (point.x > maxx2)
        {
            maxx2 = point.x;
        }
        if (point.y < miny2)
        {
            miny2 = point.y;
        }
        if (point.y > maxy2)
        {
            maxy2 = point.y;
        }
    }

    bool collisionx = false;
    bool collisiony = false;

    if (minx1 < maxx2 && maxx1 > minx2)
    {
        collisionx = true;
    }
    if (miny1 < maxy2 && maxy1 > miny2)
    {
        collisiony = true;
    }
    if (collisionx && collisiony) {std::cout << "Collision :)" << std::endl;}

    // It works :'D (I been here for 3 hours fighting with sines and cosines, I'wanna die)
    // Now it's nesesary that I do it with the separating axis, and for that I need to change the points to
    // too the separating axis world, and for that is the dot product, 
    // A = point to discover
    // B = normalized vector of separating axis
    // k = A*B
    // k = relative x from the normalized vector
    // other remember for me: I have it in geogebra

}

private:

};

