#include <SFML/Graphics.hpp>
#include "./System.hpp"
#include "../Entity.hpp"
#include "../Chunk.hpp"
#include "../config.hpp"
#include "../collisions.hpp"
#include "../components/Transform.hpp"
#include "../components/Shape.hpp"
#include "../components/PhysicBody.hpp"

#pragma once

// TODO: In proces

/**
 * @brief In proces
 * 
 */
class Collision : public System{
    public:
    void Update(std::vector<Entity*>& entities, std::vector<std::vector<Chunk>>& chunks) {
        

        for (auto &entity : entities)
        {
            // add every entity to his chunk
            sf::Vector2f position = entity->GetComponent<TransformComponent>()->getPosition();
            if (0 < position.y/config::chunkSize && 0 < position.x/config::chunkSize && position.y/config::chunkSize < chunks.size() && position.x/config::chunkSize < chunks[position.y/config::chunkSize].size()){
                chunks[position.y/config::chunkSize][position.x/config::chunkSize].add(entity);
            }
            
            // updating the position of the shape before the collision detection
            auto* shapeComponent = entity->GetComponent<ShapeComponent>();
            auto* transform = entity->GetComponent<TransformComponent>();
            if (shapeComponent && transform){
                auto* shape = shapeComponent->getShape();
                
                shape->setPosition(transform->getPosition());
                shape->setRotation(transform->getRotation());
                shape->setScale(transform->getScale());
                
            }

        }

    
        for (size_t y = 0; y < chunks.size(); y++)
        {
            for (size_t x = 0; x < chunks[y].size(); x++)
            {
                for (size_t objectAnum = 0; objectAnum < chunks[y][x].content.size(); objectAnum++)
                {
                    for (size_t objectBnum = 0; objectBnum < chunks[y][x].content.size(); objectBnum++)
                    {
                        sf::Shape* objectA = chunks[y][x].content[objectAnum]->GetComponent<ShapeComponent>()->getShape();
                        sf::Shape* objectB = chunks[y][x].content[objectBnum]->GetComponent<ShapeComponent>()->getShape();

                        if (objectA && objectB){

                            if (objectAnum == objectBnum){
                                continue;
                            } else if(Collisions::SATcollision(*objectA, *objectB)){
                                
                                chunks[y][x].content[objectAnum]->GetComponent<PhysicBodyComponent>()->getMovement();
                                // TODO: Change to a proper collision handeler
                                
                                
                            }
                        }
                    }
                }
            }
        }
    };

    virtual ~Collision() = default;
};

