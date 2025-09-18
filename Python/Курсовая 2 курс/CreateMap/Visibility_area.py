from Board import *

class visibility_area:

    def __init__(self, width, height):
        self.visibility_area = []
        self.width = width
        self.height = height
        for y in range(self.height):
            row = []
            for x in range(self.width):
                row.append(0)
            self.visibility_area.append(row)
        for y in range(self.height):
            print(self.visibility_area[y])

   # def create_visibility_area(self):
   #     for y in range(self.height):
   #         for x in range(self.width):
   #             if ()