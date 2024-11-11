#include <iostream>
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <typeindex>
#include <memory>
#include "./components/Component.hpp"

#pragma once

class Entity
{
public:

    template <typename T, typename... Args>
    void AddComponent(Args&&... args) {
        components[typeid(T)] = std::make_unique<T>(std::forward<Args>(args)...);
    }

    template <typename T>
    T* GetComponent() {
        auto it = components.find(typeid(T));
        if (it == components.end()){
            std::cerr << "Error: Componente de tipo " << typeid(T).name() << " no encontrado." << std::endl;
            return nullptr;
        }
        return it != components.end() ? static_cast<T*>(it->second.get()) : nullptr;
    }


private:

    std::unordered_map<std::type_index, std::unique_ptr<Component>> components;

};

