#pragma once
class CPermutation
{
	int * values;//wartosci
	int n;//liczba elementów
public:
	CPermutation();//konstrutkor bezparametrowy
	CPermutation(int _n);//konstrutkor tworzy permutacje o dlugosci n
	~CPermutation();//destruktor
	void start();//utworzenie permutacji poczkawoej 1,2,3...
	void random();//utworzenie permutacji loswej
	void copy(int* _pi);//kopiowanie permutacji z tablicy
	int cut(int _x);//wyciecie i zwrocenie wartosci o idneksie x
	void insert(int _v, int _x);//wstawienie wartosci v w miesjce x
	void swap(int _x, int _y);//zamiana wartosci x i y
	int getValue(int _x);//pobranie wartosci o indeksie x
	int* getAllValues();//pobranie wszystkich wartosci

	std::string ToString();//przekonwertowanie tabicy jako strnig
};

