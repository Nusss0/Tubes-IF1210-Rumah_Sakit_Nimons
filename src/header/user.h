#ifndef HADER_H
#define HEADER_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include "ADT.h"
#include "ManageUser.h"


void DynData(char folder[]);
/*Membantuk Dynamic List dari User.csv*/


// listUser* createLink(dataUser x);
// /*Membuat LinkedList dari data x*/
// void insertLink(dataUser x);
// /*Memasukan data x ke link terakhir*/

/*------------------------------------------------------------- F01 - LOGIN -------------------------------------------------------------*/ 

//Fungsi 
void MenuLogin();
/* Meminta Input Username dan Password dari user, memvalidasi kecocokan, lalu Mengembalikan Pesan yang sesuai  */

void GetField(const char *line,char field[][100]);
/* Mengambil data perbaris di file .csv dan simpan ke array field*/

int GetData(char* username, const char* password);
/* Mengambil data User dari file .csv dan simpan ke variable jika Usernam dan Passsword sesuai*/

void CreateList(arrList* arr,int capacity );
/*SetUp list awal*/
void ReAllocList(arrList* arr,int add);
/*Alokasi Ulang memory di List*/

/*------------------------------------------------------------- F02 - REGISTER  -------------------------------------------------------------*/
//Khusus PASIEN
void MenuRegister();
/* Meminta Input Username dan Password, memvalidasi apakah Username sudah ada? (case-insensitive), menambahkan ke dalam file "user", dan Output pesan yang sesuai */

bool IsUserExist(char username[]);
/* Mengembalikan True jika Username sudah digunakan */
/*Pake getField yang ada di fungsi Login, nnti cek strcmp(field[1],username)*/
/*Cara Akses file nya bisa liat di getDatanya*/

void AddUser(char username[],char password[], char role[]);
/* Memasukan Data user ke dalam file "user.csv" */

/*------------------------------------------------------------ F03 - LOGOUT  ------------------------------------------------------------------*/

void ResetData(dataUser *x);
/* Mereset data User yang tersimpan di Variable */

/*------------------------------------------------------------ F04 - LUPA PASSWORD  ------------------------------------------------------------------*/

void MenuLupaPassword();
/* Meminta input Username dan Kode Unik dari user, memvalidasi Username, meminta input Password baru */

char* RunLengthEncoding (const char* username);
/*Generate Code Unik*/

void RenewPass(const char* username, const char* password);
/*Update Password baru ke List Dinamis*/
/*------------------------------------------------------------ F05 - HELP  ------------------------------------------------------------------*/
void MenuHelp();
/* Print Output sesuai spesifikasi dari Role */
void HelpDokter();
void HelpManager();
void HelpPasien();
void HelpNonLogin();
void Footnote();








#endif
