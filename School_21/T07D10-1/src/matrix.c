#include <stdio.h>
#include <stdlib.h>
#define NMAX 100

void print_array(const int *array, int size);
void print_array_dyn_int(int **array, int *rows, int size_x, int size_y);
void print_array_dyn_char(char **array, char *rows, int size_x, int size_y);
void print_array_dyn_double(double **array, double *rows, int size_x, int size_y);
int read_array(int *array, int size_x, int size_y);
int read_array_dyn_int(int **array, int *rows, int size_x, int size_y);
char read_array_dyn_char(char **array, char *rows, int size_x, int size_y);
double read_array_dyn_double(double **array, double *rows, int size_x, int size_y);
int first_case();
int second_case();
int third_case();
int fourth_case();

int main() {
    int n = 0;
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("n/a");
        return 0;
    } else if (n == 1){
        first_case();
    }else if (n == 2){
        second_case();
    }else if (n == 3){
        third_case();
    }else if (n == 4){
        fourth_case();
    }else{
        printf("n/a");
        return 0;
    }
    return 0;
}


int first_case()
{
    int x = 0;
    int y = 0;
    if (scanf("%d", &x) != 1 || x <= 0) {
        printf("n/a");
        return 0;
    }else{
        if (scanf("%d", &y) != 1 || y <= 0) {
            printf("n/a");
            return 0;
        }
        else
        {
            int array[NMAX][NMAX];
            if (!read_array(array, x, y))
            {
                printf("n/a\n");
                return 1;
            }
            print_array(array, x, y);
        }
}

int second_case()
{
    int x = 0;
    int y = 0;
    if (scanf("%d", &x) != 1 || x <= 0) {
        printf("n/a");
        return 0;
    }else{
        if (scanf("%d", &y) != 1 || y <= 0) {
            printf("n/a");
            return 0;
        }
        else
        {
            int **array;
            int *rows;
            table = calloc(y, sizeof(int*));
            rows = malloc(sizeof(int) * x);

            if (!read_array_dyn_int(*array, rows, x, y))
            {
                printf("n/a\n");
                return 1;
            }
            print_array_dyn_int(*array, rows, x, y);
            free(*array);
            free(rows);
        }
}

int third_case()
{
    int x = 0;
    int y = 0;
    if (scanf("%d", &x) != 1 || x <= 0) {
        printf("n/a");
        return 0;
    }else{
        if (scanf("%d", &y) != 1 || y <= 0) {
            printf("n/a");
            return 0;
        }
        else
        {
            char **array;
            char *rows;
            table = calloc(y, sizeof(char*)));
            rows = malloc(sizeof(char) * x);
            if (!read_array_dyn_char(array, rows, x, y))
            {
                printf("n/a\n");
                return 1;
            }
            print_array_dyn_char(array, rows, x, y);
            free(*array);
            free(rows);
        }
}

int fourth_case()
{
    int x = 0;
    int y = 0;
    if (scanf("%d", &x) != 1 || x <= 0) {
        printf("n/a");
        return 0;
    }else{
        if (scanf("%d", &y) != 1 || y <= 0) {
            printf("n/a");
            return 0;
        }
        else
        {
            double **array;
            double *rows;
            table = calloc(y, sizeof(double*)));
            rows = malloc(sizeof(double) * x);
            int array[NMAX][NMAX] = 0;
            if (!read_array_dyn_double(array, rows, x, y))
            {
                printf("n/a\n");
                return 1;
            }
            print_array_dyn_double(array, rows, x, y);
            free(*array);
            free(rows);
        }
}


void print_array(const int *array, int sizex, size_y) {
    for (int i = 0; i < size_x; i++) {
        for (int k = 0; k < size_y; k++){
            if (k < size_y){
            printf("%d ", array[k][i]);
            }
            else{
                printf("%d", array[k][i]);
            }
        }
        printf("\n");
    }
}

void print_array_dyn_int(int **array, int *rows, int size_x, int size_y)  {
    for (int i = 0; i < size_x; i++) {
        for (int k = 0; k < size_y; k++){
            if (k < size_y){
            printf("%d ", array[k][i]);
            }
            else{
                printf("%d", array[k][i]);
            }
        }
        printf("\n");
    }
}

char print_array_dyn_char(char **array, char *rows, int size_x, int size_y)  {
    for (int i = 0; i < size_x; i++) {
        for (int k = 0; k < size_y; k++){
            if (k < size_y){
            printf("%d ", array[k][i]);
            }
            else{
                printf("%d", array[k][i]);
            }
        }
        printf("\n");
    }
}

double print_array_dyn_double(double **array, double *rows, int size_x, int size_y)  {
    for (int i = 0; i < size_x; i++) {
        for (int k = 0; k < size_y; k++){
            if (k < size_y){
            printf("%d ", array[k][i]);
            }
            else{
                printf("%d", array[k][i]);
            }
        }
        printf("\n");
    }
}


int read_array(int *array, int size_x, int size_y) {
    for (int i = 0; i < size_x; i++) {
        for (int k = 0; k < size_y; k++){
            if (scanf("%d", &array[k][i]) != 1) {
                return 0;
            }
        }
    }
    return 1;
}

int read_array_dyn_int(int **array, int *rows, int size_x, int size_y) {
    for (int i = 0; i < size_x; i++) {
        for (int k = 0; k < size_y; k++){
            if (scanf("%d", &array[k][i]) != 1) {
                return 0;
            }
        }
    }
    return 1;
}

char read_array_dyn_char(char **array, char *rows, int size_x, int size_y) {
    for (int i = 0; i < size_x; i++) {
        for (int k = 0; k < size_y; k++){
            if (scanf("%d", &array[k][i]) != 1) {
                return 0;
            }
        }
    }
    return 1;
}

double read_array_dyn_double(double **array, double *rows, int size_x, int size_y) {
    for (int i = 0; i < size_x; i++) {
        for (int k = 0; k < size_y; k++){
            if (scanf("%d", &array[k][i]) != 1) {
                return 0;
            }
        }
    }
    return 1;
}

