#ifndef DAFTAR_CHECKUP_H
#define DAFTAR_CHECKUP_H

#include "ADT.h"
#include "denah.h"

void MenuDaftarCheckup();
void ValidasiInputData();
void PilihDokter();
void InsertLink(queue **q, dataUser x);
void PrintAntrian();
void InsertAntrian(int i, int j, char* nama_pasien,int urutan);
void PrintAntrianSaya();
void SkipAntrian();
#endif
