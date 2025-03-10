#include <iostream>
#include <SFML/Graphics.hpp>

#include "Environment.hpp"
#include "config.hpp"

#include "components/Shape.hpp"
#include "components/PhysicBody.hpp"
#include "components/Transform.hpp"

class Input{
public:

    static void update(sf::RenderWindow &window, sf::View &view, Environment &enviroment){
        

        // view movement
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            view.move(-config::cameraSpeed * config::dt, 0.f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            view.move(config::cameraSpeed * config::dt, 0.f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            view.move(0.f, -config::cameraSpeed * config::dt);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            view.move(0.f, config::cameraSpeed * config::dt);
        }

        spawn(window, enviroment);



    }


    static void spawn(sf::RenderWindow &window, Environment &enviroment){
        
        sf::Vector2f worldPos;
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !enviroment.leftButtonPressed)
        {
            enviroment.leftButtonPressed = true;
            sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
            worldPos = window.mapPixelToCoords(pixelPos);

            if (enviroment.thingToSpawn == "ant")
            {
                Entity* ant1 = new Entity();
                ant1->AddComponent<TransformComponent>(worldPos.x, worldPos.y);
                ant1->AddComponent<PhysicBodyComponent>();
                ant1->AddComponent<ShapeComponent>();

                enviroment.entities.push_back(ant1);
            }
            else if (enviroment.thingToSpawn == "rock")
            {
                enviroment.rocks.push_back(new Rock(worldPos.x, worldPos.y));
            }
            else if (enviroment.thingToSpawn == "food")
            {
                enviroment.foods.push_back(new Food(worldPos.x, worldPos.y));
            }
            else if (enviroment.thingToSpawn == "nest")
            {
                enviroment.nests.push_back(new Nest(worldPos.x, worldPos.y));
            }
            else if (enviroment.thingToSpawn == "searching")
            {
                enviroment.pheromones.push_back(new Pheromone(worldPos.x, worldPos.y, "searching"));
            }
            else if (enviroment.thingToSpawn == "finded")
            {
                enviroment.pheromones.push_back(new Pheromone(worldPos.x, worldPos.y, "finded"));
            }
        }
        else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            enviroment.leftButtonPressed = false;
        }

        /* SPAWN */
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
        {
            enviroment.thingToSpawn = "ant";
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
        {
            enviroment.thingToSpawn = "rock";
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
        {
            enviroment.thingToSpawn = "food";
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
        {
            enviroment.thingToSpawn = "nest";
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
        {
            enviroment.thingToSpawn = "searching";
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6))
        {
            enviroment.thingToSpawn = "finded";
        }

        if (config::seeSpawn)
        {
            std::cout << enviroment.thingToSpawn << std::endl;
        }
    }

private:

};