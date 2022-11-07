#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int** initMatrix(size_t rowsCount, size_t columnsCount);
void randomizeMatrix(int** matrix, size_t rowsCount, size_t columnsCount);
void printMatrix(int** matrix, size_t rowsCount, size_t columnsCount);
int** multMatrix(int** matrix_1, size_t rowsCount_1, size_t columnsCount_1, int** matrix_2, size_t rowsCount_2, size_t columnsCount_2);
void freeMatrix(int** matrix, size_t rowsCount, size_t columnsCount);
