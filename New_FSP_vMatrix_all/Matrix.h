#pragma once
class CMatrix
{
	int m;//liczba wierszy
	int n;//liczba kolumn
	int **values;//wartosci
public:
	CMatrix();//konstruktor bezparametrowy
	CMatrix(int _m, int _n);//konstruktor tworzacy macierz m x n
	~CMatrix();//dekonstruktor
	void setValue(int _v, int _x, int _y);//ustawienie wartosci v w macierzy[x][y]
	void setAllValues(int _v);//ustawienie wszystkich wartosci macierzy na wartosc v
	void setRow(int* _vec, int _x);//ustawienie wiersza wartosci na podstawie wektora _vec
	void setRandom(int _min, int _max);//wylosowanie wsystkich wartosci macierzy z zakresu min max
	void swapColumn(int _x, int _y);//zamiana kolumny x i y
	void swapRow(int _x, int _y);//zamiana wierszy x i y
	int * cutColumn(int _x);//wyciecie kolumny x z macierzy i pobiranie jej wartosci
	int * cutRow(int _x);//wyciecie wiersza x z macierzy i pobiranie jej wartosci
	int * getColumn(int _x);//pobranie kolumny
	int * getRow(int _x);//pobranie wiersza
	void insertColumn(int*_vec, int _x);//wstawienie columny vec w miejsce x
	void insertRow(int*_vec, int _x);//wstawienie wiersza vec w miejsce x
	int getValue(int _x, int _y);//pobranie wartosci o indeksach [x][y]
	void matrixCopy(const CMatrix &_M);//skopiowanie macierzy na podstawie macierzy M
	void matrixCopy(const CMatrix &_M, int * _pi);//skopiowanie macierzy na podstawie macierzy M z zadana permutacja pi
	std::string ToString();//przekonwertowanie macierzy jako strnig

	
};

