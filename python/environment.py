from ant import Ant
import parameters
import pygame
from math import sqrt
import random

class Environment:
    def __init__(self):
        self.ants = [Ant(random.randint(0, 1200), random.randint(0, 800), parameters.ants_init_angle, parameters.ants_init_speed) for _ in range(parameters.ants_init_count)]


    def update_logic(self, dt):
        for ant in self.ants:

            #colisions that I don't know how to do

            #something shabby to compare performance with c++
            for colisionAnt in self.ants:
                if (sqrt((ant.transform.x - colisionAnt.transform.x)**2 + (ant.transform.y - colisionAnt.transform.y)**2) < parameters.ants_radius*2 and ant != colisionAnt):
                    ant.colision()
                
            ant.update(dt)


            



    def update_screen(self, screen):
        for ant in self.ants:
            pygame.draw.circle(screen, ant.color, (ant.transform.x, ant.transform.y), parameters.ants_radius)
            
                
