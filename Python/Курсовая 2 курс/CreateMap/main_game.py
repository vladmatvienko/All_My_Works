from Title import *
from Board import *
from Settings import *
from Visibility_area import *
pygame.init()

screen = pygame.display.set_mode((screen_width, screen_height), pygame.RESIZABLE)
pygame.display.set_caption('Map_editor')

#icon = pygame.image.load('P0S1T1V.jpg')
#pygame.display.set_icon(icon)

clock = pygame.time.Clock()


board = Board(50, 50, 4, 6)

visibility_area = visibility_area(50, 50)

while True:

    keys = pygame.key.get_pressed()

    for event in pygame.event.get():

        if event.type == pygame.MOUSEBUTTONDOWN and event.button == 1:
            board.click(event.pos)
            board.print_board()
        if event.type == pygame.QUIT:
            pygame.quit()
            exit()

    screen.fill((255,255,255))

    #title("Синий - плитка на которой нельзя находиться Зелёный - плитка на которойможно находиться Жёлтый - монетка",330, 20, 17, screen, 0, 0, 0)

    board.render(screen)
    pygame.display.flip()
    pygame.display.update()
    clock.tick(FPS)
