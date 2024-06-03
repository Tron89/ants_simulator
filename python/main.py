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
dt = 0
frame_rate = 1

environment = Environment()

clock.tick(30)

while True:

    frame_rate = int(clock.get_fps())
    
    pygame.display.set_caption(parameters.caption + " FPS - " + str(frame_rate))

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            sys.exit()

    # --- LOGIC
            
    environment.update_logic(dt)
    
    # --- LOGIC

    screen.fill((255, 255, 255))
    
    # --- SCREEN
    
    environment.update_screen(screen)
    
    # --- SCREEN

    pygame.display.flip()
    clock.tick()
    
    if frame_rate != 0:
        dt = 60/frame_rate

pygame.quit()
