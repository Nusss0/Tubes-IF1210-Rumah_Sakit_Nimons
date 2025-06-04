#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#include "../header/user.h"
#include "../header/ManageUser.h"
#include "../header/ADT.h"

/*------------------------------------------------------------ F07 - Lihat user  ------------------------------------------------------------------*/
void MenuLihatUser(const char* role) {
    int op;
    int asc;

    printf("=====================================================\n");
    printf("                 MENU LIHAT DATA USER               \n");
    printf("=====================================================\n");

    printf("Urutkan berdasarkan:\n");
    printf("1. ID\n");
    printf("2. Nama\n");
    if(strcmp(role,"dokter")==0) printf("3. Aura\n");
    printf(">> Pilihan : ");
    scanf("%d", &op);

    printf("\nUrutan Sort:\n");
    printf("1. ASC (A-Z)\n");
    printf("2. DESC (Z-A)\n");
    printf(">> Pilihan : ");
    scanf("%d", &asc);

    if ((op == 1 || op == 2 || op==3) && (asc == 1 || asc == 2)) {
        printf("\n=====================================================\n");
        if (op == 1) {
            if (asc == 1) printf("Menampilkan semua pengguna dengan ID (Ascending)...\n");
            else printf("Menampilkan semua pengguna dengan ID (Descending)...\n");
        } 
        else if(op ==2){
            if (asc == 1) printf("Menampilkan semua pengguna dengan Nama (A-Z)...\n");
            else printf("Menampilkan semua pengguna dengan Nama (Z-A)...\n");
        }
        else if(op==3 && strcmp(role,"dokter")==0){
            if (asc == 1) printf("Menampilkan semua pengguna dengan Aura (Ascending)...\n");
            else printf("Menampilkan semua pengguna dengan Aura (Descending)...\n");
        }
        printf("=====================================================\n");

        SortList(op, asc);
        PrintList(role);
    } else {
        printf("\nInput tidak valid. Silakan pilih angka yang sesuai.\n");
    }

    // Reset urutan default ke ID Ascending
    SortList(1, 1);
}




void PrintList(const char* role) {
    if (arr_User.nEff == 0) {
        printf("Data user kosong.\n");
        return;
    }

    int printed_Header = 0;
    for (int i = 0; i < arr_User.nEff; i++) {
        // Skip manager
        if (strcasecmp(arr_User.arr[i].role, "manager") == 0) continue;

        // Cek apakah user sesuai role yang diminta
        if (strcasecmp(role, "all") == 0 || strcasecmp(role, arr_User.arr[i].role) == 0) {
            
            // Jika role bukan dokter, tampilkan semua data kesehatan
            if (strcasecmp(arr_User.arr[i].role, "dokter") != 0) {
                if (!printed_Header) {
                    printf("ID   | Username         | Password       | Role    | Penyakit               | Suhu | Sis | Dias | Detak | O2   | Gula | Berat | Tinggi | Kol  | Trom\n");
                    printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
                    printed_Header = 1;
                }

                printf("%-4d | %-16s | %-14s | %-7s | %-21s | %-4.1f | %-3d | %-4d | %-5d | %-4.1f | %-5d | %-5.1f | %-6d | %-5d | %-4d\n",
                    arr_User.arr[i].id,
                    arr_User.arr[i].username,
                    arr_User.arr[i].password,
                    arr_User.arr[i].role,
                    arr_User.arr[i].penyakit,
                    arr_User.arr[i].suhuTubuh,
                    arr_User.arr[i].tekanan_Darah_Sistolik,   
                    arr_User.arr[i].tekanan_Darah_Diastolik,  
                    arr_User.arr[i].detak_Jantung,
                    arr_User.arr[i].saturasi_Oksigen,
                    arr_User.arr[i].kadar_Gula_Darah,
                    arr_User.arr[i].berat_Badan,
                    arr_User.arr[i].tinggi_Badan,
                    arr_User.arr[i].kadar_Kolesterol,        
                    arr_User.arr[i].trombosit
                );
            }

            // Jika role = dokter, tampilkan versi ringkas
            else {
                if (!printed_Header) {
                    printf("ID   | Username         | Password       | Role    | Aura   \n");
                    printf("------------------------------------------------------------\n");
                    printed_Header = 1;
                }

                printf("%-4d | %-16s | %-14s | %-7s | %-5d\n",
                    arr_User.arr[i].id,
                    arr_User.arr[i].username,
                    arr_User.arr[i].password,
                    arr_User.arr[i].role,
                    arr_User.arr[i].aura
                );
            }
        }
    }
}


void SortList(int op, int asc) {
    if (arr_User.nEff == 0) return;
    bool swapped;
    do {
        swapped = false;
        int i =0;
        while (i < arr_User.nEff-1) {
            if ((op==1 && asc==1 && arr_User.arr[i].id > arr_User.arr[i+1].id) || 
                (op==1 && asc==2 && arr_User.arr[i].id < arr_User.arr[i+1].id) ||
                (op==2 && asc==1 && strcmp(arr_User.arr[i].username,arr_User.arr[i+1].username)>0) ||
                (op==2 && asc==2 && strcmp(arr_User.arr[i].username,arr_User.arr[i+1].username)<0) ||
                (op==3 && asc==1 && arr_User.arr[i].aura > arr_User.arr[i+1].aura) ||
                (op==3 && asc==2 && arr_User.arr[i].aura < arr_User.arr[i+1].aura))
            {
                dataUser temp = arr_User.arr[i];
                arr_User.arr[i] = arr_User.arr[i+1];
                arr_User.arr[i+1] = temp;
                swapped = true;
            }
            i++;
        }
    } while (swapped);
}

/*------------------------------------------------------------ F08 - Cari user  ------------------------------------------------------------------*/
void MenuCariUser() {
    int op;
    char find[50]; // ukuran diperbesar biar aman untuk username panjang

    printf("=====================================================\n");
    printf("                  MENU CARI DATA USER                \n");
    printf("=====================================================\n");
    printf("Cari berdasarkan:\n");
    printf("1. ID\n");
    printf("2. Username\n");
    printf("3. Aura\n");
    printf(">> Pilihan : ");
    scanf("%d", &op);

    switch (op) {
        case 1:
            printf("Masukkan nomor ID user: ");
            SortList(1, 1); // sort by ID ascending
            break;
        case 2:
            printf("Masukkan username user: ");
            SortList(2, 1); // sort by username ascending
            break;
        default:
            printf("Input tidak valid.\n");
            return;
    }

    scanf("%s", find);

    printf("\n=====================================================\n");
    printf("Hasil pencarian:\n");
    printf("-----------------------------------------------------\n");

    CariUser(find);

    // Reset sort ke default: by ID ASC
    SortList(1, 1);
}

void CariUser(const char* target) {
    int left = 0;
    int right = arr_User.nEff - 1;

    while (left <= right) {
        int mid = (left + right) / 2;

        if (arr_User.arr[mid].id == atoi(target) || strcasecmp(arr_User.arr[mid].username, target) == 0) {
            printf("=====================================================\n");
            printf("                    USER DITEMUKAN                  \n");
            printf("=====================================================\n");

            // Cek apakah user adalah dokter
            if (strcasecmp(arr_User.arr[mid].role, "dokter") == 0 || strcasecmp(arr_User.arr[mid].role, "manager") == 0) {
                printf("ID   | Username         | Password       | Role    \n");
                printf("--------------------------------------------------\n");
                printf("%-4d | %-16s | %-14s | %-7s\n",
                    arr_User.arr[mid].id,
                    arr_User.arr[mid].username,
                    arr_User.arr[mid].password,
                    arr_User.arr[mid].role
                );
            } else {
                printf("ID   | Username         | Password       | Role    | Penyakit               | Suhu | Sis | Dias | Detak | O2   | Gula | Berat | Tinggi | Kol  | Trom\n");
                printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
                printf("%-4d | %-16s | %-14s | %-7s | %-21s | %-4.1f | %-3d | %-4d | %-5d | %-4.1f | %-5d | %-5.1f | %-6d | %-5d | %-4d\n",
                    arr_User.arr[mid].id,
                    arr_User.arr[mid].username,
                    arr_User.arr[mid].password,
                    arr_User.arr[mid].role,
                    arr_User.arr[mid].penyakit,
                    arr_User.arr[mid].suhuTubuh,
                    arr_User.arr[mid].tekanan_Darah_Sistolik,
                    arr_User.arr[mid].tekanan_Darah_Diastolik,
                    arr_User.arr[mid].detak_Jantung,
                    arr_User.arr[mid].saturasi_Oksigen,
                    arr_User.arr[mid].kadar_Gula_Darah,
                    arr_User.arr[mid].berat_Badan,
                    arr_User.arr[mid].tinggi_Badan,
                    arr_User.arr[mid].kadar_Kolesterol,
                    arr_User.arr[mid].trombosit
                );
            }
            return;
        } else if ((arr_User.arr[mid].id < atoi(target)) || (strcasecmp(arr_User.arr[mid].username, target) < 0)) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    printf("=====================================================\n");
    printf("               USER TIDAK DITEMUKAN :(              \n");
    printf("=====================================================\n");
}


/*------------------------------------------------------------ F09 - Lihat Antrian  ------------------------------------------------------------------*/
