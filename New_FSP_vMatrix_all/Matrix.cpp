#include "stdafx.h"
#include "Matrix.h"


CMatrix::CMatrix()
{
}


CMatrix::CMatrix(int _m, int _n)
{
	this->m = _m;
	this->n = _n;
	values = new int*[m];
	for (int i = 0; i < m; i++)
		values[i] = new int [n];
}

CMatrix::~CMatrix()
{
	for (int i = 0; i < m; i++)
		delete[] values[i];
	delete[] values;
	n = 0;
	m = 0;
}

void CMatrix::setValue(int _v, int _x, int _y)
{
	this->values[_x][_y] = _v;
}

void CMatrix::setAllValues(int _v)
{
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			this->values[i][j] = _v;
}

void CMatrix::setRow(int * _vec, int _x)
{
	for (int j = 0; j < n; j++)
		values[_x][j] =_vec[j];

}

void CMatrix::setRandom(int _min, int _max)
{
	for (int i = 0; i < m; i++) 
		for (int j = 0; j < n; j++)
			this->values[i][j] = rand() % (_max - _min) + _min;
}

void CMatrix::swapColumn(int _x, int _y)
{
	int tmp;
	for (int i = 0; i < m; i++) {
		tmp = values[i][_x];
		values[i][_x] = values[i][_y];
		values[i][_y] = tmp;
	}
		
}

void CMatrix::swapRow(int _x, int _y)
{
	int tmp;
	for (int j = 0; j < n; j++) {
		tmp = values[_x][j];
		values[_x][j] = values[_y][j];
		values[_y][j] = tmp;
	}
}

int * CMatrix::cutColumn(int _x)
{
	int* vec = new int[m];
	for (int i = 0; i < m; i++)
		vec[i] = values[i][_x];
	for (int i = 0; i < m; i++)
		for (int j = _x; j < n-1; j++)
			values[i][j] = values[i][j + 1];
	for (int i = 0; i < m; i++)
		values[i][n - 1]=0;
	return vec;
}

int * CMatrix::cutRow(int _x)
{
	int* vec = new int[n];
	for (int j = 0; j < n; j++)
		vec[j] = values[_x][j];
	for (int j = 0; j < n; j++)
		for (int i = _x; i < m - 1; i++)
			values[i][j] = values[i+1][j];
	for (int j = 0; j < n; j++)
		values[m-1][j] = 0;
	return vec;
}

int * CMatrix::getColumn(int _x)
{
	int* vec = new int[m];
	for (int i = 0; i < m; i++)
		vec[i] = values[i][_x];
	return vec;
}

int * CMatrix::getRow(int _x)
{
	int* vec = new int[n];
	for (int j = 0; j < n; j++)
		vec[j] = values[_x][j];
	return vec;
}

void CMatrix::insertColumn(int * _vec, int _x)
{
	for (int i = 0; i < m; i++)
		for (int j = n-1; j > _x; j--)
			values[i][j] = values[i][j - 1];
	for (int i = 0; i < m; i++)
		values[i][_x]=_vec[i];
	delete[] _vec;
}

void CMatrix::insertRow(int * _vec, int _x)
{
	for (int j = 0; j < n; j++)
		for (int i = m-1; i > _x; i--)
			values[i][j] = values[i - 1][j];
	for (int j = 0; j < n; j++)
		values[_x][j] = _vec[j];
	delete[] _vec;
}

int CMatrix::getValue(int _x, int _y)
{
	return values[_x][_y];
}

void CMatrix::matrixCopy(const CMatrix &_M)
{
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			this->values[i][j] = _M.values[i][j];
}

void CMatrix::matrixCopy(const CMatrix &_M, int * _pi)
{
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			this->values[i][j] = _M.values[i][_pi[j]-1];
	
}

std::string CMatrix::ToString()
{
	std::string text = "\n";
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++)
			text += std::to_string(values[i][j]) + " ";
		text += "\n";
	}
	text += "\n";
	return text;
}

