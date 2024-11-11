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


#include "Entity.hpp"

#include "components/Component.hpp"
#include "components/CircleShape.hpp"
#include "components/Movement.hpp"
#include "components/Position.hpp"

#include "systems/System.hpp"
#include "systems/Gravity.hpp"
#include "systems/Draw.hpp"

#pragma once


class Environment
{
public:
    bool leftButtonPressed;
    std::string thingToSpawn;

    std::vector<Entity*> entities;

    Environment()
    {

        Entity* ant1 = new Entity();
        ant1->AddComponent<PositionComponent>();
        ant1->AddComponent<CircleShapeComponent>();

        entities.push_back(ant1);
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
            Ant* ant = new Ant(pheromones, distributionX(generator), distributionY(generator));
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

        // Order of drawing

        all.push_back(reinterpret_cast<std::vector<sf::Shape*>*>(&rocks));
        all.push_back(reinterpret_cast<std::vector<sf::Shape*>*>(&foods));
        all.push_back(reinterpret_cast<std::vector<sf::Shape*>*>(&ants));
        all.push_back(reinterpret_cast<std::vector<sf::Shape*>*>(&pheromones));
    }

    void update(sf::RenderWindow &window)
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

            if (0 < ant->getPosition().y/config::chunkSize && 0 < ant->getPosition().x/config::chunkSize && ant->getPosition().y/config::chunkSize < chunks.size() && ant->getPosition().x/config::chunkSize < chunks[ant->getPosition().y/config::chunkSize].size()){
                chunks[ant->getPosition().y/config::chunkSize][ant->getPosition().x/config::chunkSize].add(ant);
            }

            // update ants
            AntUpdater::update(*ant, rotate);
        }

    
        for (size_t y = 0; y < chunks.size(); y++)
        {
            for (size_t x = 0; x < chunks[y].size(); x++)
            {
                for (size_t objectAnum = 0; objectAnum < chunks[y][x].content.size(); objectAnum++)
                {
                    for (size_t objectBnum = 0; objectBnum < chunks[y][x].content.size(); objectBnum++)
                    {
                        sf::Shape* objectA = chunks[y][x].content[objectAnum];
                        sf::Shape* objectB = chunks[y][x].content[objectBnum];
                        if (objectAnum == objectBnum){
                            continue;
                        } else if(Collisions::SATcollision(*objectA, *objectB)){

                            // TODO: Change to a proper collision handeler
                            if (Ant* antA = dynamic_cast<Ant*>(objectA); Ant* antB = dynamic_cast<Ant*>(objectB)){
                                AntCollider::onCollisionEnter(antA, antB);
                                AntCollider::onCollisionEnter(antB, antA);
                            }
                            
                        }
                    }
                }
            }
        }
    


        pheromones.erase(std::remove_if(pheromones.begin(), pheromones.end(),
                                [](Pheromone* pheromone)
                                {
                                    bool shouldErase = pheromone->disappear;
                                    if (shouldErase) {
                                        delete pheromone;
                                    }
                                    return shouldErase;
                                }),
                 pheromones.end());

        for (auto &pheromone : pheromones)
        {
            pheromone->update();
        }




        Gravity gravitySystem;


        gravitySystem.Update(entities, config::dt);
        


    }

    void draw(sf::RenderWindow &window)
    {

        Draw drawSystem;
        drawSystem.Update(entities, window);

        // chunks
        for (auto &line : chunks){
            for (auto &chunk : line){
                chunk.clear();
                window.draw(chunk);
            }
        }

        // all normal objects
        for (auto list : all){
            for (auto object : *list){
                window.draw(*object);
            }
        }

        // nests, because it need the text up
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

        // for tests
        for (size_t i = 0; i < config::test.size(); i++)
        {
            sf::Vector2f side(1, 1);
            sf::RectangleShape line(side);
            line.setPosition(config::test[i]);
            line.setFillColor(sf::Color(255, 0, 0));
            window.draw(line);
            config::test.clear();
        }
        
    }



    // TODO: I have to avoid do this, or else this is going to become a caos

    std::vector<Ant*> ants;
    std::vector<Rock*> rocks;
    std::vector<Food*> foods;
    std::vector<Nest*> nests;
    std::vector<Pheromone*> pheromones;

    std::vector<std::vector<sf::Shape*>*> all;
    std::vector<std::vector<Chunk>> chunks;

private:

};

