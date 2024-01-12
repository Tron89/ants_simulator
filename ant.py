import random
from vector import Vector
import random
import parameters

class Ant:
    def __init__(self, x, y, angle, speed):
        self.transform = Vector(x, y, angle, speed)

    def update(self, colision):
        self.transform.add_rotation(random.randint(-10,10))
        if colision == True:
            self.transform.add_rotation(180)
        self.transform.move()

        if self.transform.x >= parameters.width:
            self.transform.x = 0

        if self.transform.x <= 0:
            self.transform.x = parameters.width

        if self.transform.y >= parameters.height:
            self.transform.y = 0

        if self.transform.y <= 0:
            self.transform.y = parameters.height