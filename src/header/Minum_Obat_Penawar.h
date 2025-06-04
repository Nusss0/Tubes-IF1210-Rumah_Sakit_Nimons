#ifndef MINUM_OBAT_PENAWAR_H
#define MINUM_OBAT_PENAWAR_H

#include "ADT.h"
#include "user.h"

void GetDataInventLambung(char folder[]);
void CreateLambungInvent(InventLambungPasien *arr, int capacity);
void ReAllocLambungInvent(InventLambungPasien *arr, int add);
void InitLambung(int capacity);
/*------------------------------------------------------------- F16 - MINUM OBAT  -------------------------------------------------------------*/
void MenuMinumObat();
int CariData();
void PrintDaftarObat(int idxi, int idxj, int idxk);
void AddObatToLambung(int idx, int idObat);
void RemoveFromInvent(int idxi, int idxj, int idxr, int idxcount, int *idxObat);
void PrintTerurut();
void PrintStack();
/*------------------------------------------------------------- F17 - MINUM PENAWAR  -------------------------------------------------------------*/
void MenuMinumPenawar();
bool RemoveFromLambung(int *idObatOut);
void AddToInvent(int idxi, int idxj, int idObat);
void CekUrut(int i, int j, int idx, int idxObat);

#endif