#include <iostream>
#include <ctime>
#include <cstdlib>

void swap(int* a, int* b) {
    int num = *a;
    *a = *b;
    *b = num;
}

int partition(int massive[], int low, int high)
{

    int pivot = massive[high]; // Сравниваемый элемент
    
    int i = (low - 1); // Стена

    for (int j = low; j <= high; j++)
    {
        if (massive[j] < pivot)
        {
            i++; //двигаем стену
            swap(&massive[i], &massive[j]); //Меняем местами элементы
        }
    }
    swap(&massive[i + 1], &massive[high]);
    return (i + 1);
}

void quickSort(int massive[], int low, int high)
{
    if (low < high)
    {

        int i = partition(massive, low, high); // Стена

        quickSort(massive, low, i - 1);//Проверяем элементы которые находятся справа от стены
        quickSort(massive, i + 1, high);//Проверяем элементы которые находятся слева от стены
    }
}

int main() {
    std::srand(std::time(nullptr));
    int size = 0;
    std::cout << "Input size: ";
    std::cin >> size;
    int *massive = new int[size];
    for (int i = 0; i < size; i++) {
        massive[i] = rand() % size;
    }
    /*std::cout << "{ ";
    for (int i = 0; i < size - 1; i++) {
        std::cout << massive[i] << ", ";
    }
    std::cout << massive[size - 1] << " ";
    std::cout << "}" << "\n";
    quickSort(massive, 0, size - 1);
    std::cout << "{ ";
    for (int i = 0; i < size-1; i++) {
        std::cout << massive[i] << ", ";
    }
    std::cout << massive[size - 1] << " ";
    std::cout << "}";*/
    unsigned int ST = clock();
    quickSort(massive, 0, size - 1);
    unsigned int ET = clock();
    unsigned int time = ET - ST;
    std::cout << std::endl << std::endl << "Work time: " << time << " tics" << std::endl;
    delete[] massive;
    return 0;
}
