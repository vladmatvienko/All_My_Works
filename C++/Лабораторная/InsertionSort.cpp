#include <iostream>
#include <ctime>
#include <cstdlib>
void insertionSort(int massive[], int n)
{
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = massive[i];
        j = i - 1;

        while (j >= 0 && massive[j] > key) {
            massive[j + 1] = massive[j];
            j = j - 1;
        }
        massive[j + 1] = key;
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
    insertionSort(massive, size);
    std::cout << "{ ";
    for (int i = 0; i < size-1; i++) {
        std::cout << massive[i] << ", ";
    }
    std::cout << massive[size - 1] << " ";
    std::cout << "}";*/
    unsigned int ST = clock();
    insertionSort(massive, size);
    unsigned int ET = clock();
    unsigned int time = ET - ST;
    std::cout << std::endl << std::endl << "Work time: " << time << " tics" << std::endl;
    delete[] massive;
    return 0;
}

