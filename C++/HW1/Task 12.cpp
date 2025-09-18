//12th task//
//Дать рекомендации пользователю с известным ростом и весом похудеть или поправиться, если идеальный вес определяется формулой (рост - 100 = идеальный вес).
#include <iostream>
#include <cmath>
int main()
{
	double Weight = 0; //Вес
	double Height = 0; //Рост
	std::cout << "Your weight =  ";
	std::cin >> Weight;//Ввод веса
	std::cout << "Your height =  ";
	std::cin >> Height;//Ввод роста
	double ideal = Height - 100;// Идеальный вес
	//Рекомендации в зависимости от веса
	if (Weight < ideal)
		std::cout << "You should eat more!";
	else if (ideal == Weight)
		std::cout << "You Beautiful!";
	else if (Weight > ideal)
		std::cout << "You should start diet and go to the gym";
	return 0;
}
