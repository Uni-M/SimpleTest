#include <stdio.h>
#include <stdlib.h>

int** initMatrix(size_t rowsCount, size_t columnsCount);
void printMatrix(int** matrix, size_t n, size_t m);
void randomizeMatrix(int** matrix, size_t rowsCount, size_t columnsCount);
unsigned int sumPositiveMatrix(int** a, size_t n, size_t m);
void freeMatrix(int** matrix, size_t rowsCount, size_t columnsCount);
