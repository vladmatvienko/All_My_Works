//3rd task//
//Вычислить площадь прямоугольного треугольника и гипотенузу.

#include <iostream>

int main()
{
    double A = 0; //Сторона 1
    double B = 0; //Сторона 2
    std::cin >> A; //Ввод A
    std::cin >> B; //Ввод B
    double area = 0.5 * A * B;//Площадь прямоугольного треугольника
    double hyp =  sqrt(pow(A, 2) + pow(B, 2));//Гипотенуза прямоугольного треугольника
    std::cout << "The area of the triangle is equal to " << area << std::endl; //Вывод площади
    std::cout << "The hypotenuse of the triangle is equal to " << hyp; //Вывод гипотенузы
    return 0;
}
