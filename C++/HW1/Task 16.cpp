//16th task//
//Определить, является ли шестизначное число "счастливым"
//Буду подразумевать что счастливое число это то, у которого совпадают все числа (*^▽^*)


#include <iostream>
#include <cmath>

int main()
{
	int Num = 0; //Число
	std::cin >> Num;//Ввод числа
	double Sum = 0;//Переменная суммы
	double A = 0;// Число которое пригодится нам потом
	double B = 0;//Счётчик кол-ва чисел
	while (Num != 0) {// пока число не станет равно нулём
		A = Num % 10; //Вытаскиваем число
		Sum = A + Sum; //Добавляем число в сумму
		Num = Num / 10; // Убираем введённое число
		B += 1;
	}
	//проверка на кол-во символов
	if (B == 6) {
		//условие счастливого числа
		if (Sum / B == A)
			std::cout << "Lucky number";
		else
			std::cout << "Not lucky number";
	}
	else
		std::cout << "The number is not six digits";
	

	return 0;
}