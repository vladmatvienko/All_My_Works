//8th task//
//Имеется треугольник со сторонами а, b, с. Найти медианы треугольника, сторонами которого являются медианы исходного треугольника.
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
	if (A < B + C || B < A + C || C < A + B) {
		// Медианы исходного треугольника
		double M11 = 0.5 * (sqrt(2 * (pow(B, 2) + pow(C, 2)) - pow(A, 2)));
		double M12 = 0.5 * (sqrt(2 * (pow(A, 2) + pow(C, 2)) - pow(B, 2)));
		double M13 = 0.5 * (sqrt(2 * (pow(B, 2) + pow(A, 2)) - pow(A, 2)));
		// Медианы треугольника
		double M21 = 0.5 * (sqrt(2 * (pow(M13, 2) + pow(M12, 2)) - pow(M11, 2)));
		double M22 = 0.5 * (sqrt(2 * (pow(M13, 2) + pow(M11, 2)) - pow(M12, 2)));
		double M23 = 0.5 * (sqrt(2 * (pow(M11, 2) + pow(M12, 2)) - pow(M13, 2)));
		std::cout << "1Median = " << M21 << " 2Median = " << M22 << " 3Median = " << M23;
	}
	return 0;
}
