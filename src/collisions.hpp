#include <iostream>
#include <SFML/Graphics.hpp>
#include <chrono>

#include "config.hpp"
#include "math/Vectors.hpp"

#pragma once

class Collisions
{
public:

static void getCollision(sf::Shape &collision1, sf::Shape &collision2){

    // Get vertices
    std::vector<sf::Vector2f> vertices1 = getVertices(collision1);
    std::vector<sf::Vector2f> vertices2 = getVertices(collision2);

    //
    // Get the separatingAxises
    //
    std::vector<sf::Vector2f> sides1 = getSides(collision1, vertices1);
    std::vector<sf::Vector2f> sides2 = getSides(collision2, vertices2);

    std::vector<sf::Vector2f> normals1 = getNormals(sides1);
    std::vector<sf::Vector2f> normals2 = getNormals(sides2);


    // TODO: Discount the duplicated
    std::vector<sf::Vector2f> separatingAxises1 = getSeparatingAxises(normals1);
    std::vector<sf::Vector2f> separatingAxises2 = getSeparatingAxises(normals2);

    //
    // First AABB colision sistem
    //
    
    // Get the max and min vertices from that perspective
    std::array<int, 4> points = getMaxMinVertices(vertices1);
    float minx1 = points[0];
    float miny1 = points[1];
    float maxx1 = points[2];
    float maxy1 = points[3];

    std::array<int, 4> points = getMaxMinVertices(vertices2);
    float minx2 = points[0];
    float miny2 = points[1];
    float maxx2 = points[2];
    float maxy2 = points[3];

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

    static std::vector<sf::Vector2f> getVertices(sf::Shape &collision){
        std::vector<sf::Vector2f> vertices;
        for (size_t i = 0; i < collision.getPointCount(); i++)
            {
                // FIXME: This will not allow the resize

                // How the "collision.getPoint(i)" it give the local position of the point(without the position, rotation, or size)
                // I have to get the global position

                sf::Vector2f localPoint = collision.getPoint(i);
                sf::Vector2f globalPosition = collision.getPosition();
                sf::Vector2f origin = collision.getOrigin();
                float rotation = collision.getRotation();

                sf::Vector2f fromCenterPosition = localPoint - origin;
                sf::Vector2f fromCenterPositionNormalized = math::normalize(fromCenterPosition);
                float pointAngle = atan2(-fromCenterPositionNormalized.y, fromCenterPositionNormalized.x) * 180 / M_PI;

                float pointAngelObjetive = pointAngle + rotation;

                float magnitude = math::getMagnitude(fromCenterPosition);
                sf::Vector2f fromCenterPointRotated(cos(pointAngelObjetive * (M_PI / 180.0)) * magnitude, -sin(pointAngelObjetive * (M_PI / 180.0)) * magnitude);


                sf::Vector2f pointRotated(fromCenterPointRotated.x + origin.x, fromCenterPointRotated.y + origin.y);

                vertices.push_back(pointRotated + (globalPosition - origin));
            }
        return vertices;
    }

    static std::vector<sf::Vector2f> getSides(sf::Shape &collision, std::vector<sf::Vector2f> vertices){
        std::vector<sf::Vector2f> sides;
        for (size_t i = 0; i < collision.getPointCount(); i++)
        {
            if (i+1 < collision.getPointCount())
            {
                sf::Vector2f side = vertices[i] - vertices[i+1];
                sides.push_back(side);
            } else{
                sf::Vector2f side = vertices[i] - vertices[0];
                sides.push_back(side);
            }
        }
        return sides;
    }

    static std::vector<sf::Vector2f> getNormals(std::vector<sf::Vector2f> sides){
        std::vector<sf::Vector2f> normals;
        for (auto side : sides)
        {
            sf::Vector2f normal(-side.y, side.x);
            normals.push_back(math::normalize(normal));
        }
        return normals;
    }

    static std::vector<sf::Vector2f> getSeparatingAxises(std::vector<sf::Vector2f> normals){
        std::vector<sf::Vector2f> separatingAxises;
        for (auto normal : normals)
        {
            sf::Vector2f separatingAxis(-normal.y, normal.x);
            separatingAxises.push_back(normal);
        }
    }

    static std::array<int, 4> getMaxMinVertices(std::vector<sf::Vector2f> vertices){

        float minx = INT64_MAX;
        float miny = INT64_MAX;
        float maxx = INT64_MIN;
        float maxy = INT64_MIN;

        for (auto point : vertices){

        if (point.x < minx)
        {
            minx = point.x;
        }
        if (point.x > maxx)
        {
            maxx = point.x;
        }
        if (point.y < miny)
        {
            miny = point.y;
        }
        if (point.y > maxy)
        {
            maxy = point.y;
        }
        }
        return {minx, miny, maxx, maxy};
    }


};

