#include <stdio.h>
#include <stdlib.h>

int factorial(int n);
/*
* Задача 3
* Написать рекурсивную процедуру вычисления факториала
*/
int main()
{
	int n = 0;
	printf("Enter number to compute factorial : ");
	scanf_s("%d", &n);
	printf("%d! is %d", n, factorial(n));

	return 0;
}


int factorial(int n) {
	return (n == 1) ? 1 : n * factorial(n - 1);
}