#include <stdio.h>
#include <omp.h>
#include <locale>

int main()
{
	setlocale(LC_ALL, "Russian");

	omp_set_num_threads(2);
#pragma omp parallel num_threads(3)
	{
		printf("������������ ������� 1\n");
	}
#pragma omp parallel
	{
		printf("������������ ������� 2\n");
	}
	return 0;
}
