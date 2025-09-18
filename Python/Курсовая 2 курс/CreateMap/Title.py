import pygame
class title:
    def __init__(self, text, center_x, center_y, size, screen, color_x, color_y, color_z):
        self.text = text
        self.center_x = center_x
        self.center_y = center_y
        self.size = size
        font = pygame.font.Font(None, self.size)
        text_surface = font.render(self.text, True, (color_x, color_y, color_z))
        text_rect = text_surface.get_rect(center=(self.center_x, self.center_y))
        screen.blit(text_surface, text_rect)