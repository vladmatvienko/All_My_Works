//6th task//
//Выполнить переход от полярных координат к декартовым.

#include <iostream>
#include <cmath>
int main()
{
	double Ro = 0;//Полярный радиус
	double Fi = 0;//Полярный угол
	std::cout << "Ro = ";
	std::cin >> Ro;// Ввод X
	std::cout << "Fi = ";
	std::cin >> Fi;// Ввод Y
	double X = Ro*cos(Fi); //Координата Х
	double Y = Ro * sin(Fi); //Координата Y
	std::cout << "decart coordinates equal to (" << X << ", " << Y <<  ")"; //Вывод декартовых координат
	return 0;
}
