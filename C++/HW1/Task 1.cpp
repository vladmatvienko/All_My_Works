//1st task//
//Вычислить площадь трапеции с основаниями b1 и b2 и высотой h

#include <iostream>

int main()
{
    float b1 = 0; //Основание 1
    float b2 = 0; //Основание 2
    float h = 0; //Высота
    std::cin >> b1; //Ввод b1
    std::cin >> b2; //Ввод b2
    std::cin >> h; //Ввод h
    float area = ((b1 + b2)/2)*h; // Счёт площади по формуле
    std::cout << "Площадь трапеции равна" << area; //Вывод площади
    return 0;
}
