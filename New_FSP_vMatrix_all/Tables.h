#pragma once
void viewPerm(int *, int);//wyswietla permutacje
void copyPerm(int *source, int *destination, int _n);//kopiuje permutacje
int maxtab(int* vec1, int _n);//zwraca max z tablicy lub 1 gdy wartpsci ujemne
int cutPerm(int* permutation, int _n, int position);
void swapPerm(int* permutation, int x, int y);
void insertPerm(int *permutation, int _n, int position, int nr);