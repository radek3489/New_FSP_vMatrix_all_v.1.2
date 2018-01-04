#pragma once
class CFlowShop
{
	int m;//liczba maszyn
	int n;//liczba zadan
	CPermutation * pi_best;//najlepsza permutacja
	CPermutation * pi_begin;//najlepsza permutacja
	CPermutation * piSetups_best;//najlepsza permutacja
	CPermutation * piSetups_begin;//najlepsza permutacja
	CMatrix * Data;//macierz z danymi wejsciowymi
	int *** s;// macierz trzywymiarowa przechowujaca przezbrojenia
	char  name[20];//nazwa instacji
	CMatrix *P, *S,*C;//macierze czasu trwania, rozpoczecia ,zakonczenia
	int *Psetups, *Ssetups, *Csetups;
	Time_countner  stoper;
	
public:
	CFlowShop();
	CFlowShop(std::string _track);
	~CFlowShop();
	int Calculate(int* _pi, int *_piSetups,int _n);
	void Run(double _TimeStop);
	double NEH();
	double TS();
	int* TWOopt(int* _pi);
	int* SA(double _time, double _temperature, int* _pi);
	double GA(double _time, int _spopulation, double _pcrossover,double _pmutation, double _opt);
	int maxtab(int*, int);
	int idx2nr(int _i, int _j, int _k);
	int* nr2idx(int _x);
	int bettersetup(int _s1, int _s2, int *_piSetups, int _n);
	std::string generateLaTeX(std::string _track);
	std::string ToString();//przekonwertowanie instancji jako strnig
};

