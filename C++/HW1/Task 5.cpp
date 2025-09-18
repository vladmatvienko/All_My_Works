//5th task//
//Выполнить переход от декартовых координат к полярным.

#include <iostream>
#include <cmath>
int main()
{
	double X = 0; //Координата Х
	double Y = 0; //Координата Y
	std::cout << "X = ";
	std::cin >> X;// Ввод X
	std::cout << "Y = ";
	std::cin >> Y;// Ввод Y
	double Ro = sqrt(pow(X, 2) + pow(Y, 2));//Полярный радиус
	double Fi = atan(Y / X);//Полярный угол
	std::cout << "polar coordinates equal to (" << Ro << ", " << Fi << ")"; //Вывод полярных координат
	return 0;
}
