
// Задание 3
// #include <iostream>
//void zap(double **array) {
//	for (int i = 0; i < 5; i++) {
//		for (int k = 0; k < 5; k++) {
//			array[i][k] = 1 + rand() % (70 - 1 + 1);
//		}
//	}
//}
//void print(double** array) {
//	for (int i = 0; i < 5; i++) {
//		for (int k = 0; k < 5; k++) {
//			std::cout << array[i][k] << " ";
//			if (k == 4){
//				std::cout << "\n";
//			}
//		}
//	}
//}
//int main()
//{
//	double** array = new double* [5];
//	for (int i = 0; i < 5; i++) {
//		array[i] = new double[5];
//	}
//	zap(array);
//	print(array);
//	delete[]array;
//	return 0;
// }
// Задание 4
#include <iostream>
#include <string>
double add(double** array) {
	return 0;
}
double del(double** array) {
	return 0;
}
double update(double** array) {
	return 0;
}
double print(double** array) {
	for (int i = 0; i < 5; i++) {
		for (int k = 0; k < 5; k++) {
			std::cout << array[i][k] << " ";
			if (k == 4){
				std::cout << "\n";
			}
		}
	}
	return 0;
}
struct User
{
	int ID = 0;
	std::string FName = "";
	std::string SName = "";
	std::string Birthday = "";
};
int main() {
	std::cout << "instruction: 1-st number - UserID 2-nd number - birthyear \n Enter the action number: 1 - Adding an account, 2 - Deleting an account, 3 - Updating information, 4 - Displaying information about all accounts" << "\n";
	int act = 0;
	User* array = new User[2];
	array = { {1, "Andrey", "Petrov", "10.10.2002"}};
	
	


	while (act != 0) {
		std::cin >> act;
		if (act == 1) {
			fncPtr = add;
		}
		else if (act == 2) {
			fncPtr = del;
		}
		else if (act == 3) {
			fncPtr = update;
		}
		else if (act == 4) {
			fncPtr = print;
		}
		else {
			std::cout << "Invalid value";
		}
	}
	delete[]array;
	delete fncPtr;
	return 0;
	

}