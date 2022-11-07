#include "task_4.h"

/*
* Задача 4
* Написать фрагмент программы, перемножающий две матрицы.
*/
int main()
{
	srand(time(NULL));

	size_t rowsCount_1 = 0;
	size_t columnsCount_1 = 0;

	printf("Enter first matrix rows count: ");
	scanf_s("%lu", &rowsCount_1);
	printf("Enter first matrix columns count: ");
	scanf_s("%lu", &columnsCount_1);

	size_t rowsCount_2 = columnsCount_1;
	size_t columnsCount_2 = rowsCount_1;

	printf("Entered first matrix size : %lux%lu. \nSecond matrix will have size %lux%lu\n", rowsCount_1, columnsCount_1, rowsCount_2, columnsCount_2);

	int** matrix_1 = initMatrix(rowsCount_1, columnsCount_1);
	int** matrix_2 = initMatrix(rowsCount_2, columnsCount_2);

	randomizeMatrix(matrix_1, rowsCount_1, columnsCount_1);
	randomizeMatrix(matrix_2, rowsCount_2, columnsCount_2);

	printf("\nFirst generated matrix :\n");
	printMatrix(matrix_1, rowsCount_1, columnsCount_1);

	printf("\nSecond generated matrix :\n");
	printMatrix(matrix_2, rowsCount_2, columnsCount_2);


	int** resultMatrix = multMatrix(matrix_1, rowsCount_1, columnsCount_1,
		matrix_2, rowsCount_2, columnsCount_2);
	if (resultMatrix != NULL)
	{
		printf("\nThe result of multiplication :\n");
		printMatrix(resultMatrix, rowsCount_1, columnsCount_2);
		freeMatrix(resultMatrix, rowsCount_1, columnsCount_2);
	}
	else
	{
		printf("\nIncorrect data entry.\n");
	}

	freeMatrix(matrix_1, rowsCount_1, columnsCount_1);
	freeMatrix(matrix_2, rowsCount_2, columnsCount_2);

	return 0;
}


int** initMatrix(size_t rowsCount, size_t columnsCount)
{
	int** a = (int**)calloc(rowsCount, sizeof(int*));
	for (int i = 0; i < rowsCount; ++i)
	{
		a[i] = (int*)calloc(columnsCount, sizeof(int));
	}
	return a;
}

void randomizeMatrix(int** matrix, size_t rowsCount, size_t columnsCount)
{
	for (int i = 0; i < rowsCount; ++i)
	{
		for (int j = 0; j < columnsCount; ++j)
		{
			matrix[i][j] = rand() % 21 - 10;
		}
	}
}

void printMatrix(int** matrix, size_t rowsCount, size_t columnsCount)
{
	for (int i = 0; i < rowsCount; ++i)
	{
		for (int j = 0; j < columnsCount; ++j)
		{
			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

int** multMatrix(int** matrix_1, size_t rowsCount_1, size_t columnsCount_1, int** matrix_2, size_t rowsCount_2, size_t columnsCount_2)
{
	if (rowsCount_1 != columnsCount_2)
	{
		return NULL;
	}

	int** resultMatrix = initMatrix(rowsCount_1, columnsCount_2);


	for (int i = 0; i < rowsCount_1; ++i) {
		for (int j = 0; j < columnsCount_2; ++j)
		{
			for (int k = 0; k < columnsCount_1; ++k)
				resultMatrix[i][j] += matrix_1[i][k] * matrix_2[k][j];
		}
	}
	return resultMatrix;
}

void freeMatrix(int** matrix, size_t rowsCount, size_t columnsCount)
{
	for (int i = 0; i < rowsCount; ++i)
	{
		free(matrix[i]);
	}
	free(matrix);
}

