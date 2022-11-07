#include "task_5.h"

/*
* Задача 5
* Написать фрагмент программы, вычисляющий детерминант матрицы 3 Х 3.
*/
int main()
{
    srand(time(NULL));

    size_t sideCount = 3;

    printf("Generated matrix with size %lux%lu :\n", sideCount, sideCount);

    int** matrix = initMatrix(sideCount);
    randomizeMatrix(matrix, sideCount);
    printMatrix(matrix, sideCount);

    printf("Determinant of matrix : %d\n", determinant(matrix, sideCount));
    freeMatrix(matrix, sideCount);

    return 0;
}


int** initMatrix(size_t sideCount)
{
    int** matrix = (int**)malloc(sideCount * sizeof(int*));

    for (int i = 0; i < sideCount; ++i)
    {
        matrix[i] = (int*)malloc(sideCount * sizeof(int));
    }
    return matrix;
}

void randomizeMatrix(int** matrix, size_t sideCount)
{
    for (int i = 0; i < sideCount; ++i)
    {
        for (int j = 0; j < sideCount; ++j)
        {
            matrix[i][j] = rand() % 21 - 10;
        }
    }
}

void printMatrix(int** matrix, size_t sideCount)
{
    for (int i = 0; i < sideCount; ++i)
    {
        for (int j = 0; j < sideCount; ++j)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int determinant(int** matrix, size_t sideCount)
{
    return matrix[0][0] * matrix[1][1] * matrix[2][2] +
        matrix[2][0] * matrix[0][1] * matrix[1][2] +
        matrix[1][0] * matrix[2][1] * matrix[0][2] -
        matrix[2][0] * matrix[1][1] * matrix[0][2] -
        matrix[0][0] * matrix[2][1] * matrix[1][2] -
        matrix[1][0] * matrix[0][1] * matrix[2][2];
}

void freeMatrix(int** matrix, size_t sideCount)
{
    for (int i = 0; i < sideCount; ++i) {
        free(matrix[i]);
    }
    free(matrix);
}
