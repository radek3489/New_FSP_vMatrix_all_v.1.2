// New_FSP_vMatrix_all.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Time_countner.h"
#include "Matrix.h"
#include "Permutation.h"
#include "FlowShop.h"

int main()
{
	CFlowShop * Problem;
	//std::string tmp = "SDST10_ta001.txt";
	std::string tmp = "SDST3_ri001.txt";
	Problem = new CFlowShop(tmp);
	Problem->Run(10.0);
	
	Problem->generateLaTeX("output.tex");
	std::cout << std::endl;
	system("pause");
	return 0;
}

