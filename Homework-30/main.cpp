#include <iostream>
#include <cstdlib>
#include <ctime>
#include "optimized_thread.h"
mutex locker;
template< typename T >

void quickSort(T* array, const std::size_t size) {
    T temp;

    std::size_t leftBorderStack[32] = { 0 },
        rightBorderStack[32] = { 0, size - 1 },
        stackPos = 1,
        leftBorder = 0,
        rightBorder = 0,
        leftPartSize = 0,
        rightPartSize = 0,
        left = 0,
        right = 0,
        pivotElement = 0;


    while (stackPos > 0) {
        leftBorder = leftBorderStack[stackPos];
        rightBorder = rightBorderStack[stackPos];
        stackPos--;

        while (leftBorder < rightBorder) {
            left = leftBorder;
            right = rightBorder;
            pivotElement = leftBorder;

            while (left < right) {
                while (pivotElement < right)
                    if (array[pivotElement] > array[right]) {
                        temp = array[pivotElement];
                        array[pivotElement] = array[right];
                        array[right] = temp;
                        left = pivotElement + 1;
                        pivotElement = right;
                    }
                    else
                        right--;

                while (pivotElement > left)
                    if (array[pivotElement] < array[left]) {
                        temp = array[pivotElement];
                        array[pivotElement] = array[left];
                        array[left] = temp;
                        right = pivotElement - 1;
                        pivotElement = left;
                    }
                    else
                        left++;
            }

            rightPartSize = rightBorder - pivotElement;
            leftPartSize = pivotElement - leftBorder;

            if (rightPartSize > leftPartSize) {
                if (rightPartSize > 1) {
                    stackPos++;
                    leftBorderStack[stackPos] = pivotElement + 1;
                    rightBorderStack[stackPos] = rightBorder;
                }

                rightBorder = pivotElement;
            }
            else {
                if (leftPartSize > 1) {
                    stackPos++;
                    leftBorderStack[stackPos] = leftBorder;
                    rightBorderStack[stackPos] = pivotElement - 1;
                }

                leftBorder = pivotElement;
            }
        }
    }
}
void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

// Функция для разделения массива и выбора опорного элемента
int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high]; // Опорный элемент
    int i = (low - 1); // Индекс меньшего элемента

    for (int j = low; j <= high - 1; j++) {
        // Если текущий элемент меньше или равен опорному
        if (arr[j] <= pivot) {
            i++; // Увеличиваем индекс меньшего элемента
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}


// Однопоточная функция быстрой сортировки
void quicksort_vector(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        // Разделение массива на две части
        int pi = partition(arr, low, high);

        // Рекурсивный вызов функции quicksort для двух частей массива
        quicksort_vector(arr, low, pi - 1);
        quicksort_vector(arr, pi + 1, high);
    }
}
int main() {
    std::size_t size = 100000;//количество элементов для сортировки
    int* array = new int[size];

    std::srand(std::time(0));

    for (std::size_t i = 0; i < size; i++) {
        array[i] = std::rand() % 10000;

        /*f std::cout << array[i] << ' ';*/
    }

    int R = 1000;
    int M = size / R;//количество массивов в матрице или количество задач
    if (size % R > 0)M++;
    int** matrix = new int* [M];
    int size_2 = size;//переменная для обратного отсчета размера первого массива

    for (int i = 0; i < M; i++)
    {
        if (size_2 >= R)
        {
            matrix[i] = new int[R]; for (int j = 0; j < R; j++)
            {
                matrix[i][j] = array[size_2 - 1]; /*cout << matrix[i][j] << " ";*/
                size_2--;
            }
            cout << endl;

        }
        else {
            matrix[i] = new int[size_2]; int k = size_2;
            for (int j = 0; j < k; j++)
            {
                matrix[i][j] = array[size_2 - 1]; /*cout << matrix[i][j] << " ";*/
                size_2--;
            }
        }
    }


    RequestHandler2 rh;
    //OptimizedThreadPool op;

    lock_guard<mutex> l(locker);
    for (int i = 0; i < M; i++)
    {

        rh.push_task(quickSort, matrix[i], R);

    };
    vector<int>numbers;

    //for (int j = 0; j < R; j++) cout << matrix[4][j] << " ";
    for (int i = 0; i < M; i++) { for (int j = 0; j < R; j++) { numbers.push_back(matrix[i][j]); }; };
    //for (int i = 0; i < numbers.size(); i++)cout << numbers[i] << " ";
    quicksort_vector(numbers, 0, numbers.size() - 1);
    cout << endl;

    //однопоточная сортировка
    quickSort(array, size);

    //for (std::size_t i = 0; i < size; i++)std::cout << array[i] << ' ';

    delete[] array;

    return 0;
}