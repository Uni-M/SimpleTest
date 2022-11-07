#include <stdio.h>
#include <stdlib.h>

int** initMatrix(size_t rowsCount, size_t columnsCount);
void randomizeMatrix(int** matrix, size_t rowsCount, size_t columnsCount);
void printMatrix(int** matrix, size_t rowsCount, size_t columnsCount);
unsigned int sumMatrixWithoutMinMax(int** matrix, size_t rowsCount, size_t columnsCount);
void freeMatrix(int** matrix, size_t rowsCount, size_t columnsCount);
