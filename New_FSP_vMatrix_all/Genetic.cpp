#include "stdafx.h"
#include "Genetic.h"


CGenetic::CGenetic()
{
}


CGenetic::~CGenetic()
{
}

int * CGenetic::Crossover(int * _parent1, int * _parent2, int _n)
{
	int lcut, rcut;
	int * child;
	child = new int[_n];
	for (int j = 0; j < _n; j++)
		child[j] = 0;
	lcut = rand() % (_n - 3) + 1;
	rcut = rand() % (_n - lcut-1) + lcut+1;
	for (int j = 0; j < lcut; j++)
		child[j] = _parent1[j];
	for (int j = rcut; j < _n; j++)
		child[j] = _parent1[j];
	int x=lcut;
	for (int k = 0; k < _n; k++) {
			if (check(child, _parent2[k], _n) == true) {
				//std::cout << "+";
			}
			else {
				//std::cout << "-";
				child[x] = _parent2[k];
				x++;
			}

	}
		
	/*
	std::cout << "\nrodzic 1 :";
	for (int k = 0; k < _n; k++)
		std::cout << _parent1[k] << " ";
	std::cout << "\nrodzic 2 :";
	for (int k = 0; k < _n; k++)
		std::cout << _parent2[k] << " ";
	std::cout << "\ndziecko  :";
	for (int k = 0; k < _n; k++)
		std::cout << child[k] << " ";
	std::cout << "\nl: " << lcut << " r: " << rcut;*/
	delete[] _parent1;
	delete[] _parent2;
	return child;
}

int * CGenetic::Mutation(int * _parent1, int _n)
{
	int rnd1, rnd2, tmp;
	rnd1 = rand() % _n;
	rnd2 = rand() % _n;
	tmp = _parent1[rnd1];
	_parent1[rnd1] = _parent1[rnd2];
	_parent1[rnd2] = tmp;
	return _parent1;
}

int CGenetic::Roulette(int * _fitness, int _n)
{
	//int rnd = rand() % _n;
	double rnd = (double)rand() / (RAND_MAX + 1);
	double *probability;
	double sumFit=0;
	probability = new double[_n];
	for (int j = 0; j < _n; j++)
		sumFit += 1/(double)_fitness[j];
	for (int j = 0; j < _n; j++)
		probability[j] = (double)1 / ((double)_fitness[j])/sumFit;

	int k = 0;
	do {
		rnd -= probability[k];
		k++;
	} while (rnd>0);
	//std::cout << "\n k: " << k-1;

	return k-1;
}

int CGenetic::maxFitFit(int * _fitness, int _n)
{
	int x = 0;
	int result = _fitness[0];
	for (int j = 1; j<_n; j++)
		if (_fitness[j] < result) {
			result = _fitness[j];
			x = j;
		}
	return result;
}

bool CGenetic::check(int * _parent1, int _v, int _n)
{
	for (int i = 0; i < _n; i++)
		if (_parent1[i] == _v)
			return true;
	return false;
}

int CGenetic::maxFitIdx(int * _fitness, int _n)
{
	int x = 0;
	int result = _fitness[0];
	for (int j = 1; j<_n; j++)
		if (_fitness[j] < result) {
			result = _fitness[j];
			x = j;
		}
	return x;
}
