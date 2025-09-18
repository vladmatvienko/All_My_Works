import pygame
import math
from Player import *
from settings import *

pygame.init()

screen = pygame.display.set_mode((screen_width, screen_height))
pygame.display.set_caption('Название в разработке')

#icon = pygame.image.load('P0S1T1V.jpg')
#pygame.display.set_icon(icon)

clock = pygame.time.Clock()

background = pygame.transform.scale(pygame.image.load('map.png').convert(), (screen_width, screen_height))

player = Player()
while True:
    keys = pygame.key.get_pressed()

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            exit()

    screen.blit(background, (0,0))
    screen.blit(player.image, player.pos)
    player.update()

    pygame.display.update()
    clock.tick(FPS)