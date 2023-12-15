import random

class Ant:
    def __init__(self, x, y):
        self.x = x 
        self.y = y 
        # Otras inicializaciones necesarias

    def move(self):
        # Implementar la lógica de movimiento de la hormiga

        pass

    def position(self):
        return self.x * 20 + 10, self.y * 20 + 10
    
    def moveUp(self):
        self.y -= 1    
        pass

    def moveDown(self):
        self.y += 1
        pass
    
    def moveLeft(self):
        self.x -= 1
        pass

    def moveRight(self):
        self.x += 1
        pass