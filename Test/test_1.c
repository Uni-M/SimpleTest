#include "test_1.h"

/*
* Задача 1
* Написать фрагмент программы, вычисляющий сумму положительных элементов двухмерного массива.
*/
int main()
{
    size_t rowsCount = 0;
    size_t columnsCount = 0;

    printf("Enter matrix rows count: ");
    scanf_s("%lu", &rowsCount);
    printf("Enter matrix columns count: ");
    scanf_s("%lu", &columnsCount);
    printf("Entered matrix size : %lux%lu\n", rowsCount, columnsCount);

    int** matrix = initMatrix(rowsCount, columnsCount);
    randomizeMatrix(matrix, rowsCount, columnsCount);
    printMatrix(matrix, rowsCount, columnsCount);

    printf("Sum of positives : %u\n", sumPositiveMatrix(matrix, rowsCount, columnsCount));

    freeMatrix(matrix, rowsCount, columnsCount);

    return 0;
}


int** initMatrix(size_t rowsCount, size_t columnsCount)
{
    int** a = (int**)malloc(rowsCount * sizeof(int*));
    for (int i = 0; i < rowsCount; ++i) {
        a[i] = (int*)malloc(columnsCount * sizeof(int));
    }
    return a;
}

void randomizeMatrix(int** matrix, size_t rowsCount, size_t columnsCount)
{
    for (int i = 0; i < rowsCount; ++i) {
        for (int j = 0; j < columnsCount; ++j) {
            matrix[i][j] = rand() % 21 - 10;
        }
    }
}

void printMatrix(int** matrix, size_t rowsCount, size_t columnsCount)
{
    for (int i = 0; i < rowsCount; ++i) {
        for (int j = 0; j < columnsCount; ++j) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

unsigned int sumPositiveMatrix(int** matrix, size_t rowsCount, size_t columnsCount)
{
    unsigned int sum = 0;
    for (int i = 0; i < rowsCount; ++i) {
        for (int j = 0; j < columnsCount; ++j) {
            sum += matrix[i][j] > 0 ? matrix[i][j] : 0;
        }
    }
    return sum;
}

void freeMatrix(int** matrix, size_t rowsCount, size_t columnsCount)
{
    for (int i = 0; i < rowsCount; ++i) {
        free(matrix[i]);
    }
    free(matrix);
}