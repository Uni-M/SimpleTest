#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int** initMatrix(size_t sideCount);
void randomizeMatrix(int** matrix, size_t sideCount);
void printMatrix(int** matrix, size_t sideCount);
int determinant(int** matrix, size_t sideCount);
void freeMatrix(int** matrix, size_t sideCount);
