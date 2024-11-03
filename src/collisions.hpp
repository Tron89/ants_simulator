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

    /*
    if (AABBcollision(collision1, collision2)){
        std::cout << "AABB Collision detected" << std::endl;
    }
    */
    if (SATcollision(collision1, collision2)){
        std::cout << "SAT Collision detected" << std::endl;
    }
}


    // Apply the SAT (Separating Axis Theorem) 
    static bool SATcollision(sf::Shape &collision1, sf::Shape &collision2){

        // Get vertices
        std::vector<sf::Vector2f> vertices1 = getVertices(collision1);
        std::vector<sf::Vector2f> vertices2 = getVertices(collision2);

        // Get the separatingAxises
        std::vector<sf::Vector2f> sides1 = getSides(collision1, vertices1);
        std::vector<sf::Vector2f> sides2 = getSides(collision2, vertices2);

        std::vector<sf::Vector2f> separatingAxises;

        // If one is a circle, the separating axis will be the line between the centers of the two shapes
        if(dynamic_cast<sf::CircleShape*>(&collision1) || dynamic_cast<sf::CircleShape*>(&collision2)){
            // FIXME: this is asuming that the origin is the center
            separatingAxises.push_back(math::normalize(collision1.getPosition() - collision2.getPosition()));
        } else{
            std::vector<sf::Vector2f> normals1 = getNormals(sides1);
            std::vector<sf::Vector2f> normals2 = getNormals(sides2);

            std::vector<sf::Vector2f> normals = joinNormals(normals1, normals2);

            separatingAxises = getSeparatingAxises(normals);
        }




        for(auto separatingAxis : separatingAxises){

            // Get the max and min vertices from the x axis of that perspective
            std::array<float, 2> points1 = getMinMaxRelativeVectors(vertices1, separatingAxis);
            float minx1 = points1[0];
            float maxx1 = points1[1];

            std::array<float, 2> points2 = getMinMaxRelativeVectors(vertices2, separatingAxis);
            float minx2 = points2[0];
            float maxx2 = points2[1];

            if (minx1 > maxx2 || maxx1 < minx2)
            {
                return false;
            }
        }
        return true;
    }

    // First AABB (Axis-aligned bounding boxes) colision sistem
    static bool AABBcollision(sf::Shape &collision1, sf::Shape &collision2){
        
        // Get vertices
        std::vector<sf::Vector2f> vertices1 = getVertices(collision1);
        std::vector<sf::Vector2f> vertices2 = getVertices(collision2);
        
        // Get the max and min vertices from the 2 axis
        std::array<float, 4> points1 = getXYMaxMinVertices(vertices1);
        float minx1 = points1[0];
        float miny1 = points1[1];
        float maxx1 = points1[2];
        float maxy1 = points1[3];

        std::array<float, 4> points2 = getXYMaxMinVertices(vertices2);
        float minx2 = points2[0];
        float miny2 = points2[1];
        float maxx2 = points2[2];
        float maxy2 = points2[3];

        // Check if they are coliden in the 2 axis, if so, they are colliding :)
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
        if (collisionx && collisiony) {
            return true;
        } else {
            return false;
        }
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

                float pointAngelObjetive = pointAngle - rotation;

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
        return separatingAxises;
    }

    static std::array<float, 4> getXYMaxMinVertices(std::vector<sf::Vector2f> vertices){

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

    static std::array<float, 2> getMinMaxRelativeVectors(std::vector<sf::Vector2f> vertices, sf::Vector2f axis){

        float min = INT64_MAX;
        float max = INT64_MIN;
        for(sf::Vector2f vertex : vertices){
            float dotProduct = math::dotProduct(vertex, axis);
            if(dotProduct > max){
                max = dotProduct;
            }
            if(dotProduct < min){
                min = dotProduct;
            }
        }
        return {min, max};

    }

    static std::vector<sf::Vector2f> joinNormals(std::vector<sf::Vector2f> normals1, std::vector<sf::Vector2f> normals2){

        // IDK why the dot product give me the value that I need, but I dont care :)

        std::vector<sf::Vector2f> normals;
        for(auto normal : normals1){
            if(normals.size() != 0){
                for(auto normalI : normals){
                    if(!(normal == normalI || -normal.x == normalI.x && -normal.y == normalI.y)){
                        normals.push_back(normal);
                    }
                }
            } else{
                normals.push_back(normal);
            }
        }
        for(auto normal : normals2){
            if(normals.size() != 0){
                for(auto normalI : normals){
                    if(!(normal == normalI || -normal.x == normalI.x && -normal.y == normalI.y)){
                        normals.push_back(normal);
                    }
                }
            } else{
                normals.push_back(normal);
            }
        }
        return normals;
    }

};

