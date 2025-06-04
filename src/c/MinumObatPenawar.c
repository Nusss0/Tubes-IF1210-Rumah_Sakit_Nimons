#include "../header/ADT.h"
#include "../header/denah.h"
#include "../header/user.h"
#include "../header/daftar_checkup.h"
#include "../header/Minum_Obat_Penawar.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#define MAX_OBAT 50

void GetDataInventLambung(char folder[])
{
    CreateLambungInvent(&invent_Lambung, 50);
    char path[100];
    sprintf(path,"%s%s%s","file/",folder,"/config.txt");
    FILE* config = fopen(path,"r");
    if (!config)
    {
        printf("Gagal membuka file konfigurasi!\n");
        return;
    }

    char line[100];
    char field[50][100];

    fgets(line, sizeof(line), config);
    GetField(line, field);
    denah.col = atoi(field[1]);
    denah.row = atoi(field[0]);
    // printf("Ukuran denah: %d kolom x %d baris\n", denah.col, denah.row);

    for (int i = 0; i < denah.col * denah.row + 1; i++)
    {
        fgets(line, sizeof(line), config);
    }

    fgets(line, sizeof(line), config);
    GetField(line, field);
    int nInvent = atoi(field[0]);
    invent_Lambung.nInvent = nInvent;
    invent_Lambung.nEff = 0; // reset
    // printf("Jumlah data invent: %d\n", nInvent);
    int x = 0;
    int y = 0;
    InitLambung(MAX_OBAT);
    for (int j = 0; j < nInvent; j++)
    {
        // clear field
        for (int f = 0; f < 50; f++)
            field[f][0] = '\0';

        fgets(line, sizeof(line), config);
        GetField(line, field);

        int idP = atoi(field[0]);
        int idx = invent_Lambung.nEff++;
        invent_Lambung.data[idx].idPasien = idP;
        invent_Lambung.data[idx].invent.jumlahObat = 0;

        // printf("Pasien %d (invent):\n", idP);
        // baca semua obat
        for (int k = 1; k < 50 && field[k][0] != '\0'; k++)
        {
            int idO = atoi(field[k]);
            invent_Lambung.data[idx].invent.idObat[k - 1] = idO;
            invent_Lambung.data[idx].invent.jumlahObat++;
            // printf("  Obat: %d\n", invent_Lambung.data[idx].invent.idObat[k - 1]);

            bool found = false;
            while (x < denah.row && found == false)
            {
                y = 0;
                // printf("%d", i);
                while (y < denah.col && found == false)
                {
                    // printf("%d", j);
                    if (denah.data[x][y].Pasien->data.id == idP)
                    {
                        found = true;
                    }
                    else
                        y++;
                }
                x++;
                if (found == true)
                    x--;
            }
            // int count = 0;
            for (int a = 0; a < arr_Obat.nEff_Obat; a++)
            {
                // printf("DEBUG: namaobat %s\n", arr_Obat.data_Obat[a].nama_Obat);
                if (idO == arr_Obat.data_Obat[a].id_Obat)
                {
                    // printf("DEBUG: namaobattssts %s\n", arr_Obat.data_Obat[a].nama_Obat);
                    strcpy(denah.data[x][y].Pasien->rincianObat[k - 1], arr_Obat.data_Obat[a].nama_Obat);
                    break;
                }
            }
        }
        // printf("JUML:%d\n", invent_Lambung.data[idx].invent.jumlahObat);
        // printf("idP: %d\n", invent_Lambung.data[idx].idPasien);
    }

    fgets(line, sizeof(line), config);
    GetField(line, field);
    int nLambung = atoi(field[0]);
    invent_Lambung.nLambung = nLambung;
    // printf("Jumlah pasien berlambung: %d\n", nLambung);

    for (int u = 0; u < nLambung; u++)
    {
        // clear field
        for (int f = 0; f < 50; f++)
            field[f][0] = '\0';

        fgets(line, sizeof(line), config);
        GetField(line, field);

        int idP = atoi(field[0]);
        // cari atau tambahkan pasien
        int idx = -1;
        for (int t = 0; t < invent_Lambung.nEff; t++)
        {

            if (invent_Lambung.data[t].idPasien == idP)
            {
                // printf("\nidp: %d\n",idP);
                idx = t;
                break;
            }
        }
        if (idx == -1)
        {
            // pasien baru
            idx = invent_Lambung.nEff++;
            invent_Lambung.data[idx].idPasien = idP;
            invent_Lambung.data[idx].invent.jumlahObat = 0;
            // printf("Pasien %d ditambahkan tanpa invent\n", idP);
        }

        // init stack
        invent_Lambung.data[idx].lambung.top = -1;
        invent_Lambung.data[idx].lambung.data.jumlahObat = 0;

        // hitung jumlah obat di field
        int obatCount = 0;
        for (int k = 1; k < 50 && field[k][0] != '\0'; k++)
            obatCount++;

        // push dari depan ke belakang
        for (int k = 1 ; k <=obatCount; k++)
        {
            int idO = atoi(field[k]);
            if (invent_Lambung.data[idx].lambung.top < MAX_OBAT - 1)
            {
                invent_Lambung.data[idx].lambung.top++;
                invent_Lambung.data[idx].lambung.data.idObat[invent_Lambung.data[idx].lambung.top] = idO;
                invent_Lambung.data[idx].lambung.data.jumlahObat++;
                invent_Lambung.data[idx].isMinum ++;
                CekUrut(x,y,idx,idO);
                // printf("Pasien %d - Obat di lambung (stack posisi %d): %d\n", idP, invent_Lambung.data[idx].lambung.top, idO);
            }
        }
    }
    // printf("%d",invent_Lambung.nEff);
    fclose(config);
}
// Inisialisasi data inventory User
void CreateLambungInvent(InventLambungPasien *arr, int capacity)
{
    arr->data = (DataPasien *)malloc(capacity * sizeof(DataPasien));
    arr->capacity = capacity;
    arr->nEff = 0;
}

void InitLambung(int capacity)
{
    if (capacity > MAX_OBAT)
    {
        capacity = MAX_OBAT;
    }
    for (int idx = 0; idx < invent_Lambung.capacity; idx++)
    {
        // printf("DEBUG:{IDX: %d}",idx);
        invent_Lambung.data[idx].pulang = false;
        invent_Lambung.data[idx].lambung.top = -1;
        invent_Lambung.data[idx].lambung.capacity = capacity;
        invent_Lambung.data[idx].lambung.data.jumlahObat = 0;
        invent_Lambung.data[idx].isMinum = 0;
        invent_Lambung.data[idx].urut = false;
    }
}
void ReAllocLambungInvent(InventLambungPasien *arr, int add)
{
    arr->data = (DataPasien *)realloc(arr->data, (arr->capacity + add) * sizeof(DataPasien));
    arr->capacity += add;
}

/*------------------------------------------------------------- F16 - MINUM OBAT  -------------------------------------------------------------*/

int CariData()
{
    int i = 0;
    bool found = false;
    while (i < invent_Lambung.nEff && found == false)
    {
        if (invent_Lambung.data[i].idPasien == user.id)
        {
            found = true;
            // printf("%d",i);
            return i;
            break;
        }
        else
            i++;
    }
    // printf("DEBUG: {Cari index i error}\n");
    return -1;
}
void MenuMinumObat()
{
    int i = 0, j = 0;
    bool found = false;

    // Cari posisi pasien di denah
    while (i < denah.row && !found)
    {
        j = 0;
        while (j < denah.col && !found)
        {
            if (strcmp(denah.data[i][j].Pasien->data.username, user.username) == 0)
                found = true;
            else
                j++;
        }
        i++;
        if (found) i--;
    }

    int idx = CariData();
    char pilihan[100];

    PrintDaftarObat(i, j, idx);

    if (invent_Lambung.data[idx].invent.jumlahObat == 0)
        return;

    printf("🫙 Silakan ketik nama obat yang ingin diminum (atau ketik 'nvm' untuk batal):\n>> ");
    scanf("%s", pilihan);

    bool obatFound = false;
    while (!obatFound)
    {
        if (strcasecmp(pilihan, "nvm") == 0)
            return;

        for (int a = 0; a < arr_Obat.nEff_Obat; a++)
        {
            if (strcasecmp(pilihan, denah.data[i][j].Pasien->rincianObat[a]) == 0)
            {
                obatFound = true;
                break;
            }
        }

        if (!obatFound)
        {
            printf("⚠️  Obat '%s' tidak ditemukan dalam daftar! Coba lagi ya.\n>> ", pilihan);
            scanf("%s", pilihan);
        }
    }

    int l, k = 0;
    bool idxrfound = false;
    while (k < arr_Obat.nEff_Obat && !idxrfound)
    {
        l = 0;
        while (l < invent_Lambung.data[idx].invent.jumlahObat && !idxrfound)
        {
            if (
                strcasecmp(pilihan, denah.data[i][j].Pasien->rincianObat[l]) == 0 &&
                invent_Lambung.data[idx].invent.idObat[l] == arr_Obat.data_Obat[k].id_Obat &&
                strcasecmp(arr_Obat.data_Obat[k].nama_Obat, denah.data[i][j].Pasien->rincianObat[l]) == 0
            ) {
                printf("🥤 GLEKGLEKGLEK... Lezatt!!! Obat '%s' berhasil diminum!\n", pilihan);
                invent_Lambung.data[idx].isMinum += 1;
                idxrfound = true;
                break;
            }
            else l++;
        }
        if (!idxrfound) k++;
    }

    int idxObat;
    RemoveFromInvent(i, j, l, idx, &idxObat);
    CekUrut(i, j, idx, idxObat);
    AddObatToLambung(idx, idxObat);
}

// login neronimo pass10 diagnosis ngobatin logout login user2 pass22 debug Remdesivir

void RemoveFromInvent(int idxi, int idxj, int idxr, int idx, int *idxObat)
{
    int count = invent_Lambung.data[idx].invent.jumlahObat;
    // printf("jumlahObat awal: %d\n", count);

    *idxObat = invent_Lambung.data[idx].invent.idObat[idxr];
    // printf("Assigned to *idxObat: %d\n", *idxObat);

    // strcpy(denah.data[idxi][idxj].Pasien->rincianObat[idxr], "");
    // invent_Lambung.data[idx].invent.idObat[idxr] = -1;
    for (int i = idxr; i < count; i++)
    {
        // printf("Before: %s-%d\n", denah.data[idxi][idxj].Pasien->rincianObat[i], invent_Lambung.data[idx].invent.idObat[i]);
        strcpy(denah.data[idxi][idxj].Pasien->rincianObat[i], denah.data[idxi][idxj].Pasien->rincianObat[i + 1]);
        invent_Lambung.data[idx].invent.idObat[i] = invent_Lambung.data[idx].invent.idObat[i + 1];
        // printf("After: %s-%d\n", denah.data[idxi][idxj].Pasien->rincianObat[i], invent_Lambung.data[idx].invent.idObat[i]);
    }

    invent_Lambung.data[idx].invent.jumlahObat--;
    // printf("jumlahObat sesudah dikurangi: %d\n", invent_Lambung.data[idx].invent.jumlahObat);
}

void CekUrut(int i, int j, int idx, int idxObat)
{
    for (int a = 0; a < arr_Obat.nEff_Penyakit; a++)
    {

        if (arr_Obat.data_Obat_penyakit[a].id_Obat == idxObat)
        {
            if (arr_Obat.data_Obat_penyakit[a].urutan_Minum == invent_Lambung.data[idx].isMinum && strcasecmp(denah.data[i][j].Pasien->data.penyakit, arr_Obat.data_Obat_penyakit[a].nama_Penyakit) ==0)
            {
                // printf("%d-%d",arr_Obat.data_Obat_penyakit[a].urutan_Minum, invent_Lambung.data[idx].isMinum);
                invent_Lambung.data[idx].urut = true;
                // printf("truu:%d---isminum:%d\n", invent_Lambung.data[idx].urut, invent_Lambung.data[idx].isMinum);
                return;
            }
        }
    }
    // printf("false:%d---isminum:%d\n", invent_Lambung.data[idx].urut, invent_Lambung.data[idx].isMinum);
    invent_Lambung.data[idx].urut = false;
}
// void PrintTerurut() {
//     // Cari penyakit user berdasarkan username
//     char *penyakitUser = NULL;
//     int i = 0, j = 0;
//     bool found = false;

//     while (i < denah.row && !found) {
//         j = 0;
//         while (j < denah.col && !found) {
//             if (strcmp(denah.data[i][j].Pasien->data.username, user.username) == 0) {
//                 penyakitUser = denah.data[i][j].Pasien->data.penyakit;
//                 found = true;
//             } else {
//                 j++;
//             }
//         }
//         i++;
//         if (found) i--;
//     }

//     if (penyakitUser == NULL) {
//         printf("⚠️  Penyakit pasien tidak ditemukan.\n");
//         return;
//     }

//     int urutan[50];
//     char namaObat[50][100];
//     int count = 0;

//     // Ambil semua obat untuk penyakit user
//     for (int a = 0; a < arr_Obat.nEff_Penyakit; a++) {
//         if (strcasecmp(arr_Obat.data_Obat_penyakit[a].nama_Penyakit, penyakitUser) == 0) {
//             urutan[count] = arr_Obat.data_Obat_penyakit[a].urutan_Minum;

//             for (int b = 0; b < arr_Obat.nEff_Obat; b++) {
//                 if (arr_Obat.data_Obat_penyakit[a].id_Obat == arr_Obat.data_Obat[b].id_Obat) {
//                     strcpy(namaObat[count], arr_Obat.data_Obat[b].nama_Obat);
//                     break;
//                 }
//             }

//             count++;
//         }
//     }

//     for (int m = 0; m < count - 1; m++) {
//         for (int n = m + 1; n < count; n++) {
//             if (urutan[m] > urutan[n]) {
//                 int tmpU = urutan[m];
//                 urutan[m] = urutan[n];
//                 urutan[n] = tmpU;

//                 char tmpNama[100];
//                 strcpy(tmpNama, namaObat[m]);
//                 strcpy(namaObat[m], namaObat[n]);
//                 strcpy(namaObat[n], tmpNama);
//             }
//         }
//     }

//     // Cetak hasil
//     if (count == 0) {
//         printf("⚠️  Tidak ada data obat untuk penyakit %s.\n", penyakitUser);
//     } else {
//         for (int x = 0; x < count; x++) {
//             printf("%s",  namaObat[x]);
//             if(x != count-1) printf(" -> ");
//         }
//         printf("\n");
//     }
// }

// void PrintStack(){
//     for(int i=0;i<invent_Lambung.nEff;i++){
//         if(invent_Lambung.data[i].idPasien == user.id){
//             for(int k=0;k<=invent_Lambung.data[i].lambung.top;k++){
//                 for(int j=0;i<arr_Obat.nEff_Obat;j++){
//                     if(arr_Obat.data_Obat[i].id_Obat == invent_Lambung.data[i].lambung.data.idObat[k])
//                     printf("%s",arr_Obat.data_Obat->nama_Obat);
//                 }
//                 if(k!= invent_Lambung.data[i].lambung.top) printf(" -> ");
//             }
//             printf("\n");
//             break;
//         }
//     }
// }


void AddObatToLambung(int idx, int idObat)
{
    if (invent_Lambung.data[idx].lambung.top >= invent_Lambung.data[idx].lambung.capacity - 1)
    {
        printf("\n⚠️  PERUT KAMU FULL!!\n");
        printf("[WARN] Lambung pasien ID %d sudah penuh. (top = %d / cap = %d)\n",
               invent_Lambung.data[idx].lambung.data.idPasien,
               invent_Lambung.data[idx].lambung.top,
               invent_Lambung.data[idx].lambung.capacity - 1);
        return;
    }

    invent_Lambung.data[idx].lambung.top++;
    invent_Lambung.data[idx].lambung.data.idObat[invent_Lambung.data[idx].lambung.top] = idObat;
    invent_Lambung.data[idx].lambung.data.jumlahObat++;
    invent_Lambung.data[idx].idPasien = user.id;

    // printf("[INFO] Obat ID %d berhasil ditambahkan ke lambung pasien ID %d di posisi %d.\n",
    //        invent_Lambung.data[idx].lambung.data.idObat[invent_Lambung.data[idx].lambung.top],
    //        invent_Lambung.data[idx].idPasien,
    //        invent_Lambung.data[idx].lambung.top);
}


// void RemoveFromLambung()

void PrintDaftarObat(int idxi, int idxj, int idxk)
{
    bool adaObat = false;
    printf("\n🧾========== DAFTAR OBAT KAMU ==========\n");

    for (int k = 0; k < invent_Lambung.data[idxk].invent.jumlahObat; k++)
    {
        for (int l = 0; l < arr_Obat.nEff_Obat; l++)
        {
            if (invent_Lambung.data[idxk].invent.idObat[k] == arr_Obat.data_Obat[l].id_Obat)
            {
                printf("  %d. %s\n", k + 1, arr_Obat.data_Obat[l].nama_Obat);
                adaObat = true;
                break;
            }
        }
    }

    if (!adaObat)
    {
        printf("⚠️  Kamu belum punya obat apapun!\n");
    }
    else
    {
        printf("\n💬 Mau minum obat yang mana nih? (Contoh: Remdesivir)\n");
        printf("Ketik \"nvm\" untuk batal minum.\n>> ");
    }
}


// login neronimo pass10 diagnosis ngobatin logout login user2 pass22 debug remdesivir

/*------------------------------------------------------------- F17 - MINUM PENAWAR   -------------------------------------------------------------*/

void MenuMinumPenawar()
{
    int idObatOut;
    int i = 0, j = 0;
    bool found = false;

    // Cari posisi pasien di denah
    while (i < denah.col && !found)
    {
        j = 0;
        while (j < denah.row && !found)
        {
            if (strcmp(denah.data[i][j].Pasien->data.username, user.username) == 0)
            {
                found = true;
            }
            else
                j++;
        }
        i++;
        if (found) i--;
    }

    // Coba keluarkan obat dari lambung
    if (RemoveFromLambung(&idObatOut))
    {
        for (int l = 0; l < arr_Obat.nEff_Obat; l++)
        {
            if (idObatOut == arr_Obat.data_Obat[l].id_Obat)
            {
                printf("\n🤮 Uwekkk!!! Obat %s keluar dan kembali ke inventory!\n", arr_Obat.data_Obat[l].nama_Obat);
                break;
            }
        }
        AddToInvent(i, j, idObatOut);
    }
    else
    {
        printf("\n⚠️  Perut kamu masih kosong, belum ada obat yang diminum!\n");
    }
}


bool RemoveFromLambung(int *idObatOut)
{
    int idxr = CariData();
    if (invent_Lambung.data[idxr].lambung.top < 0)
    {
        return false; // Stack kosongs
    }
    *idObatOut = invent_Lambung.data[idxr].lambung.data.idObat[invent_Lambung.data[idxr].lambung.top];
    // printf("DEBUG: {id obat: %d}\n", *idObatOut);
    // printf("DEBUG: {top before: %d}\n", invent_Lambung.data[idxr].lambung.top);
    invent_Lambung.data[idxr].lambung.top--;
    // printf("DEBUG: {top after: %d}\n", invent_Lambung.data[idxr].lambung.top);
    // printf("DEBUG: {jumlah obat before: %d}\n", invent_Lambung.data[idxr].lambung.data.jumlahObat);
    invent_Lambung.data[idxr].lambung.data.jumlahObat--;
    // printf("DEBUG: {jumlah obat after: %d}\n", invent_Lambung.data[idxr].lambung.data.jumlahObat);
    invent_Lambung.data[idxr].isMinum--;
    return true;
}

void AddToInvent(int idxi, int idxj, int idObat)
{
    int idx = CariData();
    // printf("jumlahObat awal: %d\n", invent_Lambung.data[idx].invent.jumlahObat);
    for (int i = invent_Lambung.data[idx].invent.jumlahObat; i > 0; i--)
    {
        strcpy(denah.data[idxi][idxj].Pasien->rincianObat[i], denah.data[idxi][idxj].Pasien->rincianObat[i - 1]);
        invent_Lambung.data[idx].invent.idObat[i] = invent_Lambung.data[idx].invent.idObat[i - 1];
        // printf("After: %s\n", denah.data[idxi][idxj].Pasien->rincianObat[i]);
        // printf("After: %d\n", invent_Lambung.data[idx].invent.idObat[i]);
    }
    invent_Lambung.data[idx].invent.idObat[0] = idObat;
    for (int j = 0; j < arr_Obat.nEff_Obat; j++)
    {
        if (arr_Obat.data_Obat[j].id_Obat == idObat)
        {
            // printf("DEBUG:{%s}\n", arr_Obat.data_Obat[j].nama_Obat);
            strcpy(denah.data[idxi][idxj].Pasien->rincianObat[0], arr_Obat.data_Obat[j].nama_Obat);
        }
    }
    // printf("After: %d\n", invent_Lambung.data[idx].invent.idObat[0]);
    invent_Lambung.data[idx].invent.jumlahObat++;
    // printf("jumlahObat sesudah ditambah: %d\n", invent_Lambung.data[idx].invent.jumlahObat);
}