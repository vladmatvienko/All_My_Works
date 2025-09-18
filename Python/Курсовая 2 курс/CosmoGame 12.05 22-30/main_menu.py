import pygame
import sys
import math

import Settings_game
from button import ImageButton
from title import *
from player import *
from field import *
from Board import *
from Settings_game import *
from State import *
from Sam_Stormtrooper import *
# Инициализация pygame
pygame.init()

# Параметры экрана
WIDTH, HEIGHT = 960, 600
MAX_FPS = 60;

screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Game")
main_background = pygame.image.load("main_menu.png")
clock = pygame.time.Clock()
my_sound = pygame.mixer.Sound("theme_menu_music2.mp3")
button_sound = pygame.mixer.Sound("click.mp3")


def main_menu():
    my_sound.play(-1)
    # Создание кнопок
    start_button = ImageButton(WIDTH / 2 - (252 / 2), 175, 252, 74, "Играть", "green_button.png",
                               "green_button_hover.png")
    settings_button = ImageButton(WIDTH / 2 - (252 / 2), 275, 252, 74, "Настройки", "green_button.png",
                                  "green_button_hover.png")
    exit_button = ImageButton(WIDTH / 2 - (252 / 2), 375, 252, 74, "Выход", "green_button.png",
                              "green_button_hover.png")
    music_button = ImageButton(WIDTH / 2 - (75 / 2) - 50, 475, 75, 75, "", "with_sound.png", "without_sound.png")
    system_button = ImageButton(WIDTH / 2 - (75 / 2) + 50, 475, 75, 75, "", "with_sys_mus.png", "without_sys_mus.png")
    running = True
    while running:
        screen.fill((0, 0, 0))

        screen.blit(main_background, (-480, 0))

        title("Dangeon survival", WIDTH / 2, 100, 72, screen, 0, 255, 0)

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
                pygame.quit()
                sys.exit()

            if event.type == pygame.USEREVENT and event.button == start_button:
                print("Кнопка 'Играть' была нажата!")
                fade(60)
                button_sound.play()
                game_sel()

            if event.type == pygame.USEREVENT and event.button == settings_button:
                print("Кнопка 'Настройки' была нажата!")
                button_sound.play()
                fade(60)
                settings_menu()

                if my_sound.get_volume() == 0:
                    music_button = ImageButton(WIDTH / 2 - (75 / 2) - 50, 475, 75, 75, "", "without_sound.png",
                                               "with_sound.png")
                else:
                    music_button = ImageButton(WIDTH / 2 - (75 / 2) - 50, 475, 75, 75, "", "with_sound.png",
                                               "without_sound.png")

                if button_sound.get_volume() == 0:
                    system_button = ImageButton(WIDTH / 2 - (75 / 2) + 50, 475, 75, 75, "", "without_sys_mus.png",
                                                "with_sys_mus.png")
                else:
                    system_button = ImageButton(WIDTH / 2 - (75 / 2) + 50, 475, 75, 75, "", "with_sys_mus.png",
                                                "without_sys_mus.png")

            if event.type == pygame.USEREVENT and event.button == exit_button:
                print("Кнопка 'Выход' была нажата!")
                button_sound.play()
                fade(60)
                exit_screen()

            if event.type == pygame.USEREVENT and event.button == music_button:
                if my_sound.get_volume() > 0:
                    my_sound.set_volume(0)
                    music_button = ImageButton(WIDTH / 2 - (75 / 2) - 50, 475, 75, 75, "", "without_sound.png",
                                               "with_sound.png")
                else:
                    my_sound.set_volume(1)
                    music_button = ImageButton(WIDTH / 2 - (75 / 2) - 50, 475, 75, 75, "", "with_sound.png",
                                               "without_sound.png")

            if event.type == pygame.USEREVENT and event.button == system_button:
                if button_sound.get_volume() > 0:
                    button_sound.set_volume(0)
                    system_button = ImageButton(WIDTH / 2 - (75 / 2) + 50, 475, 75, 75, "", "without_sys_mus.png",
                                                "with_sys_mus.png")
                else:
                    button_sound.set_volume(1)
                    system_button = ImageButton(WIDTH / 2 - (75 / 2) + 50, 475, 75, 75, "", "with_sys_mus.png",
                                                "without_sys_mus.png")

            for btn in [start_button, settings_button, exit_button, music_button, system_button]:
                btn.handle_event(event)

        for btn in [start_button, settings_button, exit_button, music_button, system_button]:
            btn.check_hover(pygame.mouse.get_pos())
            btn.draw(screen)

        pygame.display.flip()


def exit_screen():
    yes_button = ImageButton(WIDTH / 2 - (75 / 2) - 50, 250, 75, 75, "Да", "red_button.png", "red_button_hover.png")
    no_button = ImageButton(WIDTH / 2 - (75 / 2) + 50, 250, 75, 75, "Нет", "red_button.png", "red_button_hover.png")
    running = True
    while running:
        screen.fill((0, 0, 0))

        screen.blit(main_background, (-480, 0))

        title("Вы точно хотите выйти?", WIDTH / 2, 100, 52, screen, 0, 255, 0)

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
                pygame.quit()
                sys.exit()

            if event.type == pygame.KEYDOWN:
                # Возврат в меню
                if event.key == pygame.K_ESCAPE:
                    fade(60)
                    button_sound.play()
                    running = False

            if event.type == pygame.USEREVENT and event.button == yes_button:
                print("Кнопка 'Да' была нажата!")
                button_sound.play()
                running = False
                pygame.quit()
                sys.exit()

            if event.type == pygame.USEREVENT and event.button == no_button:
                print("Кнопка 'Нет' была нажата!")
                fade(60)
                button_sound.play()
                running = False

            for btn in [yes_button, no_button]:
                btn.handle_event(event)

        for btn in [yes_button, no_button]:
            btn.check_hover(pygame.mouse.get_pos())
            btn.draw(screen)

        pygame.display.flip()


def settings_menu():
    audio_button = ImageButton(WIDTH / 2 - (252 / 2), 175, 252, 74, "Аудио", "green_button.png",
                               "green_button_hover.png")
    video_button = ImageButton(WIDTH / 2 - (252 / 2), 275, 252, 74, "Видео", "green_button.png",
                               "green_button_hover.png")
    back_button = ImageButton(WIDTH / 2 - (252 / 2), 375, 252, 74, "Назад", "green_button.png",
                              "green_button_hover.png")
    running = True
    while running:
        screen.fill((0, 0, 0))

        screen.blit(main_background, (-480, 0))

        title("Настройки", WIDTH / 2, 100, 72, screen, 0, 255, 0)

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
                pygame.quit()
                sys.exit()

            if event.type == pygame.KEYDOWN:
                # Возврат в меню
                if event.key == pygame.K_ESCAPE:
                    button_sound.play()
                    fade(60)
                    running = False

            if event.type == pygame.USEREVENT and event.button == back_button:
                button_sound.play()
                print("Кнопка 'Назад' была нажата!")
                fade(60)
                running = False

            if event.type == pygame.USEREVENT and event.button == video_button:
                button_sound.play()
                fade(60)

            if event.type == pygame.USEREVENT and event.button == audio_button:
                button_sound.play()
                print("Кнопка 'Аудио' была нажата!")
                fade(60)
                volume_settings()

            for btn in [audio_button, video_button, back_button]:
                btn.handle_event(event)

        for btn in [audio_button, video_button, back_button]:
            btn.check_hover(pygame.mouse.get_pos())
            btn.draw(screen)

        pygame.display.flip()


def volume_settings():
    volume_in = my_sound.get_volume()
    click_volume_in = button_sound.get_volume()
    music_plus_button = ImageButton(WIDTH / 2 - (75 / 2) + 100, 220, 75, 75, "+", "red_button.png",
                                    "red_button_hover.png")
    music_minus_button = ImageButton(WIDTH / 2 - (75 / 2) - 100, 220, 75, 75, "-", "red_button.png",
                                     "red_button_hover.png")
    system_plus_button = ImageButton(WIDTH / 2 - (75 / 2) + 100, 380, 75, 75, "+", "red_button.png",
                                     "red_button_hover.png")
    system_minus_button = ImageButton(WIDTH / 2 - (75 / 2) - 100, 380, 75, 75, "-", "red_button.png",
                                      "red_button_hover.png")
    back_button = ImageButton(WIDTH / 2 - (252 / 2), 500, 252, 74, "Назад", "green_button.png",
                              "green_button_hover.png")
    running = True
    while running:
        volume_in_str = str(volume_in)
        click_volume_in_str = str(click_volume_in)
        screen.fill((0, 0, 0))

        screen.blit(main_background, (-480, 0))

        title("Настройки звука", WIDTH / 2, 100, 72, screen, 0, 255, 0)
        title("Музыка", WIDTH / 2, 180.5, 52, screen, 0, 255, 0)
        title(volume_in_str, WIDTH / 2, 254.5, 36, screen, 0, 255, 0)
        title("Система", WIDTH / 2, 344.5, 52, screen, 0, 255, 0)
        title(click_volume_in_str, WIDTH / 2, 414.5, 36, screen, 0, 255, 0)

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
                pygame.quit()
                sys.exit()

            if event.type == pygame.KEYDOWN:
                # Возврат назад
                if event.key == pygame.K_ESCAPE:
                    button_sound.play()
                    fade()
                    running = False

            if event.type == pygame.USEREVENT and event.button == music_plus_button:
                button_sound.play()
                print("Кнопка 'Звук музыки больше' была нажата!")
                if volume_in != 1:
                    volume_in = round(volume_in + 0.2, 1)

            if event.type == pygame.USEREVENT and event.button == music_minus_button:
                button_sound.play()
                print("Кнопка 'Звук музыки меньше' была нажата!")
                if volume_in != 0:
                    volume_in = round(volume_in - 0.2, 1)

            if event.type == pygame.USEREVENT and event.button == system_plus_button:
                button_sound.play()
                print("Кнопка 'Звук системы больше' была нажата!")
                if click_volume_in != 1:
                    click_volume_in = round(click_volume_in + 0.2, 1)

            if event.type == pygame.USEREVENT and event.button == system_minus_button:
                button_sound.play()
                print("Кнопка 'Звук системы меньше' была нажата!")
                if click_volume_in != 0:
                    click_volume_in = round(click_volume_in - 0.2, 1)

            if event.type == pygame.USEREVENT and event.button == back_button:
                button_sound.play()
                print("Кнопка 'Назад' была нажата!")
                fade(60)
                running = False

            for btn in [music_plus_button, music_minus_button, system_plus_button, system_minus_button, back_button]:
                btn.handle_event(event)

            my_sound.set_volume(volume_in)
            button_sound.set_volume(click_volume_in)

        for btn in [music_plus_button, music_minus_button, system_plus_button, system_minus_button, back_button]:
            btn.check_hover(pygame.mouse.get_pos())
            btn.draw(screen)

        pygame.display.flip()


def game_sel():
    # continue_button = ImageButton(WIDTH/2-(252/2), 175, 252, 74, "Продолжить", "green_button.png", "green_button_hover.png")
    new_game_button = ImageButton(WIDTH / 2 - (252 / 2), 175, 252, 74, "Новая игра", "green_button.png",
                                  "green_button_hover.png")
    back_button = ImageButton(WIDTH / 2 - (252 / 2), 450, 252, 74, "Назад", "green_button.png",
                              "green_button_hover.png")
    running = True
    while running:
        screen.fill((0, 0, 0))

        screen.blit(main_background, (-480, 0))

        title("Выберете продолжить или новая игра", WIDTH / 2, 100, 52, screen, 0, 252, 0)

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
                pygame.quit()
                sys.exit()

            if event.type == pygame.KEYDOWN:
                # Возврат в меню
                if event.key == pygame.K_ESCAPE:
                    fade(60)
                    button_sound.play()
                    running = False

            if event.type == pygame.USEREVENT and event.button == back_button:
                fade(60)
                button_sound.play()
                running = False

            if event.type == pygame.USEREVENT and event.button == new_game_button:
                print('Кнопка "Новая игра" была нажата!')
                fade(10)
                new_game()
                running = False

            for btn in [new_game_button, back_button]:
                btn.handle_event(event)

        for btn in [new_game_button, back_button]:
            btn.check_hover(pygame.mouse.get_pos())
            btn.draw(screen)

        pygame.display.flip()


player = Player(400, 300, 32, 32)
screen_scroll = [0, 0]
player_bullets = []


def new_game():
    file_board = open('board.txt', 'r+')
    screen = pygame.display.set_mode((WIDTH, HEIGHT), pygame.RESIZABLE)
    my_sound.stop()
    state = State()
    clock = pygame.time.Clock()
    board = Board(Settings_game.width, Settings_game.height, Settings_game.number_pers, Settings_game.number_enemy)

    sam = Sam_Stormtrooper()
    x1, y1 = 0, 0
    w, h = 0, 0
    change_w, change_h = 0, 0
    running = True
    back = pygame.image.load('back.jpg')
    while running:
        keys = pygame.key.get_pressed()
        if screen.get_width() != WIDTH:
            w = (screen.get_width() - WIDTH) / 50
        else:
            w = 0
        if screen.get_height() != HEIGHT:
            h = (screen.get_height() - HEIGHT) / 50
        else:
            h = 0

        for event in pygame.event.get():
            if event.type == pygame.MOUSEBUTTONDOWN and event.button == 1:
                board.click(event.pos, x1, y1)
                board.print_board()
            if event.type == pygame.QUIT:
                running = False
                pygame.quit()
                sys.exit()

        if keys[pygame.K_UP]:
            if y1 < 3:
                y1 += 1
        if keys[pygame.K_DOWN]:
            if y1 > -40.5 + h:
                y1 -= 1
        if keys[pygame.K_LEFT]:
            if x1 < 3:
                x1 += 1
        if keys[pygame.K_RIGHT]:
            if x1 > -33.6 + w:
                x1 -= 1

        screen.fill((255, 255, 255))
        screen.blit(back, (-480, 0))

        # title("Синий - плитка на которой нельзя находиться Зелёный - плитка на которойможно находиться Жёлтый - монетка",330, 20, 17, screen, 0, 0, 0)
        if screen.get_width() != change_w or screen.get_height() != change_h:
            x1, y1 = 0, 0
            change_w = screen.get_width()
            change_h = screen.get_height()
        board.render(screen, x1, y1)
        pygame.display.update()
        clock.tick(60)


def do_save():
    pass


def load_save():
    pass


def save_menu():
    pass


def fade(max_fps):
    screen.blit(main_background, (-480, 0))
    running = True
    fade_alpha = 0  # Уровень прозрачности для анимации
    while running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False

        # Анимирует затухающий экран
        fade_surface = pygame.Surface((WIDTH, HEIGHT))
        fade_surface.fill((0, 0, 0))
        fade_surface.set_alpha(fade_alpha)
        screen.blit(fade_surface, (0, 0))

        # Повышает прозрачность анимации
        fade_alpha += 5
        if fade_alpha >= 100:
            fade_alpha = 255
            running = False

        pygame.display.flip()
        clock.tick(max_fps)


if __name__ == "__main__":
    main_menu()


