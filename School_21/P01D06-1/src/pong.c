// I WANT TO PLAY WITH YOU
//         YOUR FRIEND, AI
#include <stdio.h>

int ball_update_direction(int ballX, int ballY, int ballDirection, int left_rackY, int right_rackY,
                          int left_rackX, int right_rackX);
int change_direction_wall(int ballDirection);
int step_X(int ballX, int ballDirection);
int step_Y(int ballY, int ballDirection);
int change_direction_rack(int ballDirection);
void draw_map(char const game[27][82]);
void shrek();
void cat();

int main() {
    char map[27][82];  // start condition of map

    for (int i = 0; i <= 26; i++) {
        for (int k = 0; k <= 81; k++) {
            if (i == 0 || i == 26) {
                map[i][k] = '_';
            }

            else if (k == 0 || k == 81 || k == 40) {
                map[i][k] = '|';
            }

            else {
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

    int score_pl_1, score_pl_2;
    score_pl_1 = 0;
    score_pl_2 = 0;

    char check_latter = 'c';

    char ball = 'O';
    int ballX, ballY, ballDirection;
    ballX = 40;
    ballY = 13;
    ballDirection = 45;

    char left_rack = ']';
    char right_rack = '[';

    int left_rackX, right_rackX;
    left_rackX = 1;
    right_rackX = 80;

    int left_rackY, right_rackY;
    left_rackY = 13;
    right_rackY = 13;

    while (check_latter != 'q' && (score_pl_1 != 21 && score_pl_2 != 21)) {
        int key = 0;

        for (int i = 0; i <= 26; i++) {
            for (int k = 0; k <= 81; k++) {
                game[i][k] = map[i][k];
            }
        }

        for (int i = left_rackY - 1; i <= left_rackY + 1; i++) {
            game[i][left_rackX] = left_rack;
        }

        for (int i = right_rackY - 1; i <= right_rackY + 1; i++) {
            game[i][right_rackX] = right_rack;
        }

        game[ballY][ballX] = ball;

        draw_map(game);

        // start of the game
        // must be space

        if (ballX >= 81 || ballX <= 0) {
            if (ballX >= 81) score_pl_1++;
            if (ballX <= 0) score_pl_2++;
            printf("Счет: Игрок 1 - %d, Игрок 2 - %d\n", score_pl_1, score_pl_2);
            if (score_pl_1 == 21) {
                printf("Поздравляем! Игрок 1 победил с %d очками!\n", score_pl_1);
                shrek();
            } else if (score_pl_2 == 21) {
                printf("Поздравляем! Игрок 2 победил с %d очками!\n", score_pl_2);
                cat();
            }
            ballX = 40;
            ballY = 13;
        } else {
            ballDirection = ball_update_direction(ballX, ballY, ballDirection, left_rackY, right_rackY,
                                                  left_rackX, right_rackX);

            ballX = step_X(ballX, ballDirection);
            ballY = step_Y(ballY, ballDirection);
        }

        key = 0;
        printf("ENTER A/Z to move left racket  or space to pass the step!\n");
        while (key == 0 && check_latter != ' ') {
            scanf("%c", &check_latter);
            if (check_latter == 'a' && left_rackY >= 3) {
                left_rackY = left_rackY - 1;
                key = 1;
            } else if (check_latter == 'z' && left_rackY <= 23) {
                left_rackY = left_rackY + 1;
                key = 1;
            }
        }

        draw_map(game);
        check_latter = 'u';
        key = 0;

        printf(
            "ENTER K/M to move right racket or space to pass the step or q for "
            "quit!\n");
        while (key == 0 && check_latter != ' ' && check_latter != 'q') {
            scanf("%c", &check_latter);
            if (check_latter == 'k' && right_rackY >= 3) {
                right_rackY = right_rackY - 1;
                key = 1;
            } else if (check_latter == 'm' && right_rackY <= 23) {
                right_rackY = right_rackY + 1;
                key = 1;
            }
        }
        scanf("%c", &check_latter);
    }
    // scanf("%c", &check_latter);

    return 0;
}

int ball_update_direction(int ballX, int ballY, int ballDirection, int left_rackY, int right_rackY,
                          int left_rackX, int right_rackX) {
    // vertical wall rebound
    if (ballY >= 25 || ballY <= 1) {
        ballDirection = change_direction_wall(ballDirection);
    }

    // touch racket
    else if (((ballY <= left_rackY + 1 || ballY >= left_rackY - 1) ||
              (ballY <= right_rackY + 1 || ballY >= right_rackY - 1)) &&
             (ballX == left_rackX || ballX == right_rackX)) {
        if (ballY == left_rackY && ballX == left_rackX)
            ballDirection = 180;
        else if (ballY == right_rackY && ballX == right_rackX)
            ballDirection = 0;
        else if (ballY == right_rackY - 1)
            ballDirection = 45;  // up part right
        else if (ballY == right_rackY + 1)
            ballDirection = 315;  // down part right
        else if (ballY == left_rackY - 1)
            ballDirection = 135;  // up part left
        else if (ballY == left_rackY + 1)
            ballDirection = 225;  // down part left
    }

    return ballDirection;
}

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

int step_Y(int ballY, int ballDirection) {
    if (ballDirection == 45 || ballDirection == 135) ballY--;
    if (ballDirection == 315 || ballDirection == 225) ballY++;
    return ballY;
}

void draw_map(char const game[27][82]) {
    for (int i = 0; i <= 26; i++) {
        for (int k = 0; k <= 81; k++) {
            printf("%c", game[i][k]);
        }

        printf("\n");
    }
};
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
