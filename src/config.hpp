#include <iostream>
#include <SFML/Graphics.hpp>

#ifndef CONFIG_HPP
#define CONFIG_HPP

namespace config
{
std::string title = "Ants!";
int screenX = 1500;
int screenY = 1000;
int antsNumber = 500;
int cameraSpeed = 100;

// maybe this can break the world, but meeee
float timeSpeed = 1.f;

bool passConsole = true;
bool seeFPS = true;

// ant
float antRadius = 1.f;
float antSpeed = 40.f;
float antRotation = 1.f;
}

#endif // CONFIG_HPP