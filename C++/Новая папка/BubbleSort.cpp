#include <iostream>
#include <ctime>
#include <cstdlib>

void swap(int *a, int *b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void randomNums(int num[], int size){
    for(int i = 0; i < size; i++){
        num[i] = rand() % size;
    }
}

void bubbleSort(int num[], int size){
    for(int i = 0; i < size - 1; i++){
        for(int j = 0; j < size - i - 1; j++){
            if(num[j] > num[j + 1]){
                swap(&num[j], &num[j + 1]);
            }
        }
    }
}

int main(){
    std::srand(std::time(nullptr));
    int size = 0;
    std::cout << "Input size: ";
    std::cin >> size;
    int *num = new int[size];
    randomNums(num, size);
    unsigned int start_time = clock();
    bubbleSort(num, size);
    unsigned int end_time = clock();
    unsigned int search_time = end_time - start_time;
    for(int i = 0; i < size; i++){
        if(i % 10 == 0){
            std::cout << std::endl;
        }
        std::cout << num[i] << " ";
    }
    std::cout << std::endl << std::endl << "Work time: " << search_time << " tics" << std::endl;
    delete[] num;
    return 0;
}