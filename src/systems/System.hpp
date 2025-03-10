#include <SFML/Graphics.hpp>
#include "../Entity.hpp"

#pragma once

/**
 * @brief  The base class for systems
 * 
 */
class System{
    public:
    virtual void Update(std::vector<Entity*>& entities){};
    virtual ~System() = default;
};