#ifndef NGOBATIN_H
#define NGOBATIN_H

#include "../header/ADT.h"

void GetDataObat();

void CreateListObat(arrObat *arr, int capacity);

void ReAllocListObat(arrObat *arr, int add);

void MenuNgobatin();

void ObatinPasien();

bool IsSakitValid(int idxi, int idxj);

void RincianObat(int idxi, int idxj,char rincian_Obat[50][100]);

void SortRincianObat(char rincian_Obat[50][100], int count);

void PrintRincianObat(int idxi, int idxj,int count);

void AssignRincian(int idxi, int idxj, const char rincian_Obat[50][100], int count);

// void MappingDataObat();


#endif