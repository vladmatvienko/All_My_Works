import pygame
from settings import *
class Player(pygame.sprite.Sprite):
    def __init__(self):
        super().__init__()
        self.image = pygame.image.load('character_test.png').convert_alpha()
        self.pos = pygame.math.Vector2(player_start_x, player_start_y)
        self.steps = step_counter
    def user_input(self):
        self.velocity_x = 0
        self.velocity_y = 0

        keys = pygame.key.get_pressed()

        if keys[pygame.K_w]:
            while self.steps >= 0:
                pygame.time.wait(20) #Вот про таймер который я говорил в сообщении, он не особо спасает, но как временное решение сошёл
                self.velocity_y -= self.steps
                self.steps -= 1
            self.steps = step_counter
        if keys[pygame.K_s]:
            while self.steps >= 0:
                pygame.time.wait(20) #Вот про таймер который я говорил в сообщении, он не особо спасает, но как временное решение сошёл
                self.velocity_y += self.steps
                self.steps -= 1
            self.steps = step_counter
        if keys[pygame.K_d]:
            while self.steps >= 0:
                pygame.time.wait(20) #Вот про таймер который я говорил в сообщении, он не особо спасает, но как временное решение сошёл
                self.velocity_x += self.steps
                self.steps -= 1
            self.steps = step_counter
        if keys[pygame.K_a]:
            while self.steps >= 0:
                pygame.time.wait(20) #Вот про таймер который я говорил в сообщении, он не особо спасает, но как временное решение сошёл
                self.velocity_x -= self.steps
                self.steps -= 1
            self.steps = step_counter
    def move(self):
        self.pos += pygame.math.Vector2(self.velocity_x, self.velocity_y)
    def update(self):
        self.user_input()
        self.move()