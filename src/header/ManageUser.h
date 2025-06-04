#ifndef MANAGE_USER_H
#define MANAGE_USER_H


#include "ADT.h"
#include "user.h"
/*------------------------------------------------------------ F07 - Lihat User  ------------------------------------------------------------------*/

void MenuLihatUser(const char* role);
/*Menu Utama fitur lihat user*/

void PrintList();
/*Print Link dari user.csv yang sudah dibentuk sesuai format*/

void SortList(int op, int asc);
/*Sort Linklist*/

/*------------------------------------------------------------ F07 - Lihat User  ------------------------------------------------------------------*/
void MenuCariUser();
/*Menu Utama cari user*/
void CariUser(const char* target);
/*Binary Search buat nyari user*/


/*------------------------------------------------------------- F08 - TAMBAH DOKTER  -------------------------------------------------------------*/
//Khusus MANAGER
void MenuTambahDokter();
/* Meminta Input Username dan Password, memvalidasi apakah Username sudah ada? (case-insensitive), menambahkan ke dalam file "user", dan Output pesan yang sesuai */
/*fungsi lainnya: CreateUser, IsExists ada di user.h*/
// bool IsRoomAndDokterBusy(const char* target,const char* ruangan);
// //memberi true jika dokter sudah diassign dan room sudah ditempati
bool IsDokterAssigned (const char* target);
//memberi true jika dokter sudah diassign
bool IsDokterExist(const char* target);
// True jika username dokter sudah ada
bool IsRoomOccupied (const char* ruangan,const char* target);
// True jika ruangan sudah di huni oleh dokter
void AssignDokter(char username[], char ruangan[]);
// assign dokter
void MenuAssignDokter();
#endif