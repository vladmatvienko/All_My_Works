import Settings_game
from Settings_game import *

class Area():
    def create_area(self):
        for y in range(self.height):
            for x in range(self.width):
                if self.board[y][x] == self.obj:
                    self.X_pers.append(x)
                    self.Y_pers.append(y)
                    for i in range(-self.radius, self.radius+1):
                        for p in range(-self.radius, self.radius+1):
                            if y+i >= 0 and x+p >= 0:
                                self.Area[y+i][x+p] = self.board[y+i][x+p]

    def __init__(self, obj, radius):
        self.Area = []
        self.width = Settings.width
        self.height = Settings.height
        self.board = Settings.board
        self.obj = obj
        self.radius = radius
        self.X_pers = []
        self.Y_pers = []

        for y in range(self.height):
            row = []
            for x in range(self.width):
                row.append(0)
            self.Area.append(row)
        self.create_area()
