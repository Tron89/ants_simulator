#include <iostream>
#include <SFML/Graphics.hpp>

#pragma once

namespace config
{
std::string title = "Ants!";
int screenX = 1000;
int screenY = 1000;
// 400 ants max for 60 fps (with a bad colision detection)
// 10000 ants max for 60 fps with a non finished chunk-based colision detection
int antsNumber = 0;
int cameraSpeed = 100;

// maybe this can break the world, but meeee
float timeSpeed = 1.f;
float dt;

bool passConsole = true;
bool seeFPS = false;
bool seeSpawn = false;
int fpsLimit = 10;

// Chunks
float chunkSize = 20.f;
sf::Color chunkOutlineColor(194, 197, 204, 50);

// ant
int antCreationNumber = 1;
float antRadius = 1.f;
float antSpeed = 40.f;
float antRotation = 90.f;
float antDetection = 100.f;

float movmentWeight = 1.f;
float pheromonesWeight = 1.f;
float rotationWeight = 1.f;
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
float pheromoneTimeToDisappear = 30.f;


std::vector<sf::Vector2f> test;
std::vector<sf::Vector2f> test2;

}
