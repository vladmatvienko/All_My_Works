import pygame
from enum import Enum

class State(Enum):
    MENU = 0,
    START = 1,
    CONTINUE = 2,
    QUIT = 3
    
class GameStat:
    def __init__(self):
        self.state = State.MENU
        
    def change(self, stat):
        self.stat = stat