//13th task//
//Программа генерирует два случайных числа в диапазоне от 1 до 9. Тестируемый вводит результат произведения этих чисел. Программа сообщает тестируемому ошибся он или нет. 
//(Рандом по непонятной причине не работает) ＞﹏＜
#include <iostream>
#include <cmath>
#include <cstdlib>

int main()
{
	int Rand1 = 1 + std::rand() / ((RAND_MAX + 1u) / 9);//1st random number
	int Rand2 = 1 + std::rand() / ((RAND_MAX + 1u) / 9);//2nd random number
	std::cout << "How much " << Rand1 << " * " << Rand2 << std::endl;
	int Ans = 0;//Ответ
	std::cout << "Answer: ";
	std::cin >> Ans;//Ввод ответа
	//проверка на верность ответа
	if (Ans == Rand1 * Rand2) {
		std::cout << "Good Answer";
	}
	else {
		std::cout << "Bad Answer";
	}
	return 0;
}