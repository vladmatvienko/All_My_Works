#include <iostream>
#include <cmath>
struct dot
{
    int x;
    int y;
};
struct triangle
{
    dot d1;
    dot d2;
    dot d3;
};
int getSide(dot d1, dot d2) {
    return sqrt(pow((d1.x - d2.x), 2) + pow((d1.y - d2.y), 2));
}
int getS(triangle tr) {
    int Side1 = getSide(tr.d1, tr.d2);
    int Side2 = getSide(tr.d2, tr.d3);
    int Side3 = getSide(tr.d3, tr.d1);
    int p = (Side1 + Side2 + Side3) / 2;
    return sqrt(p * (p - Side1) * (p - Side2) * (p - Side3));
}

int main() {
    triangle trs[4] =
    {
        {{1,6},{2,8},{3,0}},
        {{2,7},{3,7},{9,4}},
        {{3,8},{4,6},{5,8}},
        {{4,9},{5,5},{7,6}}
    };
    int MAXINDEX = 0;
    int MAXS = 0;
    for (int i = 0; i < 4; i++) {
        if (getS(trs[i]) > MAXS) {
            MAXS = getS(trs[i]);
            MAXINDEX = i;
        }
    }
    std::cout << "Индекс самого большого треугольника = " << MAXINDEX << "Его площадь = " << MAXS;
    return 0;
}
