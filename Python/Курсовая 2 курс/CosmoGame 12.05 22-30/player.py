import pygame
import math

class Player:
    def __init__(self, x, y, width, height):
        self.x = x
        self.y = y
        self.width = width
        self.height = height
        self.animation_count = 0
    def main(self, screen):
        if self.animation_count + 1 >= 16:
            self.animation_count = 0
        
        self.animation_count += 1
        
        # screen.blit(player_walk_images[self.animation_count], (self.x, self.y))
        pygame.draw.rect(screen, (255, 0, 0), (self.x, self.y, self.width, self.height))
        
class PlayerShoot:
    def __init__(self, x, y, mouse_x, mouse_y):
        self.x = x
        self.y = y
        self.mouse_x = mouse_x
        self.mouse_y = mouse_y
        self.speed = 15
        self.angle = math.atan2(y-mouse_y, x-mouse_x)
        self.x_vel = math.cos(self.angle) * self.speed
        self.y_vel = math.sin(self.angle) * self.speed
    def main(self, screen):
        self.x -= int(self.x_vel)
        self.y -= int(self.y_vel)
        
        pygame.draw.circle(screen, (0, 0, 0), (self.x, self.y), 5)
        