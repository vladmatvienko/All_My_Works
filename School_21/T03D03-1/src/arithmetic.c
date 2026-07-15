#include <stdio.h>

int sum(int a, int b);
int mul(int a, int b);
int minus(int a, int b);
int div(int a, int b);

int main()
{
    float x, y;
    scanf("%f %f", &x, &y);
    if (x == (int)x){
        if (y == (int)y){
            sum(x, y);
            minus(x,y);
            mul(x, y);
            div(x,y);
        }
        else
        printf("n/a ");
    }
    else
        printf("n/a ");

    return 0;
}

int sum(int a, int b){
    printf("%d ", a+b);
    return 0;
}

int mul(int a, int b){
    printf("%d ", a*b);
    return 0;
}

int minus(int a, int b){
    printf("%d ", a-b);
    return 0;
}

int div(int a, int b){
    float answ;
    if (a<0 || b<=0)
        printf("n/a ");
    else{
        answ = a/b;
        if (answ == (int)answ )
            printf("%d ", a/b);
        else
            printf("n/a ");
    }

    return 0;
}
