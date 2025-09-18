#include <iostream>
#include <ctime>
#include <cstdlib>
void swap(int* a, int* b) {
    int num = *a;
    *a = *b;
    *b = num;
}

void BubbleSort(int massive[], int size)
{
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (massive[j] > massive[j + 1]) {
                swap(&massive[j], &massive[j + 1]);
            }
        }
    }
}
int main() {
    std::srand(std::time(nullptr));
    int size = 0;
    std::cout << "Input size: ";
    std::cin >> size;
    int* massive = new int[size];
    for (int i = 0; i < size; i++) {
        massive[i] = rand() % size;
    }
    /*std::cout << "{ ";
    for (int i = 0; i < size - 1; i++) {
        std::cout << massive[i] << ", ";
    }
    std::cout << massive[size - 1] << " ";
    std::cout << "}" << "\n";
    BubbleSort(massive, 0, size - 1);
    std::cout << "{ ";
    for (int i = 0; i < size-1; i++) {
        std::cout << massive[i] << ", ";
    }
    std::cout << massive[size - 1] << " ";
    std::cout << "}";*/
    unsigned int ST = clock();
    BubbleSort(massive, size);
    unsigned int ET = clock();
    unsigned int time = ET - ST;
    std::cout << std::endl << std::endl << "Work time: " << time << " tics" << std::endl;
    delete[] massive;
    return 0;
}