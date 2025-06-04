#ifndef DENAH_H
#define DENAH_H
/*------------------------------------------------------------ F06 - DENAH RUMAH SAKIT  ------------------------------------------------------------------*/
void CreateDenah(char folder[]);
/*Membuat Denah Awal*/

void StateConfig(char folder[]);
/*Membaca file config*/

void resetField();
/*Reset Field agar tidak overlap*/


void AllocDenah(int row,int col);
/*Alokasi Memori ke data tiap denah*/

void ReAllocDenah(int row,int col);
/*reAlokasi Memori ke data tiap denah*/


void AssignRuang(int row,int col);
/*Mengassign Nama tiap ruangan di List Denah*/

void PrintPembatas();
/*Print +---- sebagai pembatas untuk memperindah tampilan denah*/

void PrintDenah();
/*Print Interface Denah*/

void RemakeDenah(int row,int col);
/*Menu Khusus Manager jika ingin mengubah ukuran denah*/

void PindahDokter(char ruang1[], char ruang2[]);
/* Memindahkan dokter dari ruang1 ke ruang 2 jika ruang 2 kosong*/
bool IsDocterInRoom(int col, int row);
/*Cek apakah dokter berada di ruangan yang ingin di Ubah*/
    
void PrintDataRuangan( char* ruang);
/*Print data pada suatu ruangan*/


#endif