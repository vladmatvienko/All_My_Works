//2nd task//
//Вычислить длину окружности и площадь круга радиуса r

#include <iostream>
#include <cmath>
int main()
{
    float r = 0; //Радиус круга
    const float pi = 3.14;//Число пи (неизменяемое)
    std::cout << "The radius of the circle is equal to ";
    std::cin >> r; //Ввод r
    float area = pi*pow(r,2); // Счёт площади по формуле
    float length = 2*pi*r; // Счёт длины по формуле
    std::cout << "The area of the circle is equal to " << area << std::endl; //Вывод площади
    std::cout << "The length of the circle is equal to " << length; //Вывод длины
    return 0;
}
