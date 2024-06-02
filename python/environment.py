from ant import Ant
import parameters
import pygame

class Environment:
    def __init__(self):
        self.ants = [Ant(parameters.ants_init_x, parameters.ants_init_y, parameters.ants_init_angle, parameters.ants_init_speed) for _ in range(parameters.ants_init_count)]


    def update_logic(self):
        for ant in self.ants:

            #colisions that I don't know how to do
                
            ant.update()


            



    def update_screen(self, screen):
        for ant in self.ants:
            pygame.draw.circle(screen, (0, 0, 0), (ant.transform.x, ant.transform.y), parameters.ants_radius)
            
                
