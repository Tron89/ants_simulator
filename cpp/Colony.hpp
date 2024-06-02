#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include "Ant.hpp"

class Colony
{
public:
    Colony(size_t numberOfAnts)
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
    }

    void update(float dt)
    {
        // create the random generator
        std::mt19937 generator;
        auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
        generator.seed(seed);
        std::uniform_real_distribution<float> distribution(-1, 1);

        // what is going to do every ant
        for (auto &ant : ants)
        {
            float rotate = distribution(generator);

            // colision detection
            for (auto &antToColide : ants)
            {
                if (antToColide.getPosition() != ant.getPosition())
                {
                    sf::Vector2f pos1 = ant.getPosition();
                    sf::Vector2f pos2 = antToColide.getPosition();
                    float distance = std::sqrt(std::pow(pos1.x - pos2.x, 2) + std::pow(pos1.y - pos2.y, 2));

                    if (distance < (ant.getRadius() + antToColide.getRadius()))
                    {
                        ant.onCollisionEnter(&antToColide);
                    }
                }
            }

            ant.update(dt, rotate);
        }
    }

    void draw(sf::RenderWindow &window)
    {
        for (auto &ant : ants)
        {
            window.draw(ant);
        }
    }

private:
    std::vector<Ant> ants;
};