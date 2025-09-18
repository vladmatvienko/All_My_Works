from Area import *

class Sam_Stormtrooper():

    def __init__(self):
        self.health = 100
        self.hit_radius = 1
        self.Area = Area(2, 4)
        self.Sam_area = self.Area.get_Area()
        print(self.Sam_area)
        self.hit_strength = 40
        self.visibility = 10
        self.Sam_X = self.Area.get_X()
        self.Sam_Y = self.Area.get_Y()

    #def shoot(self):

    def click(self, mouse_pos, x1, y1):

        cell_x = mouse_pos[0] // self.cell_size - x1
        cell_y = mouse_pos[1] // self.cell_size - y1