//9th task//
//Идет k-я секунда суток. Определить, сколько целых часов и целых минут прошло с начала суток.
#include <iostream>
#include <cmath>
int main()
{
	int k = 0; //Секунда суток
	std::cout << "K = ";
	std::cin >> k;
	int Hour = 0; //часов прошло с начала суток
	int Minute = 0;//минут прошло с начала суток
	//счёт часов
	while (k >= 3600) {
		Hour += 1;
		k -= 3600;
	}
	while (k > 0) {
		Minute += 1;
		k -= 60;
	}
	std::cout << Hour << " Hours " << Minute << " minutes" << " have passed since the beginning of the day";
	return 0;
}
