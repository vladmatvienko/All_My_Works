//1) Написать функцию, добавляющую в конец списка вещественных чисел
//которого равно среднему арифметическому всех его элементов.

//#include <iostream>
//#include <vector>
//#include <list>
//
//double mid(const std::list <double> &num){
//    double sum = 0;
//    for (std::list<double>::const_iterator i = num.begin(); i != num.end(); i++) {
//        sum += *i;
//    }
//    return sum / num.size();
//}
//
//int main()
//{
//    std::list <double> num;
//    for (int i = 0; i < 10; i++) {
//        std::cout << "Input number: ";
//        double a = 0;
//        std::cin >> a;
//        num.push_back(a);
//    }
//    num.push_back(mid(num));
//    for (std::list<double>::iterator i = num.begin(); i != num.end(); i++) {
//        std::cout << *i << " ";
//    }
//    return 0;
//    
//}


//#include <iostream>
//#include <vector>
//#include <list>
//
//void numbers(const std::list <int>& num, std::vector <int> &vec) {
//    for (std::list<int>::const_iterator i = num.begin(); i != num.end(); i++) {
//        if (*i%2 == 0) {
//            vec.push_back(*i);
//        }
//     }
//}
//
//int main()
//{
//    std::list <int> num;
//    for (int i = 0; i < 10; i++) {
//        std::cout << "Input number: ";
//        int a = 0;
//        std::cin >> a;
//        num.push_back(a);
//    }
//    std::vector <int> vec;
//    numbers(num, vec);
//    for (auto i: vec) {
//        std::cout << i << " ";
//    }
//    return 0;
//
//}



//Написать шаблонную функцию от 2ух параметров (вектор и список). Функция
//должна построить и вернуть новый вектор, полученный из исходного заменой
//нечетных элементов вектора на четные элементы списка.Длины вектора и списка
//могут быть различны.Вывести на экран исходные данные и результат работы
//функции.
#include <iostream>
#include <vector>
#include <list>

std::vector <int> numbers(const std::list <int>& num, const std::vector <int>& vec) {
    std::vector <int> answer(10, 0);
    std::list<int>::const_iterator a = num.begin();
    for (int i = 0; i < 10; i++) {
        if (vec[i] % 2 != 0) {
            if (a == num.begin()) {
                for (std::list<int>::const_iterator it = num.begin(); it != num.end(); it++) {
                    if (*it % 2 == 0) {
                        answer[i] = *it;
                    }
                    a = ++it;
                    break;
                }
            }
            else {
                for (std::list<int>::const_iterator it = a; it != num.end(); it++) {
                    if (*it % 2 == 0) {
                        answer[i] = *it;
                    }
                    a = ++it;
                    break;
                }
            }
        }
        else{
            answer[i] = vec[i];
        }

    }
    return answer;
}
        

int main()
{
    std::list <int> num;
    for (int i = 0; i < 5; i++) {
        std::cout << "Input number list: ";
        int a = 0;
        std::cin >> a;
        num.push_back(a);
    }
    std::vector <int> vec;
    vec.reserve(10);
    for (int i = 0; i < 10; i++) {
        std::cout << "Input number vec: ";
        int a = 0;
        std::cin >> a;
        vec.push_back(a);
    }
    std::vector <int> answer = numbers(num, vec);
    for (auto i : answer) {
        std::cout << i << " ";
    }
    return 0;

}