#include <iostream>
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <typeindex>
#include <memory>
#include "./components/Component.hpp"

#pragma once

/**
 * @brief A class representing a game object with components,
 *  without any default components
 * 
 */
class Entity
{
public:

    /**
     * @brief It receives a component and adds it to the entity
     * 
     * @tparam T The component to be added
     * @tparam Args 
     * @param args The arguments to be forwarded to the component constructor
     */
    template <typename T, typename... Args>
    void AddComponent(Args&&... args) {
        components[typeid(T)] = std::make_unique<T>(std::forward<Args>(args)...);
    }

    /**
     * @brief It gets a pointer to a component from the entity, if it not exists, it returns nullptr
     * 
     * @tparam T The component to be removed
     */
    template <typename T>
    T* GetComponent() {
        auto it = components.find(typeid(T));
        return it != components.end() ? static_cast<T*>(it->second.get()) : nullptr;
    }

    virtual ~Entity() = default;

private:
    std::unordered_map<std::type_index, std::unique_ptr<Component>> components;
};

