//1)
//1.1 Объявить константный указатель на константу типа float.
//1.2.Объявить тип указателя на long int.
//1.3.Объявить указатель на double.
//1.4.Объявить указатель на константу типа short int.
//1.5.Объявить тип константного указателя на константу типа float.
//1.6.Объявить тип указателя на константу типа char.
//1.7.Объявить константный указатель на double.
//1.8.Объявить тип константного указателя на unsigned int.
//#include <iostream>
//
//int main()
//{
//    const float a = 5;
//    const float *const ptr1 = &a;
//
//    typedef long int * Biba;
//
//    double b = 5;
//    double *ptr2 = &b;
//
//    const short int c = 5;
//    const short int *ptr3 = &c;
//
//    typedef const float *const Bubble;
//
//    typedef const char * Boba;
//
//    double d = 5;
//    double *const ptr4 = &d;
//
//    typedef unsigned int* const LALALALALALA_VSYO_BUDET_HOROSHO;
//
//    return 0;
//}
//объявить тип - typedef

//2) Объявите указатель на массив типа double и предложите пользователю выбрать его размер.Далее напишите четыре функции :
//первая должна выделить память для массива,
//вторая – заполнить ячейки данными, 
//третья – показать данные на экран, 
//четвертая – освободить занимаемую память.
//Программа должна предлагать пользователю продолжать работу(создавать новые динамические массивы) или выйти из программы.
//#include <iostream>
//double *fun1(int a) {
//	double* array = new double[a];
//	return array;
//}
//void fun2(int a, double *array) {
//	int b = 0;
//		while (b < a) {
//			array[b] = b;
//			b++;
//	}
//}
//void fun3(int a, double* array) {
//	for (int i = 0; i < a; i++)
//		std::cout << array[i] << " ";
//	std::cout << std::endl;
//}
//void fun4(double* array) {
//	delete []array;
//}
//
//int main() {
//	int a = 0;
//	while (a != -1) {
//		std::cout << "Write length massive:  ";
//		std::cin >> a;
//		double* array = fun1(a);
//		fun2(a, array);
//		fun3(a, array);
//		fun4(array);
//	}
//	return 0;
//}
//3) Объявите указатель на массив типа int и выделите память память для 12 - ти элементов.
//Необходимо написать функцию, которая поменяет значения четных и нечетных ячеек массива.
//#include <iostream>
//void fun1(int* array) {
//	for (int i = 0; i < 12; i = i + 2) {
//		int b = i + 1;
//		int c = array[i];
//		array[i] = array[b];
//		array[b] = c;
//	}
//
//}
//int main() {
//	int* array = new int[12] {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
//	for (int i = 0; i < 12; i++)
//	    std::cout << array[i] << " ";
//	fun1(array);
//	for (int i = 0; i < 12; i++)
//		std::cout << array[i] << " ";
//	delete []array;
//}
//________________________________________БЫЛО ПОКАЗАННО В КЛАССЕ_____________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________
//
// 
// _______________________________________________ДЗ:____________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________
// 4) Объявить и заполнить двумерный динамический массив случайными числами от 10 до 50. 
// Показать его на экран. 
// Для заполнения и показа на экран написать отдельные функции. 
// (подсказка: функции должны принимать три параметра – указатель на динамический массив, количество строк, количество столбцов). 
// Количество строк и столбцов выбирает пользователь. 
//#include <iostream>
//void vvod(int** array, int columns, int rows) {//Функция ввода рандомного числа
//	for (int i = 0; i < columns; i++) {
//		for (int k = 0; k < rows; k++) {
//			int start = 10;
//			int end = 50;
//			int x = rand() % (end - start + 1) + start; //рандомное число
//			array[i][k] = x;
//		}
//	}
//}
//void out(int** array, int columns, int rows) {//Функция вывода массива
//	std::cout << "{";
//	for (int i = 0; i < columns; i++) {
//		std::cout << "{";
//		for (int k = 0; k < rows; k++) {
//			if (k < rows - 1)
//				std::cout << array[i][k] << ", ";
//			else
//				std::cout << array[i][k];
//		}
//		if (i < columns - 1)
//			std::cout << "}, ";
//		else
//			std::cout << "}";
//	}
//	std::cout << "}";
//}
//int main() {
//	int columns = 0;
//	int rows = 0;
//	while (columns != -1) {
//		std::cout << "Write the number of columns and rows" << "\n";
//		std::cout << "Columns: ";
//		std::cin >> columns;
//		std::cout << "Rows: ";
//		std::cin >> rows;
//		int** array = new int* [columns];
//		for (int i = 0; i < columns; i++) {
//			array[i] = new int[rows];
//		}
//		vvod(array, columns, rows);
//		out(array, columns, rows);
//		std::cout << "\n";
//		delete[]array;
//	}
//	return 0;
//}
// Решите задачу, используя один указатель на функцию.
// Разработайте четыре функции над двумя целыми параметрами, соответствующие арифметическим операциям (+, -, *, /).
// В основной программе задавайте два целых параметра и символьный знак операции до тех пор, пока не будет введен пробел в качестве знака операции.
// В выходных данных выводите значения функций. 
#include <iostream>
void minus(int num1, int num2) {

}
void plus(int num1, int num2) {

}
void divide(int num1, int num2) {

}
void multiply(int num1, int num2) {

}

int main() {
	char* znak = new char;
	while (znak != "_") {
		int num1 = 0;
		std::cout << "\n" << "Num 1 =";
		std::cin >> num1;
		int num2 = 0;
		std::cout << "Num 2 =";
		std::cin >> num2;
		std::cout << "Znak =";
		std::cin >> znak;
		std::cout << num1 << " " << znak << " " << num2 << " = ";

	}

	return 0;
}