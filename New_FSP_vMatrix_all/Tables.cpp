#include "stdafx.h"
#include "Tables.h"

void viewPerm(int * pi, int size) {
	for (int i = 0; i < size; i++)
		std::cout << pi[i] << " ";
	std::cout << "\n\n";
}

void copyPerm(int *source, int *destination, int _n)
{
	for (int i = 0; i<_n; i++)
		destination[i] = source[i];
}

int maxtab(int* vec1, int _n) {
	int result = vec1[0];
	for (int j = 1; j<_n; j++)
		if (vec1[j]>result)
			result = vec1[j];
	if (result>0)
		return result;
	else
		return 1;
}

int cutPerm(int* permutation, int _n, int position) {
	int tmp;
	tmp = permutation[position];
	for (int i = position; i<_n - 1; i++)
		permutation[i] = permutation[i + 1];
	permutation[_n - 1] = 0;
	return tmp;
}

void swapPerm(int* permutation, int x, int y) {
	int tmp;
	tmp = permutation[x];
	permutation[x] = permutation[y];
	permutation[y] = tmp;
}

void insertPerm(int *permutation, int _n, int position, int nr) {
	for (int i = _n - 1; i>position; i--)
		permutation[i] = permutation[i - 1];
	permutation[position] = nr;
}
