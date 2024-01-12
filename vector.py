# it's time to use my new adquired of trigonometry

# rotation in radians, but the inputs in grades

from math import atan2, sin, cos, radians

class Vector:
    def __init__(self, x, y, angle, speed):
        self.x = x
        self.y = y
        self.angle = radians(angle)
        self.speed = speed
    
    def move(self):
        movementx = self.speed * cos(self.angle)
        movementy = self.speed * sin(self.angle)
        
        self.x += movementx
        self.y += movementy

    def add_rotation(self, angle):
        self.angle += radians(angle)

    def subtract(x, y):
        return(x.transform.x - y.transform.x, x.transform.y - y.transform.y)



