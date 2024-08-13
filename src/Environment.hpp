#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include "Ant.hpp"
#include "Rock.hpp"
#include "Food.hpp"
#include "Nest.hpp"
#include "Pheromone.hpp"

// sf::Vector2f normalize(sf::Vector2f toNormalize){
//     float x = toNormalize.x;
//     float y = toNormalize.y;
//     float magnitude = sqrt(pow(x, 2) + pow(y, 2));
//     sf::Vector2f normalized(x/magnitude, y/magnitude);
//     return normalized;
// }

class Environment
{
public:
    bool leftButtonPressed;
    std::string thingToSpawn;

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

        Food food1(500, 500, 50);
        foods.push_back(food1);

        Nest nest1(100, 50, 10);
        nests.push_back(nest1);
    }

    void update(float dt, sf::RenderWindow &window)
    {
        sf::Vector2f worldPos;
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !leftButtonPressed)
        {
            leftButtonPressed = true;
            sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
            worldPos = window.mapPixelToCoords(pixelPos);

            if (thingToSpawn == "ant")
            {
                Ant ant(worldPos.x, worldPos.y);
                ants.push_back(ant);
            }
            else if (thingToSpawn == "rock")
            {
                Rock rock(worldPos.x, worldPos.y);
                rocks.push_back(rock);
            }
            else if (thingToSpawn == "food")
            {
                Food food(worldPos.x, worldPos.y);
                foods.push_back(food);
            }
            else if (thingToSpawn == "nest")
            {
                Nest nest(worldPos.x, worldPos.y);
                nests.push_back(nest);
            }
            else if (thingToSpawn == "searching")
            {
                Pheromone pheromone(worldPos.x, worldPos.y, "searching");
                pheromones.push_back(pheromone);
            }
            else if (thingToSpawn == "finded")
            {
                Pheromone pheromone(worldPos.x, worldPos.y, "finded");
                pheromones.push_back(pheromone);
            }
        }
        else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            leftButtonPressed = false;
        }

        /* SPAWN */
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
        {
            thingToSpawn = "ant";
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
        {
            thingToSpawn = "rock";
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
        {
            thingToSpawn = "food";
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
        {
            thingToSpawn = "nest";
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
        {
            thingToSpawn = "searching";
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6))
        {
            thingToSpawn = "finded";
        }

        if (config::seeSpawn)
        {
            std::cout << thingToSpawn << std::endl;
        }

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

            for (auto &food : foods)
            {
                if (food.getPosition() != ant.getPosition())
                {
                    sf::Vector2f pos1 = ant.getPosition();
                    sf::Vector2f pos2 = food.getPosition();
                    float distance = std::sqrt(std::pow(pos1.x - pos2.x, 2) + std::pow(pos1.y - pos2.y, 2));

                    if (distance < (ant.getRadius() + food.getRadius()))
                    {
                        ant.onCollisionEnter(food);
                        food.onCollisionEnter(ant);
                    }
                }
            }

            for (auto &rock : rocks)
            {
                // an Axis-Aligned Bounding Box (AABB) Collision Detection
                float antXMaxPosition = ant.getPosition().x + ant.getRadius();
                float antXMinPosition = ant.getPosition().x - ant.getRadius();
                float antYMaxPosition = ant.getPosition().y + ant.getRadius();
                float antYMinPosition = ant.getPosition().y - ant.getRadius();

                float rockXMaxPosition = rock.getPosition().x + rock.getSize().x / 2;
                float rockXMinPosition = rock.getPosition().x - rock.getSize().x / 2;
                float rockYMaxPosition = rock.getPosition().y + rock.getSize().y / 2;
                float rockYMinPosition = rock.getPosition().y - rock.getSize().y / 2;

                bool xCollision = antXMaxPosition >= rockXMinPosition && rockXMaxPosition >= antXMinPosition;
                bool yCollision = antYMaxPosition >= rockYMinPosition && rockYMaxPosition >= antYMinPosition;

                if (xCollision && yCollision)
                {
                    ant.onCollisionEnter(rock);
                }
            }
            for (auto &nest : nests)
            {
                if (nest.getPosition() != ant.getPosition())
                {
                    sf::Vector2f pos1 = ant.getPosition();
                    sf::Vector2f pos2 = nest.getPosition();
                    float distance = std::sqrt(std::pow(pos1.x - pos2.x, 2) + std::pow(pos1.y - pos2.y, 2));

                    if (distance < (ant.getRadius() + nest.getRadius()))
                    {
                        ant.onCollisionEnter(nest);
                        nest.onCollisionEnter(ant);
                    }
                }
            }
            float angle = 0;
            float minDistance = config::antDetection;
            for (auto pheromone : pheromones)
            {
                sf::Vector2f pos1 = ant.getPosition();
                sf::Vector2f pos2 = pheromone.getPosition();

                std::vector<Pheromone> pheromones;

                float distance = std::sqrt(std::pow(pos1.x - pos2.x, 2) + std::pow(pos1.y - pos2.y, 2));
                if (distance <= config::antDetection)
                {
                    if (ant.hasFood && pheromone.type == "searching")
                    {
                        pheromones.push_back(pheromone);
                        // sf::Vector2f vectorToPheromone = pos2 - pos1;
                        // float radiansAngle = atan2(vectorToPheromone.y, vectorToPheromone.x);
                        // if (distance < minDistance)
                        // {
                        //     minDistance = distance;
                        //     angle = (radiansAngle * 180) / 3.141592;
                        // }
                    }
                    else if (!ant.hasFood && pheromone.type == "finded")
                    {
                        pheromones.push_back(pheromone);
                        // sf::Vector2f vectorToPheromone = pos2 - pos1;
                        // sf::Vector2f NormalizedVectorToPheromone = normalize(vectorToPheromone);
                        // float dotProduct = ant.vMovment.x * NormalizedVectorToPheromone.x + ant.vMovment.y * NormalizedVectorToPheromone.y;
                        // float radiansAngle = atan2(vectorToPheromone.y, vectorToPheromone.x);
                        // if (distance < minDistance)
                        // {
                        //     minDistance = distance;
                        //     angle = (radiansAngle * 180) / 3.141592;
                        //     angle = sqrt(pow(angle - ant.getRotation(), 2)) * dotProduct;
                        // }
                    }

                }
                ant.GetVDesired(pheromones);
            }
            // std::cout << angle << std::endl;
            // if (angle != 0)
            // {
            //     ant.rotate(angle);
            // }

            // update ants
            ant.update(dt, rotate);
        }

        pheromones.erase(std::remove_if(pheromones.begin(), pheromones.end(),
                                        [](const Pheromone &pheromone)
                                        { return pheromone.disappear; }),
                         pheromones.end());

        for (auto &pheromone : pheromones)
        {
            pheromone.update(dt);
        }
    }

    void draw(sf::RenderWindow &window)
    {
        for (auto &rock : rocks)
        {
            window.draw(rock);
        }
        for (auto &food : foods)
        {
            window.draw(food);
        }
        for (auto &ant : ants)
        {
            window.draw(ant);
        }
        for (auto &nest : nests)
        {
            sf::Text text;

            sf::Font font;
            if (!font.loadFromFile("./fonts/arial.ttf"))
            {
                std::cout << "FONT NOT FINDED" << std::endl;
            }
            text.setFont(font);
            text.setString(std::to_string(nest.foodCount));
            text.setCharacterSize(24);
            text.setPosition(nest.getPosition().x - 10, nest.getPosition().y - 50);

            window.draw(text);

            window.draw(nest);
        }

        for (auto &pheromone : pheromones)
        {
            window.draw(pheromone);
        }
    }

private:
    // TODO: I have to avoid do this, or else this is going to become a caos
    // I have to, put all in one or something (for improve collision update)
    // Change all this to pointer vectors

    std::vector<Ant> ants;
    std::vector<Rock> rocks;
    std::vector<Food> foods;
    std::vector<Nest> nests;
    std::vector<Pheromone> pheromones;
};