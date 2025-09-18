//11th task//
//Вычислить стоимость покупки с учётом скидки. Скидка в 10% предоставляется, если сумма покупки превышает 1000 рублей.
#include <iostream>
#include <cmath>
int main()
{
	double sum = 0; //Сумма покупки
	std::cout << "Sum = ";
	std::cin >> sum;//Ввод Sum
        //проверка на скидку
	if (sum > 1000) {
		sum = sum * 0.9; //Скидка
		std::cout << "SALE!!!" << std::endl;
	}
	std::cout << "Cost = " << sum;

	return 0;
}
