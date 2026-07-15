aa#include <fcntl.h>  // Для FIONREAD
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>  // Для ioctl
#include <termios.h>
#include <unistd.h>

#define DELAY 550000000  // Задержка для контроля скорости игры

// Функция для установки неблокирующего режима ввода
void set_nonblocking_input(int enable) {
    static struct termios oldt, newt;
    if (enable) {
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);  // Отключаем канонический режим и эхо
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    } else {
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);  // Восстанавливаем старые настройки
    }
}

int kbhit() {
    int bytes_waiting;
    ioctl(STDIN_FILENO, FIONREAD, &bytes_waiting);  // Проверяем наличие данных в stdin
    return bytes_waiting;
}

char getch() {
    char buf = 0;
    read(STDIN_FILENO, &buf, 1);  // Считываем один символ
    return buf;
}

int ball_update_direction(int ballX, int ballY, int ballDirection, int left_rackY, int right_rackY,
                          int left_rackX, int right_rackX);
int change_direction_wall(int ballDirection);
int step_X(int ballX, int ballDirection);
int step_Y(int ballY, int ballDirection);
void draw_map(char const game[27][82], int score_pl_1, int score_pl_2);
void shrek();
void cat();

int main() {
    char map[27][82];  // Начальное состояние карты

    for (int i = 0; i <= 26; i++) {
        for (int k = 0; k <= 81; k++) {
            if (i == 0 || i == 26) {
                map[i][k] = '_';
            } else if (k == 0 || k == 81 || k == 40) {
                map[i][k] = '|';
            } else {
                map[i][k] = ' ';
            }
        }
    }

    char game[27][82];

    for (int i = 0; i <= 26; i++) {
        for (int k = 0; k <= 81; k++) {
            game[i][k] = map[i][k];
        }
    }

    int score_pl_1 = 0, score_pl_2 = 0;

    char ball = 'O';
    int ballX = 40, ballY = 13, ballDirection = 45;

    char left_rack = ']', right_rack = '[';
    int left_rackX = 1, right_rackX = 80;
    int left_rackY = 13, right_rackY = 13;

    set_nonblocking_input(1);  // Включаем неблокирующий ввод

    while (score_pl_1 != 21 && score_pl_2 != 21) {
        // Очистка поля
        for (int i = 0; i <= 26; i++) {
            for (int k = 0; k <= 81; k++) {
                game[i][k] = map[i][k];
            }
        }

        // Рисование ракеток
        for (int i = left_rackY - 1; i <= left_rackY + 1; i++) {
            game[i][left_rackX] = left_rack;
        }

        for (int i = right_rackY - 1; i <= right_rackY + 1; i++) {
            game[i][right_rackX] = right_rack;
        }

        // Рисование мяча
        game[ballY][ballX] = ball;

        // Вывод поля
        draw_map(game, score_pl_1, score_pl_2);

        // Проверка состояния игры
        if (ballX >= 81 || ballX <= 0) {
            if (ballX >= 81) score_pl_1++;
            if (ballX <= 0) score_pl_2++;

            ballX = 40;
            ballY = 13;
            ballDirection = 45;
        } else {
            // Обновление направления мяча
            ballDirection = ball_update_direction(ballX, ballY, ballDirection, left_rackY, right_rackY,
                                                  left_rackX, right_rackX);

            // Движение мяча
            ballX = step_X(ballX, ballDirection);
            ballY = step_Y(ballY, ballDirection);
        }

        // Обработка управления ракетками
        if (kbhit()) {           // Проверка наличия ввода
            char key = getch();  // Считываем символ
            if (key == 'a' && left_rackY > 2) {
                left_rackY--;
            } else if (key == 'z' && left_rackY < 24) {
                left_rackY++;
            } else if (key == 'k' && right_rackY > 2) {
                right_rackY--;
            } else if (key == 'm' && right_rackY < 24) {
                right_rackY++;
            } else if (key == 'q') {
                printf("Игра завершена.\n");
                break;
            }
        }

        // Задержка для контроля скорости игры
        for (volatile int i = 0; i < DELAY; i++);
    }
    if (score_pl_1 == 21) {
        printf("Поздравляем! Игрок 1 победил с %d очками!\n", score_pl_1);
        shrek();
    } else if (score_pl_2 == 21) {
        printf("Поздравляем! Игрок 2 победил с %d очками!\n", score_pl_2);
        cat();
    }
    set_nonblocking_input(0);  // Возвращаем стандартный режим ввода

    return 0;
}

// Функция обновления направления мяча
int ball_update_direction(int ballX, int ballY, int ballDirection, int left_rackY, int right_rackY,
                          int left_rackX, int right_rackX) {
    if (ballY >= 25 || ballY <= 1) {
        ballDirection = change_direction_wall(ballDirection);
    } else if (((ballY <= left_rackY + 1 || ballY >= left_rackY - 1) ||
                (ballY <= right_rackY + 1 || ballY >= right_rackY - 1)) &&
               (ballX == left_rackX || ballX == right_rackX)) {
        if (ballY == left_rackY && ballX == left_rackX)
            ballDirection = 180;
        else if (ballY == right_rackY && ballX == right_rackX)
            ballDirection = 0;
        else if (ballY == right_rackY - 1)
            ballDirection = 45;  // Верхняя часть правой ракетки
        else if (ballY == right_rackY + 1)
            ballDirection = 315;  // Нижняя часть правой ракетки
        else if (ballY == left_rackY - 1)
            ballDirection = 135;  // Верхняя часть левой ракетки
        else if (ballY == left_rackY + 1)
            ballDirection = 225;  // Нижняя часть левой ракетки
    }

    return ballDirection;
}

// Изменение направления от стенки
int change_direction_wall(int ballDirection) {
    if (ballDirection == 45)
        ballDirection = 315;
    else if (ballDirection == 135)
        ballDirection = 225;
    else if (ballDirection == 225)
        ballDirection = 135;
    else if (ballDirection == 315)
        ballDirection = 45;
    return ballDirection;
}

// Шаг по X
int step_X(int ballX, int ballDirection) {
    if (ballDirection == 45 || ballDirection == 315)
        ballX--;
    else if (ballDirection == 135 || ballDirection == 225)
        ballX++;
    else if (ballDirection == 180)
        ballX++;
    else if (ballDirection == 0)
        ballX--;
    return ballX;
}

// Шаг по Y
int step_Y(int ballY, int ballDirection) {
    if (ballDirection == 45 || ballDirection == 135)
        ballY--;
    else if (ballDirection == 315 || ballDirection == 225)
        ballY++;
    return ballY;
}

// Отображение игрового поля
void draw_map(char const game[27][82], int score_pl_1, int score_pl_2) {
    for (int i = 0; i <= 26; i++) {
        for (int k = 0; k <= 81; k++) {
            printf("%c", game[i][k]);
        }
        printf("\n");
    }
    printf("Счет: Игрок 1 - %d, Игрок 2 - %d\n", score_pl_1, score_pl_2);
}

// ASCII-art для Shrek
void shrek() {
    printf("⡴⠑⡄⠀⠀⠀⠀⠀⠀⠀⣀⣀⣤⣤⣤⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠸⡇⠀⠿⡀⠀⠀⠀⣀⡴⢿⣿⣿⣿⣿⣿⣿⣷⣦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠑⢄⣠⠾⠁⣀⣄⡈⠙⣿⣿⣿⣿⣿⣿⣿⣆⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⢀⡀⠁⠀⠀⠈⠙⠛⠂⠈⣿⣿⣿⣿⣿⠿⡿⢿⣆⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⢀⡾⣁⣀⠀⠴⠂⠙⣗⡀⠀⢻⣿⣿⠭⢤⣴⣦⣤⣹⠀⠀⠀⢀⢴⣶⣆\n");
    printf("⠀⠀⢀⣾⣿⣿⣿⣷⣮⣽⣾⣿⣥⣴⣿⣿⡿⢂⠔⢚⡿⢿⣿⣦⣴⣾⠁⠸⣼⡿\n");
    printf("⠀⢀⡞⠁⠙⠻⠿⠟⠉⠀⠛⢹⣿⣿⣿⣿⣿⣌⢤⣼⣿⣾⣿⡟⠉⠀⠀⠀⠀\n");
    printf("⠀⣾⣷⣶⠇⠀⠀⣤⣄⣀⡀⠈⠻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⠀⠀⠀⠀\n");
    printf("⠀⠉⠈⠉⠀⠀⢦⡈⢻⣿⣿⣶⣶⣶⣶⣤⣽⡹⣿⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠉⠲⣽⡻⢿⣿⣿⣿⣿⣿⣿⣷⣜⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⣷⣶⣮⣭⣽⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⣀⣀⣈⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠇⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠃⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠟⠁⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠉⠛⠻⠿⠿⠿⠿⠛⠉\n");
}

// ASCII-art для кота
void cat() {
    printf("／ﾌﾌ 　　　　　　　　　　　　ム｀ヽ\n");
    printf("/ ノ)　　 ∧　　∧　　　）　ヽ\n");
    printf("/ ｜　　(´・ω ・`）ノ⌒（ゝ._,ノ\n");
    printf("/　ﾉ⌒＿⌒ゝーく　 ＼　　／\n");
    printf("丶＿ ノ 　　 ノ､　　|　/\n");
    printf("　　 `ヽ `ー-‘人`ーﾉ /\n");
    printf("　　　 丶 ￣ _人’彡ﾉ\n");
    printf("　　　／｀ヽ _/\\__'\n");
}
