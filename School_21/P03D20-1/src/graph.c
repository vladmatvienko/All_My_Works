
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//Не забудьте про clang-format, cppcheck и valgrind!!!!!!!!!!!!!!!!!
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

#include "stack.h"
//include "polish_notation.h" Надо сделать.
#include <stdio.h>
#include <stdlib.h>

int x_g = 80;
int y_g = 25;

void create_graph(char **graph);
void output(char **graph);
void delete(char **graph);
void input_dots(char **graph, char *mem_pol_not);
void replace_x (char *pol_not);

int main() {

    char **graph = calloc(y_g, sizeof(char *));

    for (int i = 0; i < y; i++) {
        graph[i] = malloc(x_g * sizeof(char));

    }

    char expression[256];
    printf("Введите выражение: ");
    fgets(expression, sizeof(expression), stdin);
    expression[strcspn(expression, "\n")] = '\0';

    char mem_pol_not[256] = polish_notation(expression); // Создание польской нотации


    if (mem_pol_not[0] == 'E'){ // Проверка на корректность. надо будет сделать, если в выражении ошибка/недопустимые символы будет в переменной mem_pol_not[0] будет 'E'
        printf("Error");
    }
    else
    {
        create_graph(graph);
        input_dots(graph, mem_pol_not);
        output(graph);
        delete(graph);
    }





    return 0;
}



void create_graph(char **graph)
{
    for (int i = 0; i < y_g; i++) {
        for (int k = 0; k < x_g; k++) {
            graph[i][k] = '.';
        }
    }
}

void output(char **graph)
{
    for (int i = 0; i < y_g; i++) {
        for (int k = 0; k < x_g; k++) {
            printf("%c", graph[i][k]);
        }
        printf("\n");
    }
}


void delete(char **graph)
{
     for (int i = 0; i < y_g; i++) {
        free(graph[i]);
    }
    free(graph);
}

void input_dots(char **graph, char *mem_pol_not)
{
    double x_pol_not = 0;
    for (int x = 0; x < x_g)
    {
        char pol_not[256] = mem_pol_not;

        replace_x (pol_not);

        double answer = count_polish_notation(pol_not);
        if (answer < 0)
        {

        }
        for (int i = 0; i < ; i++)
    }
}

void replace_x (char *pol_not)
{
    for (int i = 0; i < strlen(pol_not); i++)
        {
            if(pol_not[i] == "x")
            {
                pol_not[i] = x_pol_not;
                x_pol_not = x_pol_not + M_PI/20;
            }
        }
}
