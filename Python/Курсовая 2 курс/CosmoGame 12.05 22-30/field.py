import pygame

class Field:
    def __init__(self, width, height, screen, sqr_size):
        self.width = width
        self.height = height
        self.screen = screen
        self.sqr_size = sqr_size

        self.board = []
        for asimp in range(self.height):
            str = []
            for ord in range(self.width):
                str.append(0)
            self.board.append(str)

    def render(self):
        for asimp in range(self.height):
            for ord in range(self.width):
                pygame.draw.rect(self.screen, pygame.Color(0, 0, 0), 
                                (ord * self.sqr_size, asimp * self.sqr_size, 
                                self.sqr_size, self.sqr_size), 1)
    
        
    def check_hover_cel(self, mouse_pos):
        self.is_hovered = self.rect.collidepoint(mouse_pos)