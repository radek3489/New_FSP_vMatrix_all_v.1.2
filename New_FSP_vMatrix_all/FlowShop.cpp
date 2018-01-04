#include "stdafx.h"
#include "Permutation.h"
#include "Matrix.h"
#include "Time_countner.h"
#include "FlowShop.h"
#include "Genetic.h"

using namespace std;

CFlowShop::CFlowShop()
{

}

CFlowShop::CFlowShop(std::string _track)
{
	int tmpIdx,tmpVal;
	char tmpChar[5];
	strcpy_s(name, _track.c_str());
	fstream file;
	file.open(_track, fstream::in);
	if (!file.is_open()) {
		cout << "Nie ma takiego pliku\n";
		system("pause");
		exit(0);
	}
	file >> n;
	file >> m;

	pi_best = new CPermutation(n);
	pi_begin= new CPermutation(n);
	piSetups_begin = new CPermutation(n*n);
	piSetups_best = new CPermutation(n*n);
	Data = new CMatrix(m, n);
	for (int j = 0; j<n; j++) {
		for (int i = 0; i<m; i++) {
			file >> tmpIdx;
			file >> tmpVal;
			Data->setValue(tmpVal, tmpIdx, j);
		}
	}
	file >> tmpChar;
	cout << tmpChar << endl;

	s = new int **[m];
	for (int i = 0; i<m; i++) {
		s[i] = new int*[n];
		for (int j = 0; j<n; j++)
			s[i][j] = new int[n];
	}
	for (int i = 0; i<m; i++) {
		file >> tmpChar;
		cout << tmpChar << endl;
		for (int j = 0; j<n; j++)
			for (int k = 0; k < n; k++) {
				file >> s[i][j][k];//<---jeœli odwrotna impretacja to zamienic j z k 
			}
	}
	file.close();
	//std::cout<<ToString();
	pi_begin->start();
	pi_best->start();
	piSetups_begin->start();
	piSetups_best->start();
	P = new CMatrix(m, n);
	S = new CMatrix(m, n);
	C = new CMatrix(m, n);
	Psetups = new int[n*n];
	Ssetups = new int[n*n];
	Csetups = new int[n*n];

}


CFlowShop::~CFlowShop()
{

}

int CFlowShop::Calculate(int* _pi,int* _piSetpus, int _n)
{
	P->matrixCopy(*Data, _pi);
	int * tmp = new int[2];
	S->setAllValues(0);
	for (int k = 0; k < n*n; k++) {
		Ssetups[k] = 0;
		Psetups[k] = 0;
	}

	for (int i = 0; i < m; i++)
		for (int j = 1; j < _n; j++)
			Psetups[i*_n+j] = s[i][_pi[j - 1] - 1][_pi[j] - 1];
		
	for (int i = 1; i < m; i++)
		S->setValue(S->getValue(i - 1, 0) + P->getValue(i-1, 0),i,0);
	for (int i = 0; i < m; i++)
		for (int j = 1; j < _n; j++) {
			tmp[0] = S->getValue(i, j - 1) + P->getValue(i, j - 1) + Psetups[i*_n+j];
			if (i > 0)
				tmp[1] = S->getValue(i - 1, j) + P->getValue(i - 1, j);
			else
				tmp[1] = 1;
			S->setValue(maxtab(tmp,2), i, j);

		}


	for (int j = 0; j < _n; j++)
		for (int i = 0; i < m; i++)
			C->setValue(S->getValue(i,j)+ P->getValue(i, j), i, j);

	delete[] tmp;

	return C->getValue(m-1,_n-1);
}

void CFlowShop::Run(double _TimeStop)
{
	double neh,sa,ga,to;
	cout << "wartosc poczatkowa:  " << Calculate(pi_best->getAllValues(),piSetups_begin->getAllValues(), n) ;
	/*cout << "\n algorytm NEH:\nczas: " << NEH();
	neh = Calculate(pi_best->getAllValues(), n);
	cout << " s\nCmax: " << neh;
	cout <<"\npermutacja"<< pi_best->ToString();
	//*/
	/*neh = 31961;
	cout << "\n algorytm 2-opt\nczas: ";
	pi_best->copy(TWOopt(pi_begin->getAllValues()));
	to = Calculate(pi_best->getAllValues(), n);
	cout << " s\nCmax: " << to;
	cout << "\nPRD : " << (double)((to - neh) * 100) / neh <<" %";
	cout << "\npermutacja" << pi_best->ToString();*/
	/*neh = 31961;
	cout << "\n algorytm Symulowane wyzarzanie\nczas: " << SA(.1,100.0,pi_begin->getAllValues());
	sa = Calculate(pi_best->getAllValues(), n);
	cout << " s\nCmax: " << sa;
	cout << "\nPRD : " << (double)((sa - neh) * 100) / neh <<" %";
	cout << "\npermutacja" << pi_best->ToString();*/
	//neh = 31961;
	/*cout << "\n algorytm Genetyczny\nczas: " << GA(_TimeStop -1.0, 20, 1.0,0.05,1.0);
	ga = Calculate(pi_best->getAllValues(), n);
	cout << " s\nCmax: " << ga;
	cout << "\nPRD : " << (double)((ga - neh) * 100) / neh << " %";
	cout << "\npermutacja" << pi_best->ToString();*/


}

double CFlowShop::NEH()
{
	stoper.startTime();
	//sortowanie
	CPermutation * pi_tmp;
	pi_tmp = new CPermutation(n);
	pi_tmp->start();

	

	int _v;
	int * tmp;
	tmp = new int[n];
	for (int k = 0; k<n; k++) {
		tmp[k] = 0;
		for (int j = 0; j<m; j++) {
			tmp[k] += P->getValue(j, k);
		}
	}
	for (int j = 0; j<n - 1; j++)
		for (int k = 0; k<n - 1; k++)
			if (tmp[k]<tmp[k + 1]) {
				_v = tmp[k];
				tmp[k] = tmp[k + 1];
				tmp[k + 1] = _v;
				pi_tmp->swap(k, k + 1);
			}
	delete[] tmp;
	pi_begin->copy(pi_tmp->getAllValues());
	//wstawianie
	CPermutation *_tmp, *_top, *_handly;
	_tmp = new CPermutation(n);
	_top = new CPermutation(n);
	_handly = new CPermutation(n);
	_handly->insert(pi_tmp->getValue(0),0);
	for (int k = 1; k<n; k++) {//wybranie k-tego zadania
		_top->copy(_handly->getAllValues());
		_top->insert(pi_tmp->getValue(k), 0);
		for (int j = 1; j <= k; j++) {//wstwienie na j-tej pozycji
			_tmp->copy(_handly->getAllValues());
			_tmp->insert(pi_tmp->getValue(k), j);
			//if (Calculate(_tmp->getAllValues(), k + 1)<Calculate(_top->getAllValues(), k + 1))//sprawdzenie czy wstawienie na j-tej pozycji poprawia wynik
			//	_top->copy(_tmp->getAllValues());
		}
		_handly->copy(_top->getAllValues());
	}
	pi_best->copy(_top->getAllValues());
	pi_begin->copy(_top->getAllValues());
	_tmp->~CPermutation();
	_top->~CPermutation();
	_handly->~CPermutation();
	stoper.stopTime();
	return stoper.getTime();
}

int* CFlowShop::TWOopt(int * _pi)
{
	//stoper.startTime();
	//stoper.stopTime();
	CPermutation *_tmp, *_top;
	int Ctmp, Ctop;
	_tmp = new CPermutation(n);
	_top = new CPermutation(n);
	_tmp->copy(_pi);
	_top->copy(_pi);
	//--Ctop = Calculate(_tmp->getAllValues(), n);
	Ctop = 0;//
	Ctmp = Ctop;
	for(int j =0;j<n;j++)
		for (int k = 0; k < n; k++) {
			_tmp->swap(j, k);
			//--Ctmp = Calculate(_tmp->getAllValues(), n);
			if (Ctmp < Ctop) {
				Ctop = Ctmp;
				_top->copy(_tmp->getAllValues());
				k = 0;
				j = 0;
			}
			else
				_tmp->swap(j, k);
		}
	//pi_best->copy(_top->getAllValues());
	//_tmp->~CPermutation();
	_tmp->~CPermutation();
	//stoper.stopTime();
	//return stoper.getTime();
	return _top->getAllValues();
}

int* CFlowShop::SA(double _time, double _temperature, int* _pi)
{
	Time_countner substoper;
	substoper.startTime(); 
	srand(time(0));
	CPermutation *_tmp, *_handly, *_top;
	int Ctmp, Chandly, Ctop;
	_tmp = new CPermutation(n);
	_handly = new CPermutation(n);
	_top = new CPermutation(n);
	_handly->copy(_pi);
	_top->copy(_pi);
	double _wsp;
	//--Chandly = Calculate(_handly->getAllValues(), n);
	Chandly = 0;//---
	Ctop = Chandly;
	for (double k = 0; k < _time; k = substoper.getTime()) {
		_wsp = (_time-k)/_time;
		substoper.stopTime();
		_tmp->copy(_handly->getAllValues());
		_tmp->swap(rand()%n, rand() % n);
		//--Ctmp = Calculate(_tmp->getAllValues(), n);
		Ctmp = 0;//---
			if (Ctmp <= Chandly) {
				Chandly = Ctmp;
				_handly->copy(_tmp->getAllValues());
				if (Chandly < Ctop) {
					Ctop = Ctmp;
					_top->copy(_handly->getAllValues());
					//cout << "\n"<< stoper.getTime() <<" s fit:" << Ctop;
				}
			}
			else if (((float)rand() / (float)RAND_MAX) < (1 / (exp(Ctmp - Chandly) / (_temperature* _wsp)))) {
				Chandly = Ctmp;
				_handly->copy(_tmp->getAllValues());
			}
				
}
	//pi_best->copy(_top->getAllValues());
	_tmp->~CPermutation();
	_handly->~CPermutation();
	return _top->getAllValues();//<--
	//_top->~CPermutation();
	//stoper.stopTime();
	//return stoper.getTime();
}

double CFlowShop::GA(double _time, int _spopulation, double _pcrossover, double _pmutation, double _opt)
{
	stoper.startTime();
	srand(time(0));
	CGenetic * GA;
	CMatrix * Mpopulation, *newMpopulation;
	CPermutation * _pi,* _top;
	int Ctop;
	int * fitness;
	int fit;
	_pi = new CPermutation(n);
	_top = new CPermutation(n);
	fitness = new int[_spopulation];
	Mpopulation = new CMatrix(_spopulation, n);
	newMpopulation = new CMatrix(_spopulation, n);
	GA = new CGenetic();
	Mpopulation->setAllValues(0);
	newMpopulation->setAllValues(0);
	for (int i = 0; i < _spopulation; i++) {
		_pi->random();
		Mpopulation->setRow(_pi->getAllValues(), i);
	}
	for (int i = 0; i < _spopulation; i++)
		//---fitness[i] = Calculate(Mpopulation->getRow(i), n);
	//cout<<Mpopulation->ToString();
	Ctop = fitness[_spopulation - 1];
	_top->copy(Mpopulation->getRow(_spopulation-1));
	int age = 0;
	for (double k = 0; k < _time; k = stoper.getTime()) {
		
		//Sleep(250);
		cout <<"\npokolenie: "<< age << endl;
		age++;
		for (int i = 0; i < _spopulation; i++)
			newMpopulation->setRow(GA->Crossover(Mpopulation->getRow(GA->Roulette(fitness,_spopulation)),Mpopulation->getRow(GA->Roulette(fitness, _spopulation)),n),i);
		for (int i = 0; i < _spopulation; i++)
			if (((float)rand() / (float)RAND_MAX) < _pmutation) {
				//cout << "+";
				newMpopulation->setRow(GA->Mutation(newMpopulation->getRow(i),n), i);
			}
		//<---2opt
		/*for (int i = 0; i < _spopulation; i++)
			if (((float)rand() / (float)RAND_MAX) < _opt)
				newMpopulation->setRow(TWOopt(newMpopulation->getRow(i)), i);
		//<---v2*/
		/*for (int i = 0; i < 10; i++) {
			int rnd = GA->Roulette(fitness, _spopulation);
			if (((float)rand() / (float)RAND_MAX) < _opt)
				newMpopulation->setRow(TWOopt(newMpopulation->getRow(rnd)), rnd);
		}
		//<---SA*/
		for (int i = 0; i < _spopulation; i++)
			newMpopulation->setRow(SA(0.1,100.0,newMpopulation->getRow(i)), i);
		//<---2opt*/
		Mpopulation->matrixCopy(*newMpopulation);
		//cout << Mpopulation->ToString();
		for (int i = 0; i < _spopulation; i++)
			//---fitness[i] = Calculate(Mpopulation->getRow(i), n);
		fit = GA->maxFitFit(fitness, _spopulation);
		if (fit< Ctop) {
			cout <<"\n"<< stoper.getTime() <<" s fit: "<< fit;
			Ctop = GA->maxFitFit(fitness, _spopulation);
			_top->copy(Mpopulation->getRow(GA->maxFitIdx(fitness, _spopulation)));
		}
		stoper.stopTime();
	}
	//cout << Mpopulation->ToString();
	//for (int i = 0; i < _spopulation; i++)
		//cout << i << ": " << fitness[i] << "\n";
	pi_best->copy(_top->getAllValues());
	_top->~CPermutation();
	_pi->~CPermutation();
	stoper.stopTime();
	return stoper.getTime();
}

int CFlowShop::maxtab(int *vec1, int _n)
{
	int result = vec1[0];
	for (int j = 1; j<_n; j++)
		if (vec1[j]>result)
			result = vec1[j];
	if (result>0)
		return result;
	else
		return 1;
}

int CFlowShop::idx2nr(int _i, int _j, int _k)
{
	int x;
	x = _i*n * n + _j*n + _k + 1;
	return x;
}

int * CFlowShop::nr2idx(int _x)
{
	int* _vec = new int[3];
	int _i=0, _j=0, _k=0;
	_x--;
	while (_x - n*n>= 0) {
		_i++;
		_x -= n*n;
	}
	while (_x - n>= 0) {
		_k++;
		_x -= n;
	}
	_j = _x;
	_vec[0] = _i;
	_vec[1] = _k;
	_vec[2] = _j;
	return _vec;
}

int CFlowShop::bettersetup(int _s1, int _s2, int * _piSetups, int _n)
{
	int k = 0, j = 0;
	do {
		k++;
	} while (_s1 != _piSetups[k]);
	do {
		j++;
	} while (_s2 != _piSetups[j]);
	if (k < j)
		return k;
	return j;
}

string CFlowShop::generateLaTeX(string _track)
{
	fstream file;
	ostringstream tmp;
	char symbols[] = { 'e',' ','d','f','g','a' };
	string Code = "";
	Code += "\\documentclass[border=3mm, tikz, preview]{standalone}\n\\usepackage{pgfplots}\n\\usepackage{pgfgantt}\n\\begin{document}";
	Code += "\\begin{tikzpicture}[\nscale = 1,\ntransform shape,\na/.style = {pattern = north east lines},\nc/.style = {pattern = horizontal lines},\ng/.style = {pattern = north west lines},\nd/.style={pattern = dots},\ne/.style = {pattern = crosshatch},\nf/.style = {pattern = vertical lines},\nb/.style = {pattern = grid},\n]";
	Code += "\\begin{ganttchart}[inline, y unit title=.8cm, y unit chart=.5cm, vgrid,bar label font=\\LARGE\\bfseries,title label font=\\large,link label font=\\Large,link label node/.append style={above}, bar height=1.8, canvas/.append style={fill=none}]{1}{";
	Code += to_string(C->getValue(m-1,n-1)) + "}\n\\gantttitlelist{1,...,";
	Code += to_string(C->getValue(m - 1, n - 1)) + "}{1}\n\\\\\n";
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			Code += "\\ganttbar[bar/.append style={";
			Code += symbols[j % 6];
			Code += "}, name=";
			tmp.str("");
			tmp.clear();
			tmp << i + 1 << pi_best->getValue(j);
			Code += tmp.str() + "] {$";
			Code += to_string(pi_best->getValue(j)) + "$}{";
			Code += to_string(S->getValue(i,j) + 1) + "}{";
			Code += to_string(C->getValue(i, j)) + "}\n";
		}
		Code += "\\\\\n\\\\\n\\\\\n";
	}
	Code += "\\end{ganttchart}\n\\end{tikzpicture}";
	Code += "\\end{document}";
	file.open(_track, fstream::out);
	file << Code;
	file.close();
	return _track;
}

std::string CFlowShop::ToString()
{
	std::string text = "";
	text += to_string(n) + " x ";
	text += to_string(m) + "\n\n";
	text += Data->ToString();

	for (int i = 0; i<m; i++) {
		for (int j = 0; j<n; j++){
			for (int k = 0; k < n; k++) 
				text += std::to_string(s[i][j][k]) + " ";
			text += "\n";
			}
		text+= "\n";
	}	
	return text;
}
