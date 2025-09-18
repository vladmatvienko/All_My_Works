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

void help(int num[], int n, int i){
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < n && num[l] > num[largest]){
        largest = l;
    }
    if (r < n && num[r] > num[largest]){
        largest = r;
    }
    if (largest != i){
        swap(&num[i], &num[largest]);
        return help(num, n, largest);
    }
}

void BinnaryTreeSort(int num[], int n){
    for (int i = n / 2 - 1; i >= 0; i--){
        help(num, n, i);
    }
    for (int i = n - 1; i >= 0; i--){
        swap(&num[0], &num[i]);
        help(num, i, 0);
    }
}

void printNum(int num[], int n){
    for (int i = 0; i < n ; i++){
        std::cout << " " << num[i];
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
    BinnaryTreeSort(num, size);
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