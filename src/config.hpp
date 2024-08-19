#include <iostream>
#include <SFML/Graphics.hpp>

#ifndef CONFIG_HPP
#define CONFIG_HPP

namespace config
{
std::string title = "Ants!";
int screenX = 550;
int screenY = 550;
int antsNumber = 0;
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
float antDetection = 100.f;

float movmentWeight = 1.f;
float pheromonesWeight = 5.f;
float rotationWeight = 2.5f;
float foodWeight = 100.f;
float nestsWeight = 100.f;

float timeToCreatePheromone = 1.f;
float timeToLost = 15.f;
// rock
float rockSizeX = 10.f;
float rockSizeY = 10.f;
sf::Color rockColor(194, 197, 204);

//food
float foodRadius = 5.f;
sf::Color foodColor(100, 255, 100);

//nest
float nestRadius = 10.f;
sf::Color nestColor(100, 255, 100);

//pheromones
float pheromoneRadius = 1.f;
float pheromoneTimeToDisappear = 20.f;
}

#endif // CONFIG_HPP