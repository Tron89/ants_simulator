import pygame
from environment import Environment
from ant import Ant
import sys
import parameters

# I don't put the DeltaTime because I don't want c:

pygame.init()

width, height = parameters.width, parameters.height
screen = pygame.display.set_mode((width, height))
clock = pygame.time.Clock()

environment = Environment()

clock.tick(30)

while True:

    frame_rate = str(int(clock.get_fps()))
    pygame.display.set_caption(parameters.caption + " FPS - " + frame_rate)

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            sys.exit()

    # --- LOGIC
    environment.update()
    # --- LOGIC
    screen.fill((255, 255, 255))
    # --- SCREEN
    environment.screen(screen)

    
    # --- SCREEN

    pygame.display.flip()
    clock.tick()

pygame.quit()
