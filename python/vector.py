# it's time to use my new adquired of trigonometry

# rotation in radians, but the inputs in grades because I'm stoned

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

    def subtract(a, b):
        return(a.transform.x - b.transform.x, a.transform.y - b.transform.y)
    
    def add(a, b):
        return(a.transform.x + b.transform.x, a.transform.y + b.transform.y)



