#include "stdafx.h"
#include "Permutation.h"


CPermutation::CPermutation()
{
}

CPermutation::CPermutation(int _n)
{
	this->n = _n;
	values = new int[n];
	for (int i = 0; i<n; i++)
		values[i] = 0;
}


CPermutation::~CPermutation()
{
	n = 0;
	delete[] values;
}

void CPermutation::start()
{
	for (int i = 0; i<n; i++)
		values[i] = i+1;
}

void CPermutation::random()
{
	start();
	int x, y;
	for (int i = 0; i < n / 2; i++) {
		x = rand() % n;
		y = rand() % n;
		swap(x, y);
	}
	
}

void CPermutation::copy(int * _pi)
{
	for (int i = 0; i<n; i++)
		values[i] = _pi[i];
}

int CPermutation::cut(int _x)
{
	int tmp;
	tmp = values[_x];
	for (int i = _x; i<n - 1; i++)
		values[i] = values[i + 1];
	values[n - 1] = 0;
	return tmp;
}

void CPermutation::insert(int _v, int _x)
{
	for (int i = n - 1; i>_x; i--)
		values[i] = values[i - 1];
	values[_x] = _v;
}

void CPermutation::swap(int _x, int _y)
{
	int tmp;
	tmp = values[_x];
	values[_x] = values[_y];
	values[_y] = tmp;
}

int CPermutation::getValue(int _x)
{
	return values[_x];
}

int * CPermutation::getAllValues()
{
	return values;
}

std::string CPermutation::ToString()
{
	std::string text = "\n";
	for (int i = 0; i < n; i++)
		text += std::to_string(values[i]) + " ";
	text += "\n";
	return text;
}
