//15th task//
//Ввести с клавиатуры номер месяца. Выдать сообщение о названии месяца и времени года.
#include <iostream>
#include <cmath>

int main()
{
	int Month = 0; //Номер месяца
	std::cout << "Number of month: ";
	std::cin >> Month;//Ввод месяца
        //Проверка на месяц
	if (Month == 1) {
		std::cout << "January winter";
	}
	else if(Month == 2) {
		std::cout << "February winter";
	}
	else if (Month == 3) {
		std::cout << "March spring";
	}
	else if (Month == 4) {
		std::cout << "April spring";
	}
	else if (Month == 5) {
		std::cout << "May spring";
	}
	else if (Month == 6) {
		std::cout << "June summer";
	}
	else if (Month == 7) {
		std::cout << "July summer";
	}
	else if (Month == 8) {
		std::cout << "August summer";
	}
	else if (Month == 9) {
		std::cout << "September fall";
	}
	else if (Month == 10) {
		std::cout << "October fall";
	}
	else if (Month == 11) {
		std::cout << "November fall";
	}
	else if (Month == 12) {
		std::cout << "December winter";
	}
	else {
		std::cout << "Not month";
	}

	return 0;
}