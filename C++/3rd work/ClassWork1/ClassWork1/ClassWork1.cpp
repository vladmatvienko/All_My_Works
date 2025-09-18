//task1//
//1) Создать указатель* ptr на целочисленную
//переменную и присвоить значение через
//указатель 100. Скопировать значения
//указателя * ptr в указатель * ptr2.Присвоить
//значение 200 через указатель * ptr2.Вывести
//содержимое обоих указателей.
//#include <iostream>
//
//int main()
//{
//
//    int *ptr = new int;
//    *ptr = 100;
//    int *ptr2 = ptr;
//    *ptr2 = 200;
//    std::cout << "Ptr1 = " << *ptr << " Ptr2 = " << *ptr2;
//    delete ptr;
//    return 0;
//} ctrl+c+k
//task2//
//2) Напишите функцию swap, которая меняет
//значения переданных аргументов
//Например, после вызова swap(a, b) в
//переменной а должно оказаться значение b, а
//в переменной b значение а
//void swap(int a, int b) {
//    int *ptr1 = new int;
//    *ptr1 = 10;
//    int  *ptr2 = &a;
//    *ptr2 = a;
//    int *ptr3 = &b;
//    *ptr3 = b;
//    *ptr1 = *ptr2;
//    *ptr2 = *ptr3;
//    *ptr3 = *ptr1;
//    std::cout << *ptr1 << " " << *ptr2 << " " << *ptr3 << " ";
//    delete ptr1;
//    
//}
#include <iostream>
void swap(int &a, int &b) {
    int tmp = a;
    a = b;
    b = tmp;
}

void swap_ptr(int *ptr_a, int *ptr_b)
{
    *ptr_a = *ptr_a - *ptr_b;
    *ptr_b = *ptr_b + *ptr_a;
    *ptr_a = *ptr_b - *ptr_a;
}

int main()
{

    int a = 5;
    int b = 7;
    swap(a, b);
    std::cout << "a = " << a << "; b = " << b;
    swap_ptr(&a, &b);
    std::cout << "a = " << a << "; b = " << b;
    return 0;
} 


