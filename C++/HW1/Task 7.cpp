//7th task//
//Найти корни квадратного уравнения. aX^2+bX+c=0

#include <iostream>
#include <cmath>
int main()
{
	double A = 0; //Параметр A
	double B = 0; //Параметр B
	double C = 0; //Параметр C
	std::cout << "A = ";
	std::cin >> A;// Ввод A
	std::cout << "B = ";
	std::cin >> B;// Ввод B
	std::cout << "C = ";
	std::cin >> C;// Ввод C
	double Dis = pow(B, 2) - (4 * A * C); // Дискриминант
	// Проверка дискриминанта
	if (Dis > 0) {
		double X1 = (-B - sqrt(Dis)) / 2*A; //Корень X1
		double X2 = (-B + sqrt(Dis)) / 2*A; //Корень X2
		std::cout << "X1 = " << X1 << "; X2 = " << X2; // Вывод X1 X2
		}
	if (Dis == 0) {
		double X12 = (- B) / 2*A; //Корень X12
		std::cout << "X12 = " << X12; // Вывод X12 
	}
	if (Dis < 0) {
		std::cout << "There is no solution, the discriminant is less than 0"; // Вывод Ошибки 
	}
	return 0;
}
