// Lab_07.1.rec.cpp
// Варіант 1 (Рекурсивний спосіб)
// Лабораторна робота № 7.1.
// Пошук заданих елементів та впорядкування рядків / стовпчиків матриці.

#include <iostream>
#include <iomanip>
#include <ctime>

using namespace std;

// Прототипи рекурсивних функцій
void Create(int** T, const int rowCount, const int colCount, const int Low, const int High, int i = 0, int j = 0);
void Print(int** T, const int rowCount, const int colCount, int i = 0, int j = 0);
void Sort(int** T, const int rowCount, const int colCount, int i0 = 0, int i1 = 0);
void Change(int** T, const int row1, const int row2, const int colCount, int j = 0);
void Calc(int** T, const int rowCount, const int colCount, int& S, int& k, int i = 0, int j = 0);

int main()
{
    srand((unsigned)time(NULL));

    const int Low = -17;
    const int High = 14;
    const int rowCount = 8;
    const int colCount = 5;

    // Динамічне виділення пам'яті під матрицю T
    int** T = new int* [rowCount];
    for (int i = 0; i < rowCount; i++)
        T[i] = new int[colCount];

    // 1. Формування та виведення початкової матриці
    Create(T, rowCount, colCount, Low, High);
    cout << "Initial matrix T:";
    Print(T, rowCount, colCount);

    // 2. Впорядкування матриці за ключами та виведення
    Sort(T, rowCount, colCount);
    cout << "Sorted matrix T:";
    Print(T, rowCount, colCount);

    // 3. Обчислення суми, кількості та заміна елементів нулями
    int S = 0;
    int k = 0;
    Calc(T, rowCount, colCount, S, k);

    cout << "S = " << S << endl;
    cout << "k = " << k << endl;

    cout << "Modified matrix T:";
    Print(T, rowCount, colCount);

    // Звільнення динамічної пам'яті
    for (int i = 0; i < rowCount; i++)
        delete[] T[i];
    delete[] T;

    return 0;
}

// 1. Рекурсивне формування матриці випадковими числами
void Create(int** T, const int rowCount, const int colCount, const int Low, const int High, int i, int j)
{
    T[i][j] = Low + rand() % (High - Low + 1);
    if (j < colCount - 1)
        Create(T, rowCount, colCount, Low, High, i, j + 1);
    else if (i < rowCount - 1)
        Create(T, rowCount, colCount, Low, High, i + 1, 0);
}

// 2. Рекурсивне виведення матриці на екран (форматування як в ітераційному способі)
void Print(int** T, const int rowCount, const int colCount, int i, int j)
{
    if (i == 0 && j == 0)
        cout << endl; // Один відступ перед матрицею

    cout << setw(4) << T[i][j];

    if (j < colCount - 1)
    {
        Print(T, rowCount, colCount, i, j + 1);
    }
    else if (i < rowCount - 1)
    {
        cout << endl; // Перехід на новий рядок матриці
        Print(T, rowCount, colCount, i + 1, 0);
    }
    else
    {
        cout << endl << endl; 
    }
}

// 3. Рекурсивна функція перестановки двох рядків місцями
void Change(int** T, const int row1, const int row2, const int colCount, int j)
{
    int tmp = T[row1][j];
    T[row1][j] = T[row2][j];
    T[row2][j] = tmp;

    if (j < colCount - 1)
        Change(T, row1, row2, colCount, j + 1);
}

// 4. Рекурсивне сортування рядків (метод бульбашки)
void Sort(int** T, const int rowCount, const int colCount, int i0, int i1)
{
    if ((T[i1][0] > T[i1 + 1][0]) ||
        (T[i1][0] == T[i1 + 1][0] && T[i1][1] > T[i1 + 1][1]) ||
        (T[i1][0] == T[i1 + 1][0] && T[i1][1] == T[i1 + 1][1] && T[i1][2] > T[i1 + 1][2]))
    {
        Change(T, i1, i1 + 1, colCount);
    }

    if (i1 < rowCount - i0 - 1 - 1)
        Sort(T, rowCount, colCount, i0, i1 + 1);
    else if (i0 < rowCount - 1 - 1)
        Sort(T, rowCount, colCount, i0 + 1, 0);
}

// 5. Рекурсивне обчислення суми, кількості та обнулення елементів
void Calc(int** T, const int rowCount, const int colCount, int& S, int& k, int i, int j)
{
    if (T[i][j] < 0 && !(T[i][j] % 4 == 0))
    {
        S += T[i][j];
        k++;
        T[i][j] = 0;
    }

    if (j < colCount - 1)
        Calc(T, rowCount, colCount, S, k, i, j + 1);
    else if (i < rowCount - 1)
        Calc(T, rowCount, colCount, S, k, i + 1, 0);
}