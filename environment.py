from ant import Ant
import parameters
import pygame
from vector import Vector

class Environment:
    def __init__(self):
        self.ants = [Ant(parameters.ants_init_x, parameters.ants_init_y, parameters.ants_init_angle, parameters.ants_init_speed) for _ in range(parameters.ants_init_count)]
        self.ants.append(Ant(10, 10, 0, 1))

    def update(self):
        for ant1 in self.ants:

            colision = False

            #colisions that I don't know how to do
            """
            for ant2 in self.ants:
                if ant1 != ant2:
                    total_vector = Vector.subtract(ant1, ant2)
                    distance = total_vector[0] - total_vector[1]
                    distance = abs(distance)
                    print(total_vector)
                    print(distance)
                    if distance <= 4:
                        colision = True

            """
                
            ant1.update(colision)



    def screen(self, screen):
        for ant in self.ants:
            pygame.draw.rect(screen, (0, 0, 0), (ant.transform.x, ant.transform.y,2,2))
            
                
