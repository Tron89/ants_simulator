#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <random>
#include "ant/Ant.hpp"
#include "ant/ant_collider.hpp"
#include "ant/ant_updater.hpp"
#include "collisions.hpp"

#include "Rock.hpp"
#include "Food.hpp"
#include "Nest.hpp"
#include "Pheromone.hpp"
#include "Chunk.hpp"

#pragma once


/* 
template <typename Ta, typename Tb>
void colisionDetection(Ta &objectA, Tb &objectB){
    sf::Vector2f pos1 = objectA->getPosition();
    sf::Vector2f pos2 = objectB->getPosition();
    float distance = std::sqrt(std::pow(pos1.x - pos2.x, 2) + std::pow(pos1.y - pos2.y, 2));
    if (distance < (objectA->getRadius() + objectB->getRadius()))
    {
        AntCollider::onCollisionEnter(objectA, objectB);
        AntCollider::onCollisionEnter(objectB, objectA);
    }
}
*/


class Environment
{
public:
    bool leftButtonPressed;
    std::string thingToSpawn;

    Environment()
    {
        // this->all.push_back(&ants);





        // spawn ants in random places
        std::mt19937 generator;
        auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
        generator.seed(seed);
        std::uniform_real_distribution<float> distributionX(0, config::screenX);
        std::uniform_real_distribution<float> distributionY(0, config::screenY);

        // create the ants and save it in a vector
        ants.reserve(config::antsNumber);
        for (size_t i = 0; i < config::antsNumber; ++i)
        {
            Ant* ant = new Ant(pheromones, distributionX(generator), distributionY(generator)); // Example radius
            ants.push_back(ant);
        }
        for (size_t y = 0; y < config::screenY/config::chunkSize; ++y){
            std::vector<Chunk> line;
            for (size_t x = 0; x < config::screenX/config::chunkSize; ++x){
                Chunk chunk(x*config::chunkSize, y*config::chunkSize);
                line.push_back(chunk);
            }
            chunks.push_back(line);
        }
        rocks.push_back(new Rock(20, 20, 10, 20));
        ants.push_back(new Ant(pheromones, 10, 10));
    }

    void update(sf::RenderWindow &window)
    {

        sf::Vector2f worldPos;
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !leftButtonPressed)
        {
            leftButtonPressed = true;
            sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
            worldPos = window.mapPixelToCoords(pixelPos);

            if (thingToSpawn == "ant")
            {
                for (size_t i = 0; i < config::antCreationNumber; i++)
                {
                    ants.push_back(new Ant(pheromones, worldPos.x, worldPos.y));
                }
            }
            else if (thingToSpawn == "rock")
            {
                rocks.push_back(new Rock(worldPos.x, worldPos.y));
            }
            else if (thingToSpawn == "food")
            {
                foods.push_back(new Food(worldPos.x, worldPos.y));
            }
            else if (thingToSpawn == "nest")
            {
                nests.push_back(new Nest(worldPos.x, worldPos.y));
            }
            else if (thingToSpawn == "searching")
            {
                pheromones.push_back(new Pheromone(worldPos.x, worldPos.y, "searching"));
            }
            else if (thingToSpawn == "finded")
            {
                pheromones.push_back(new Pheromone(worldPos.x, worldPos.y, "finded"));
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

            if (0 < ant->getPosition().y/config::chunkSize && 0 < ant->getPosition().x/config::chunkSize && ant->getPosition().y/config::chunkSize < chunks.size() && ant->getPosition().x/config::chunkSize < chunks[ant->getPosition().y/config::chunkSize].size()){
                chunks[ant->getPosition().y/config::chunkSize][ant->getPosition().x/config::chunkSize].add(ant);
            }

            // update ants
            AntUpdater::update(*ant, rotate);
        }

    /*
    for (size_t y = 0; y < chunks.size(); y++)
    {
        for (size_t x = 0; x < chunks[y].size(); x++)
        {
            for (size_t objectAnum = 0; objectAnum < chunks[y][x].content.size(); objectAnum++)
            {
                for (size_t objectBnum = 0; objectBnum < chunks[y][x].content.size(); objectBnum++)
                {
                    if (objectAnum == objectBnum){
                        continue;
                    } else{
                        colisionDetection(chunks[y][x].content[objectAnum], chunks[y][x].content[objectBnum]);
                    }
                }
            }
        }
    }
    */


        pheromones.erase(std::remove_if(pheromones.begin(), pheromones.end(),
                                [](Pheromone* pheromone)
                                {
                                    bool shouldErase = pheromone->disappear;
                                    if (shouldErase) {
                                        delete pheromone; // Libera la memoria del objeto
                                    }
                                    return shouldErase;
                                }),
                 pheromones.end());

        for (auto &pheromone : pheromones)
        {
            pheromone->update();
        }

        float speed = 25;
        float rotationSpeed = 25;
        // shape movement
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            rocks[0]->move(-speed * config::dt, 0.f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            rocks[0]->move(speed * config::dt, 0.f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            rocks[0]->move(0.f, -speed * config::dt);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            rocks[0]->move(0.f, speed * config::dt);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
        {
            rocks[0]->rotate(rotationSpeed * config::dt);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        {
            rocks[0]->rotate(-rotationSpeed * config::dt);
        }

        Collisions::getCollision(*rocks[0], *ants[0]);

    }

    void draw(sf::RenderWindow &window)
    {
        for (auto &line : chunks){
            for (auto &chunk : line){
                chunk.clear();
                window.draw(chunk);
            }
        }

        for (auto &rock : rocks)
        {
            window.draw(*rock);
        }
        for (auto &food : foods)
        {
            window.draw(*food);
        }
        for (auto &ant : ants)
        {
            window.draw(*ant);
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
            text.setString(std::to_string(nest->foodCount));
            text.setCharacterSize(24);
            text.setPosition(nest->getPosition().x - 10, nest->getPosition().y - 50);

            window.draw(text);

            window.draw(*nest);
        }

        for (auto &pheromone : pheromones)
        {
            window.draw(*pheromone);
        }

        for (size_t i = 0; i < config::test.size(); i++)
        {
            sf::Vector2f side(1, 1);
            sf::RectangleShape line(side);
            line.setPosition(config::test[i]);
            line.setFillColor(sf::Color(255, 0, 0));
            window.draw(line);
            config::test.clear();
        }

        for (size_t i = 0; i < config::test2.size(); i++)
        {
            sf::Vector2f side(1, 1);
            sf::RectangleShape line(side);
            line.setPosition(config::test2[i]);
            line.setFillColor(sf::Color(255, 0, 0));
            window.draw(line);
            config::test2.clear();
        }
        
    }

private:
    // TODO: I have to avoid do this, or else this is going to become a caos
    // I have to, put all in one or something (for improve collision update)
    // Change all this to pointer vectors

    std::vector<Ant*> ants;
    std::vector<Rock*> rocks;
    std::vector<Food*> foods;
    std::vector<Nest*> nests;
    std::vector<Pheromone*> pheromones;
    std::vector<std::vector<sf::Shape>*> all;
    std::vector<std::vector<Chunk>> chunks;
};




            // // colision detection
            // std::vector<Food> antFoods;
            // for (auto &food : foods)
            // {

            //     sf::Vector2f pos1 = ant.getPosition();
            //     sf::Vector2f pos2 = food.getPosition();

            //     float distance = std::sqrt(std::pow(pos1.x - pos2.x, 2) + std::pow(pos1.y - pos2.y, 2));
            //     if (distance <= config::antDetection && !ant.hasFood)
            //     {
            //         antFoods.push_back(food);   
            //     }

            //     if (food.getPosition() != ant.getPosition() && distance < (ant.getRadius() + food.getRadius()))
            //     {
            //         AntCollider::onCollisionEnter(ant, food);
            //         food.onCollisionEnter(ant);
            //     }
            // }


            // for (auto &rock : rocks)
            // {
            //     // an Axis-Aligned Bounding Box (AABB) Collision Detection
            //     float antXMaxPosition = ant.getPosition().x + ant.getRadius();
            //     float antXMinPosition = ant.getPosition().x - ant.getRadius();
            //     float antYMaxPosition = ant.getPosition().y + ant.getRadius();
            //     float antYMinPosition = ant.getPosition().y - ant.getRadius();

            //     float rockXMaxPosition = rock.getPosition().x + rock.getSize().x / 2;
            //     float rockXMinPosition = rock.getPosition().x - rock.getSize().x / 2;
            //     float rockYMaxPosition = rock.getPosition().y + rock.getSize().y / 2;
            //     float rockYMinPosition = rock.getPosition().y - rock.getSize().y / 2;

            //     bool xCollision = antXMaxPosition >= rockXMinPosition && rockXMaxPosition >= antXMinPosition;
            //     bool yCollision = antYMaxPosition >= rockYMinPosition && rockYMaxPosition >= antYMinPosition;

            //     if (xCollision && yCollision)
            //     {
            //         AntCollider::onCollisionEnter(ant, rock);
            //     }
            // }

            // std::vector<Nest> antNests;
            // for (auto &nest : nests)
            // {
            //     sf::Vector2f pos1 = ant.getPosition();
            //     sf::Vector2f pos2 = nest.getPosition();
            //     float distance = std::sqrt(std::pow(pos1.x - pos2.x, 2) + std::pow(pos1.y - pos2.y, 2));

            //     if (distance <= config::antDetection && ant.hasFood)
            //     {
            //         antNests.push_back(nest);   
            //     }

            //     if (distance < (ant.getRadius() + nest.getRadius()))
            //     {
            //         AntCollider::onCollisionEnter(ant, nest);
            //         nest.onCollisionEnter(ant);
            //     }
            // }

            // std::vector<Pheromone> antPheromones;

            // for (auto &pheromone : pheromones)
            // {
            //     sf::Vector2f pos1 = ant.getPosition();
            //     sf::Vector2f pos2 = pheromone.getPosition();

            //     float distance = std::sqrt(std::pow(pos1.x - pos2.x, 2) + std::pow(pos1.y - pos2.y, 2));
            //     if (distance <= config::antDetection)
            //     {
            //         if (ant.hasFood && pheromone.type == "searching") antPheromones.push_back(pheromone);
            //         if (!ant.hasFood && pheromone.type == "finded") antPheromones.push_back(pheromone);
            //     }
            // }
            // AntUpdater::GetVFood(ant, antFoods);
            // AntUpdater::GetVNests(ant, antNests);
            // AntUpdater::GetVPheromones(ant, antPheromones);

            // // std::cout << angle << std::endl;
            // // if (angle != 0)
            // // {
            // //     ant.rotate(angle);
            // // }