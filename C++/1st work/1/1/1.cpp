//Task 1/
	//for (int i = 1; i <= 20; i++) {
	//	std::cout << i << "Duim = " << i * 2 << "Santimeter" << std::endl;
	//}
//Task 2/
//    std::cout << "Numbers that equal 5: ";
//for (int i = 2; i <= 100; i++) {
	//if (i % 5 == 0) {
		//std::cout << i << " ";
//Task 4/
//int Sum = 1;
//for (int i = 1; i <= 10; i = i++) {
	//Sum = Sum + pow(2, i);
	//std::cout << Sum << std::endl;
//}
//Task 10/
//Найти все числа кратные семи, сумма цифр которых которых также кратна семи.
#include <iostream>
#include <cmath>
int main() {
	for (int i = 1; i <= 100000; i++) {
		int Answer = i;
		int Answer1 = i;
		if (Answer%7 == 0){
			int g = 0;
			int a = 0;
			while (Answer1 != 0) {
				g = Answer1 % 10;
				a = g + a;
				Answer1 = Answer1 / 10;
			}
			if (a % 7 == 0) {
				std::cout << Answer << std::endl;
			}
				
		}
	}
}
