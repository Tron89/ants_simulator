import pygame
from environment import Environment
from ant import Ant

pygame.init()

# Configuración de la pantalla
width, height = 800, 600
screen = pygame.display.set_mode((width, height))
pygame.display.set_caption("Simulador de Hormigas")

# Inicializar el entorno y las hormigas
environment = Environment(width, height)
ant1 = Ant(5, 0) # Crear una hormiga de ejemplo

running = True
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    # Limpiar la pantalla y dibujar el entorno y las hormigas
    screen.fill((255, 255, 255))  # Fondo blanco

    # Dibujar la cuadrícula
    cell_size = 20
    for x in range(0, width, cell_size):
        pygame.draw.line(screen, (200, 200, 200), (x, 0), (x, height))
    for y in range(0, height, cell_size):
        pygame.draw.line(screen, (200, 200, 200), (0, y), (width, y))

    ant1.moveRight()

    # Actualizar el entorno y las hormigas
    environment.update()
    pygame.draw.circle(screen, (0, 0, 0), (ant1.position()), 10)  # (255, 0, 0) es el color rojo, 10 es el radio

    # Dibujar el entorno y las hormigas

    pygame.display.flip()

pygame.quit()
