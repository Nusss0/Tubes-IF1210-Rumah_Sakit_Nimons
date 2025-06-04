#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#include "../header/ADT.h"
#include "../header/user.h"
#include "../header/ManageUser.h"
#include "../header/Save_Load.h"

#define MAX_LENGTH 50

/*------------------------------------------------------------- F10 - TAMBAH DOKTEr  -------------------------------------------------------------*/
//Khusus MANAGER
void MenuTambahDokter()
/* Meminta input username & password untuk dokter baru, mengecek duplikasi, lalu menambahkan ke dalam sistem */
{
    char username[MAX_LENGTH];
    char password[MAX_LENGTH];

    printf("═══════════════════════════════════════════════════\n");
    printf("🩺  Tambah Dokter Baru\n");
    printf("═══════════════════════════════════════════════════\n");

    // Input username
    printf("👤  Username Dokter   : ");
    scanf("%s", username);

    // Validasi username
    if (IsUserExist(username)) {
        printf("⚠️  Sudah ada dokter bernama '%s' dalam sistem.\n", username);
        printf("❌ Gagal menambahkan dokter.\n\n");
        return;
    }

    // Input password
    printf("🔒  Password Dokter   : ");
    scanf("%s", password);

    // Simpan ke user dan array dokter
    AddUser(username, password, "dokter");

    strcpy(arr_Dokter.data[arr_Dokter.nEff].username, username);
    arr_Dokter.data[arr_Dokter.nEff].id = arr_User.nEff - 1;
    arr_Dokter.data[arr_Dokter.nEff].room = false;
    arr_Dokter.nEff++;

    printf("\n✅ Dokter '%s' berhasil ditambahkan ke dalam sistem!\n\n", username);
}


bool IsDokterExist(const char* target)
{

    for(int i =0;i<arr_Dokter.nEff;i++){
        if (strcasecmp(target,arr_Dokter.data[i].username)==0)
        {
           return true;
        }
        
    }
    return false; 
}

// bool isRoomAndDokterBusy (const char* target,const char* ruangan)
//  //ngecek room dipake or dokter udah di assign, dan ngeassign dokter kalo dia memenuhi kondisi
// {
//     if (IsRoomOccupied(ruangan) && IsDokterAssigned(target))
//     {
//         printf("Dokter %s sudah menempati ruangan %s.\nsilahkan cari ruangan lain untuk Dokter %s.\n",denah.data[i][j].namadokter,denah.data[i][j].namaruang,target);
//         printf("Dokter %s juga sudah diassign ke ruangan %s.\n", denah.data[i][j].namadokter, denah.data[i][j].namaruang);
//         return true;
//     }
//     return false;
// }

bool IsDokterAssigned (const char* target)
// Mengecek apakah dokter sudah ter-assign ke suatu ruangan dalam denah
{
    for(int i=0;i<denah.row;i++){
        for(int j = 0 ;  j<denah.col;j++){
            if (strcmp(denah.data[i][j].nama_dokter , target)==0){
                printf("╔════════════════════════════════════════════╗\n");
                printf("║ ⚠️  Dokter %-25s ║\n", denah.data[i][j].nama_dokter);
                printf("║ ✅ Sudah di-assign ke ruangan %-10s ║\n", denah.data[i][j].nama_ruang);
                printf("╚════════════════════════════════════════════╝\n\n");
                return true;
            }
        }
    }
    return false;
}


bool IsRoomOccupied(const char* ruangan, const char* target) {
    for (int i = 0; i < denah.row; i++) {
        for (int j = 0; j < denah.col; j++) {
            if (strcmp(denah.data[i][j].nama_ruang, ruangan) == 0 &&
                denah.data[i][j].nama_dokter[0] != '-' && denah.data[i][j].nama_dokter[0] != '\0') {
                
                printf("=====================================================\n");
                printf("     ❌ Ruangan %s sudah ditempati oleh Dokter %s\n", 
                       denah.data[i][j].nama_ruang, denah.data[i][j].nama_dokter);
                printf("     ⚠️  Silakan pilih ruangan lain untuk Dokter %s.\n", target);
                printf("=====================================================\n");
                return true;
            }
        }
    }
    return false;
}


void MenuAssignDokter()
{
    char username[MAX_LENGTH];
    char ruangan[MAX_LENGTH];

    printf("╔══════════════════════════════════════════════════════╗\n");
    printf("║                  📋 Daftar Dokter                    ║\n");
    printf("╚══════════════════════════════════════════════════════╝\n");

    for (int i = 0; i < arr_Dokter.nEff; i++) {
        printf("• Dokter %-20s ", arr_Dokter.data[i].username);
        if (arr_Dokter.data[i].room == true) {
            printf("🟢 Diassign: %s\n", arr_Dokter.data[i].nama_ruang);
        } else {
            printf("🔴 Belum di-assign\n");
        }
    }

    printf("\n👨‍⚕️ Input Username Dokter yang ingin di-assign: ");
    scanf("%s", username);

    if (!IsDokterExist(username)) {
        printf("❌ Tidak ada Dokter dengan nama \"%s\".\n\n", username);
        return;
    }

    if (IsDokterAssigned(username)) {
        return;
    }

    printf("🏥 Masukkan Nama Ruangan Tujuan (Contoh: A1, B2): ");
    scanf("%s", ruangan);

    if (!IsRoomOccupied(ruangan, username)) {
        AssignDokter(username, ruangan);
        printf("✅ Dokter \"%s\" berhasil di-assign ke ruangan \"%s\"!\n\n", username, ruangan);

        for (int i = 0; i < arr_Dokter.nEff; i++) {
            if (strcasecmp(arr_Dokter.data[i].username, username) == 0) {
                arr_Dokter.data[i].room = true;
                break;
            }
        }
    }
}


void AssignDokter(char username[],char ruangan[])
{
    
    char str1 ='A';
    int str2 =1;

    char word=ruangan[0];
    int num = atoi(&ruangan[1]);
    for(int i = 0 ; i<denah.row;i++){
        for(int j = 0; j<denah.col;j++){
            if (str1==word && str2==num)
            {
                strcpy(denah.data[i][j].nama_dokter,username);
            }
                str2++;
        }
        str1++;
        str2 =1;
    }
    for(int i=0;i<arr_Dokter.nEff;i++){
        if(strcmp(arr_Dokter.data[i].username,username)==0) strcpy(arr_Dokter.data[i].nama_ruang,ruangan);
    }
}


/*----------------------------------------------------------------------------------------------------------------------------------*/