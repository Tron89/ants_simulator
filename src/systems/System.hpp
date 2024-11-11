#include <SFML/Graphics.hpp>
#include "../Entity.hpp"

#pragma once

class System{
    public:
    virtual void Update(std::vector<Entity*>& entities){};
    virtual ~System() = default;
};