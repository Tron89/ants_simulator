#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include "Ant.hpp"

class Environment
{
public:
    Environment(size_t numberOfAnts)
    {
        // spawn ants in random places
        std::mt19937 generator;
        auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
        generator.seed(seed);
        std::uniform_real_distribution<float> distribution(0, 1000);

        // create the ants and save it in a vector
        ants.reserve(numberOfAnts);
        for (size_t i = 0; i < numberOfAnts; ++i)
        {
            Ant ant(distribution(generator), distribution(generator)); // Example radius
            ants.push_back(ant);
        }

        // an example of a rectangle (for collisions test)

        // int rectangleX = 500;
        // int rectangleY = 500;
        // sf::RectangleShape rectangle(sf::Vector2f(500, 500));
        // rectangle.setOrigin(rectangleX/2, rectangleY/2);
        // rectangle.setPosition(1500, 500);
        // rectangle.setFillColor(sf::Color(100,100,100));
        // squares.push_back(rectangle);
        
    }

    void update(float dt)
    {
        // create the random generator (is here and no in the ants because is more eficient)
        std::mt19937 generator;
        auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
        generator.seed(seed);
        std::uniform_real_distribution<float> distribution(-1, 1);

        // what is going to do every ant
        for (auto &ant : ants)
        {
            // update things
            float rotate = distribution(generator);

            // colision detection
            
            // for (auto &antToColide : ants)
            // {
            //     if (antToColide.getPosition() != ant.getPosition())
            //     {
            //         sf::Vector2f pos1 = ant.getPosition();
            //         sf::Vector2f pos2 = antToColide.getPosition();
            //         float distance = std::sqrt(std::pow(pos1.x - pos2.x, 2) + std::pow(pos1.y - pos2.y, 2));

            //         if (distance < (ant.getRadius() + antToColide.getRadius()))
            //         {
            //             ant.onCollisionEnter(antToColide);
            //             antToColide.onCollisionEnter(ant);
            //         }
            //     }
            // }


            // for (auto &square : squares){
            //     // an Axis-Aligned Bounding Box (AABB) Collision Detection
            //     float antXMaxPosition = ant.getPosition().x + ant.getRadius();
            //     float antXMinPosition = ant.getPosition().x - ant.getRadius();
            //     float antYMaxPosition = ant.getPosition().y + ant.getRadius();
            //     float antYMinPosition = ant.getPosition().y - ant.getRadius();

            //     float squareXMaxPosition = square.getPosition().x + square.getSize().x/2;
            //     float squareXMinPosition = square.getPosition().x - square.getSize().x/2;
            //     float squareYMaxPosition = square.getPosition().y + square.getSize().y/2;
            //     float squareYMinPosition = square.getPosition().y - square.getSize().y/2;

            //     bool xCollision = antXMaxPosition >= squareXMinPosition && squareXMaxPosition >= antXMinPosition;
            //     bool yCollision = antYMaxPosition >= squareYMinPosition && squareYMaxPosition >= antYMinPosition;

            //     if (xCollision && yCollision){
            //         ant.onCollisionEnter(square);
            //     }

            // }

            // update ants
            ant.update(dt, rotate);
        }
    }

    void draw(sf::RenderWindow &window)
    {
        for (auto &square : squares){
            window.draw(square);
        }
        for (auto &ant : ants)
        {
            window.draw(ant);
        }

    }

private:
    // TODO: I have to avoid do this, or else this is going to become a caos
    // I have to, put all in one or something (for improve collision update)

    std::vector<Ant> ants;
    std::vector<sf::RectangleShape> squares;
};