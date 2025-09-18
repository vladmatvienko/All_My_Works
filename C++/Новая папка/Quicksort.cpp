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

int randomPivot(int low, int high){
    return low + rand() % (high - low + 1);
}

void quickSort(int num[], int low, int high){
    if(low < high){
        int pivot = randomPivot(low, high);
        int pivotValue = num[pivot];
        swap(&num[pivot], &num[high]);
        int i = low - 1;
        for(int j = low; j < high; j++){
            if(num[j] < pivotValue){
                i++;
                swap(&num[i], &num[j]);
            }
        }
        swap(&num[i + 1], &num[high]);
        quickSort(num, low, i);
        quickSort(num, i + 2, high);
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
    quickSort(num, 0, size - 1);
    unsigned int end_time = clock();
    unsigned int search_time = end_time - start_time;
    // for(int i = 0; i < size; i++){
    //     if(i % 10 == 0){
    //         std::cout << std::endl;
    //     }
    //     std::cout << num[i] << " ";
    // }
    std::cout << std::endl << std::endl << "Work time: " << search_time << " tics" << std::endl;
    delete[] num;
    return 0;
}