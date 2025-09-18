import pygame.draw
import random
from State import *
class Board():

    def __init__(self, width, height, number_pers, number_enemy):
        self.number_pers = number_pers
        self.number_enemy = number_enemy
        self.width = width
        self.height = height
        spawn_pl = [1, 2]
        spawn_en = [1, 4]
        self.board = []
        for y in range(self.height):
            row = []
            for x in range(self.width):
                if y <= 3 and x <= 3:
                    a = 1
                else:
                    a = random.randint(1, 100)
                    if a < 96:
                        a = 1
                    else:
                        a = 3

                row.append(a)
            self.board.append(row)
        self.spawn_rand_pl()
        self.spawn_rand_en()
        self.cell_size = 50



    def spawn_rand_pl(self):
        count = 0
        while count < self.number_pers:
            x = random.randint(1, 3)
            y = random.randint(1, 3)
            if self.board[x][y] != 2:
                self.board[x][y] = 2
                count += 1
    def spawn_rand_en(self):
        count = 0
        while count < self.number_enemy:
            x = random.randint(10, 15)
            y = random.randint(10, 15)
            if self.board[x][y] != 4:
                self.board[x][y] = 4
                count += 1
    def render(self, screen, x1, y1):
        for y in range(self.height):
            for x in range(self.width):
                if self.board[y][x] == 1:
                    pygame.draw.rect(screen, pygame.Color(State.grass[1]), ((x + x1) * self.cell_size, (y + y1) * self.cell_size, self.cell_size, self.cell_size), 0)
                elif self.board[y][x] == 2:
                    pygame.draw.rect(screen, pygame.Color(State.pers[1]), ((x + x1) * self.cell_size, (y + y1) * self.cell_size, self.cell_size, self.cell_size), 0)
                elif self.board[y][x] == 3:
                    pygame.draw.rect(screen, pygame.Color(State.tree[1]),((x + x1) * self.cell_size, (y + y1) * self.cell_size, self.cell_size, self.cell_size), 0)
                else:
                    pygame.draw.rect(screen, pygame.Color(State.enemy[1]), ((x + x1) * self.cell_size, (y + y1) * self.cell_size, self.cell_size, self.cell_size), 0)
                pygame.draw.rect(screen, pygame.Color("Grey"),((x + x1) * self.cell_size, (y + y1) * self.cell_size, self.cell_size, self.cell_size), 1)


    def click(self, mouse_pos, x1, y1):

        cell_x = mouse_pos[0] // self.cell_size - x1
        cell_y = mouse_pos[1] // self.cell_size - y1

        if not(cell_x < 0 or cell_x >= self.width or cell_y < 0 or cell_y >= self.height):
            self.board[cell_y][cell_x] = (self.board[cell_y][cell_x] + 1) % 4
    def print_board(self):
        print("\n \n \n Original \n \n \n")
        for y in range(self.height):
            print(self.board[y])

    def get_board(self):
        return self.board
    def get_height(self):
        return self.height
    def get_width(self):
        return self.width
