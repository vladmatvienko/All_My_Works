//10th task//
//Определить, является ли треугольник со сторонами a, b, c равнобедренным.
#include <iostream>
#include <cmath>
int main()
{
	double A = 0; //Сторона A
	double B = 0; //Сторона B
	double C = 0; //Сторона C
	std::cout << "A = ";
	std::cin >> A;// Ввод A
	std::cout << "B = ";
	std::cin >> B;// Ввод B
	std::cout << "C = ";
	std::cin >> C;// Ввод C
	if (A < B + C || B < A + C || C < A + B) {//проверка на то треугольник ли это
		if (A == B || A == C || C == B)//проверка на равнобедренность
			std::cout << "The triangle is isosceles";
		else
			std::cout << "The triangle is no isosceles";
	}
	else
		std::cout << "The not triangle";
	return 0;
}
