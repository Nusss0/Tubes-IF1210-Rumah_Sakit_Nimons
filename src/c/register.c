#include <string.h>
#include <stdio.h>
#include <stdbool.h>


#include "../header/ADT.h"
#include "../header/user.h"


#define MAX_LENGTH 50

/*------------------------------------------------------------- F02 - REGISTER  -------------------------------------------------------------*/
//Khusus PASIEN
void MenuRegister()
/* Meminta Input Username dan Password, memvalidasi apakah Username sudah ada? (case-insensitive), menambahkan ke dalam file "user", dan Output pesan yang sesuai */
{
    char username[MAX_LENGTH];
    char password1[MAX_LENGTH];
    char password2[MAX_LENGTH];

    printf("=====================================================\n");
    printf("                   REGISTRASI AKUN                  \n");
    printf("=====================================================\n");

    // Input username
    printf("Username               : ");
    scanf("%s", username);

    // Validasi username
    if (IsUserExist(username)) {
        printf("Registrasi gagal! Pasien dengan nama %s sudah terdaftar.\n", username);
        return;
    }

    // Input password
    printf("Password               : ");
    scanf("%s", password1);
    printf("Konfirmasi Password    : ");
    scanf("%s", password2);

    // Validasi password
    if (strcmp(password1, password2) != 0) {
        printf("Registrasi gagal! Password tidak cocok.\n");
        return;
    }

    // Tambah user ke sistem dan login otomatis
    AddUser(username, password1, "pasien");
    is_Logged_in = true;
    user.id = arr_User.nEff-1;
    strcpy(user.username,username);
    strcpy(user.password,password1);
    strcpy(user.role,"pasien");

    printf("=====================================================\n");
    printf("Selamat pagi %s! Ada keluhan apa?\n", username);
}


bool IsUserExist(char username[])
/* Mengembalikan True jika Username sudah digunakan */
{
    for(int i=0;i<arr_User.nEff;i++)
    {
        if(strcasecmp(arr_User.arr[i].username,username)==0)
        return true;
    }
    return false;
}

void AddUser(char username[],char password[], char role[])
/* Memasukan Data user ke dalam file "user.txt" */
{
    ResetData(&arr_User.arr[arr_User.nEff]);
    arr_User.arr[arr_User.nEff].aura = 0;
    arr_User.arr[arr_User.nEff].id = arr_User.nEff;
    strcpy(arr_User.arr[arr_User.nEff].username, username);
    strcpy(arr_User.arr[arr_User.nEff].password, password);
    strcpy(arr_User.arr[arr_User.nEff].role, role);
    arr_User.nEff ++;

}



/*----------------------------------------------------------------------------------------------------------------------------------*/