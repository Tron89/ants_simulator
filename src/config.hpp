#include <iostream>
#include <SFML/Graphics.hpp>

#ifndef CONFIG_HPP
#define CONFIG_HPP

namespace config
{
std::string title = "Ants!";
int screenX = 1500;
int screenY = 1000;
int antsNumber = 50;
int cameraSpeed = 100;

// maybe this can break the world, but meeee
float timeSpeed = 1.f;

bool passConsole = false;
bool seeFPS = false;
bool seeSpawn = false;


// ant
float antRadius = 1.f;
float antSpeed = 40.f;
float antRotation = 90.f;
float antDetection = 50.f;

// rock
float rockSizeX = 10.f;
float rockSizeY = 10.f;
sf::Color rockColor(194, 197, 204);

//food
float foodRadius = 50.f;
sf::Color foodColor(100, 255, 100);

//nest
float nestRadius = 10.f;
sf::Color nestColor(100, 255, 100);

//pheromones
float pheromoneRadius = 0.5f;
float pheromoneTimeToDisappear = 5.f;
}

#endif // CONFIG_HPP