#pragma once
class CGenetic
{
public:
	CGenetic();
	~CGenetic();
	int* Crossover(int * _parent1, int * _parent2, int _n);
	int* Mutation(int * _parent1, int _n);
	int Roulette(int* _fitness, int _n);
	int maxFitIdx(int* _fitness, int _n);
	int maxFitFit(int* _fitness, int _n);
	bool check(int * _parent1, int _v, int _n);
};

