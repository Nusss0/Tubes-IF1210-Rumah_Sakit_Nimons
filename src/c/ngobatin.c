#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "../header/ADT.h"
#include "../header/user.h"
#include "../header/DiagnosisPenyakit.h"
#include "../header/ngobatin.h"
#include "../header/Save_Load.h"

#define MAX_LENGTH 50

void GetDataObat()
{
    CreateListObat(&arr_Obat, 100);
    FILE *fObat = fopen("file/obat.csv", "r");
    if (!fObat)
    {
        printf("File tidak Terbaca\n");
        fclose(fObat);
        return;
    }
    char line[100];
    char field[5][100];
    fgets(line, sizeof(line), fObat); // skip baca header
    int i = 0;
    // printf("%s", line);
    while (fgets(line, sizeof(line), fObat))
    {
        GetField(line, field);
        arr_Obat.data_Obat[i].id_Obat = atoi(field[0]);
        // printf("id obat:[%d]\n", arr_Obat.data_Obat[i].id_Obat);
        strcpy(arr_Obat.data_Obat[i].nama_Obat, field[1]);
        int len = strlen(arr_Obat.data_Obat[i].nama_Obat);
        while (len > 0 && (arr_Obat.data_Obat[i].nama_Obat[len - 1] == '\r' || arr_Obat.data_Obat[i].nama_Obat[len - 1] == '\n'))
        {
            arr_Obat.data_Obat[i].nama_Obat[len - 1] = '\0';
            len--;
        }
        // printf("DEBUG: [%s]\n",arr_Obat.data_Obat[i].nama_Obat);
        arr_Obat.nEff_Obat++;
        i++;
    }
    fclose(fObat);

    FILE *fObat_Penyakit = fopen("file/obat_penyakit.csv", "r");
    if (!fObat_Penyakit)
    {
        printf("File tidak Terbaca\n");
        fclose(fObat_Penyakit);
        return;
    }
    char linea[2048];
    char fielda[3][100];
    fgets(linea, sizeof(linea), fObat_Penyakit); // skip baca header
    // printf("%s", linea);
    i = 0;
    while (fgets(linea, sizeof(linea), fObat_Penyakit))
    {
        GetField(linea, fielda);
        arr_Obat.data_Obat_penyakit[i].id_Obat = atoi(fielda[0]);
        // printf("id penyakit obat: %d\n", arr_Obat.data_Obat_penyakit[i].id_Obat);
        arr_Obat.data_Obat_penyakit[i].id_Penyakit = atoi(fielda[1]);
        // printf("id penyakit: %d\n", arr_Obat.data_Obat_penyakit[i].id_Penyakit);
        arr_Obat.data_Obat_penyakit[i].urutan_Minum = atoi(fielda[2]);
        // printf("urutan minum: %d\n", arr_Obat.data_Obat_penyakit[i].urutan_Minum);

        arr_Obat.nEff_Penyakit++;
        i++;
    }
    fclose(fObat_Penyakit);

    for (int j = 0; j < arr_Obat.nEff_Penyakit; j++)
    {
        // printf("nama penyakit: %s::id penyakit: %d\n", arr_Obat.data_Obat_penyakit[j].nama_Penyakit,arr_Obat.data_Obat_penyakit[j].id_Penyakit);
        for (int k = 0; k < arr_Penyakit.nEff; k++)
        {
            // printf("nama penyakits: %s::id penyakits: %d\n", arr_Penyakit.arr[k].nama_Penyakit,arr_Penyakit.arr[k].id);
            if (arr_Obat.data_Obat_penyakit[j].id_Penyakit == arr_Penyakit.arr[k].id)
            {
                strcpy(arr_Obat.data_Obat_penyakit[j].nama_Penyakit, arr_Penyakit.arr[k].nama_Penyakit);
                // printf("jadi: nama penyakit: %s\n", arr_Obat.data_Obat_penyakit[j].nama_Penyakit);
                break;
            }
        }
        // printf("id obat:%d == id penyakit:%d == urutan:%d\n", arr_Obat.data_Obat_penyakit[j].id_Obat, arr_Obat.data_Obat_penyakit[j].id_Penyakit, arr_Obat.data_Obat_penyakit[j].urutan_Minum);
    }
}

void CreateListObat(arrObat *arr, int capacity)
{
    arr->data_Obat = (dataObat *)malloc(capacity * sizeof(dataObat));
    arr->data_Obat_penyakit = (mapObatPenyakit *)malloc(capacity * sizeof(mapObatPenyakit));
    arr->capacity = capacity;
    arr->nEff_Penyakit = 0;
    arr->nEff_Obat = 0;
}

void ReAllocListObat(arrObat *arr, int add)
{
    arr->data_Obat = (dataObat *)realloc(arr->data_Obat, (arr->capacity + add) * sizeof(dataObat));
    arr->data_Obat_penyakit = (mapObatPenyakit *)realloc(arr->data_Obat, (arr->capacity + add) * sizeof(mapObatPenyakit));
    arr->capacity += add;
}

/*------------------------------------------------------------- F12 - NGOBATIN  -------------------------------------------------------------*/
void MenuNgobatin()
{
    int i = 0, j = 0;
    bool found = false;

    // Cari posisi dokter di denah
    while (i < denah.row && !found)
    {
        j = 0;
        while (j < denah.col && !found)
        {
            if (strcmp(denah.data[i][j].nama_dokter, user.username) == 0)
            {
                found = true;
            }
            else
                j++;
        }
        i++;
        if (found) i--;
    }
    for(int x=0;x<invent_Lambung.nEff;x++){
        if(invent_Lambung.data[x].idPasien == denah.data[i][j].Pasien->data.id && (invent_Lambung.data[x].invent.idObat[0]!= 0 || invent_Lambung.data[x].lambung.data.idObat[0] !=0)){
            printf("\n⚠️  Pasien %s udah di-Obatin!\n", denah.data[i][j].Pasien->data.username);
            return;
        }
    }
    if (denah.data[i][j].Pasien != NULL &&strcasecmp(denah.data[i][j].Pasien->data.penyakit, "sehat") == 0) {

        printf("\n🩺 Pasien %s dinyatakan SEHAT! Tidak memerlukan pengobatan lebih lanjut.\n", denah.data[i][j].Pasien->data.username);
        invent_Lambung.data[invent_Lambung.nEff].idPasien = denah.data[i][j].Pasien->data.id;
        invent_Lambung.data[invent_Lambung.nEff].urut = true;
        invent_Lambung.nEff++;
        return;
    }

    if (!IsSakitValid(i, j))
    {
        bool isDoneBefore = false;
        for (int k = 0; k < invent_Lambung.nEff; k++)
        {
            if (denah.data[i][j].Pasien == NULL)
            {
                printf("Maaf Dok, antrian kosong.\n");
                return;
            }

            if (denah.data[i][j].Pasien->data.id == invent_Lambung.data[k].idPasien)
            {
                printf("\n🧾 Dokter %s sudah pernah mengobati pasien %s.\n", user.username, denah.data[i][j].Pasien->data.username);
                printf("📋 Data Pasien:\n");
                printf("   - Penyakit  : %s\n", denah.data[i][j].Pasien->data.penyakit);
                printf("   - Obat-obatan:\n");
                for (int l = 0; l < invent_Lambung.data[k].invent.jumlahObat; l++)
                {
                    for (int m = 0; m < arr_Obat.nEff_Obat; m++)
                    {
                        if (invent_Lambung.data[k].invent.idObat[l] == arr_Obat.data_Obat[m].id_Obat)
                            printf("     %d. %s\n", l + 1, arr_Obat.data_Obat[m].nama_Obat);
                    }
                }
                isDoneBefore = true;
                break;
            }
        }
        if (!isDoneBefore && !denah.data[i][j].Pasien->data.is_Diagnosed)
        {
            printf("\n⚠️  Pasien belum memiliki diagnosis penyakit!\n");
            printf("Silakan lakukan diagnosis terlebih dahulu.\n");
        }
    }

    if (IsSakitValid(i, j))
    {
        bool isNgobatin = false;
        for (int k = 0; k < invent_Lambung.nEff; k++)
        {
            if (denah.data[i][j].Pasien->data.id == invent_Lambung.data[k].idPasien)
            {
                printf("\n🧾 Dokter %s sudah pernah mengobati pasien %s.\n", user.username, denah.data[i][j].Pasien->data.username);
                printf("📋 Data Pasien:\n");
                printf("   - Penyakit  : %s\n", denah.data[i][j].Pasien->data.penyakit);
                printf("   - Obat-obatan:\n");
                for (int l = 0; l < invent_Lambung.data[k].invent.jumlahObat; l++)
                {
                    for (int m = 0; m < arr_Obat.nEff_Obat; m++)
                    {
                        if (invent_Lambung.data[k].invent.idObat[l] == arr_Obat.data_Obat[m].id_Obat)
                            printf("     %d. %s\n", l + 1, arr_Obat.data_Obat[m].nama_Obat);
                    }
                }
                isNgobatin = true;
                break;
            }
        }

        if (!isNgobatin)
        {
            printf("\n💊 Dokter %s sedang memberikan pengobatan pada pasien %s.\n",
                   user.username, denah.data[i][j].Pasien->data.username);
            printf("🦠 Penyakit yang diderita: %s\n", denah.data[i][j].Pasien->data.penyakit);
            printf("📦 Obat yang harus diberikan:\n");

            char rincian_Obat[50][100];
            RincianObat(i, j, rincian_Obat);
        }
    }
}

bool IsSakitValid(int idxi, int idxj)
{
    // printf("apa\n");
    if (denah.data[idxi][idxj].Pasien != NULL)
    {
        return (denah.data[idxi][idxj].Pasien->data.is_Diagnosed == true);
    }
    return false;
}

void RincianObat(int idxi, int idxj, char rincian_Obat[50][100])
{
    // asumsi obat per penyakit tidak lebih dari 20 untuk sementara, mungkin nanti pake dynamic
    memset(rincian_Obat, 0, sizeof(char) * 20 * 50);
    // ambil nama obat yang sesuai, store ke rincian_obat
    int i = 0;
    int count = 0;
    while (i < arr_Obat.nEff_Penyakit)
    {
        // printf("\n===%s:%s===\n", arr_Obat.data_Obat_penyakit[i].nama_Penyakit, denah.data[idxi][idxj].Pasien->data.penyakit);
        // printf("\naaa%d nama obat: %s\n",i, arr_Obat.data_Obat[i].nama_Obat);
        for (int j = 0; j < arr_Obat.nEff_Penyakit; j++)
        {
            if (strcmp(denah.data[idxi][idxj].Pasien->data.penyakit, arr_Obat.data_Obat_penyakit[i].nama_Penyakit) == 0)
            {
                if (arr_Obat.data_Obat_penyakit[i].id_Obat == arr_Obat.data_Obat[j].id_Obat)
                {
                    strcpy(rincian_Obat[count], arr_Obat.data_Obat[j].nama_Obat);
                    count++;
                }
            }
        }
        i++;
    }

    SortRincianObat(rincian_Obat, count);
    AssignRincian(idxi, idxj, rincian_Obat, count);
    PrintRincianObat(idxi, idxj, count);
}

void AssignRincian(int idxi, int idxj, const char rincian_Obat[50][100], int count)
{
    for (int i = 0; i < count; i++)
    {
        strcpy(denah.data[idxi][idxj].Pasien->rincianObat[i], rincian_Obat[i]);
    }
    bool inventInitializedAlready = false;
    // printf("a");
    for (int i = 0; i < invent_Lambung.nEff; i++)
    {
        for (int j = 0; j < arr_Obat.nEff_Obat; j++)
        {
            for (int k = 0; k < 50; k++)
            {
                // printf("DEBUGG:{ID: %d-%d-%s-%s}\n", invent_Lambung.data[i].idPasien, denah.data[idxi][idxj].Pasien->data.id, denah.data[idxi][idxj].Pasien->rincianObat[k], arr_Obat.data_Obat[j].nama_Obat);
                if (invent_Lambung.data[i].idPasien == denah.data[idxi][idxj].Pasien->data.id && strcasecmp(denah.data[idxi][idxj].Pasien->rincianObat[k], arr_Obat.data_Obat[j].nama_Obat) == 0)
                {
                    // printf("b");
                    for (int l = 0; l < count; l++)
                    {
                        invent_Lambung.data[i].invent.idObat[invent_Lambung.data[i].invent.jumlahObat] = arr_Obat.data_Obat[j].id_Obat;
                        inventInitializedAlready = true;
                    }
                    // printf("DEBUG: JUMLAH OBAT= %d\n", invent_Lambung.data[i].invent.jumlahObat);
                    invent_Lambung.data[i].invent.jumlahObat += count;
                    // printf("%d\n", invent_Lambung.data[i].idPasien);
                    // printf("DEBUG: JUMLAH OBAT= %d\n", invent_Lambung.data[i].invent.jumlahObat);
                }
            }
            if (inventInitializedAlready)
                break;
        }
        if (inventInitializedAlready)
            break;
    }
    if (!inventInitializedAlready)
    {
        int idxObat = 0;
        invent_Lambung.data[invent_Lambung.nEff].idPasien = denah.data[idxi][idxj].Pasien->data.id;
        // printf("%d", invent_Lambung.data[invent_Lambung.nEff].idPasien);
        // printf("%d", invent_Lambung.nEff);
        for (int i = 0; i < count; i++)
        {
            for (int j = 0; j < arr_Obat.nEff_Obat; j++)
            {
                if (strcasecmp(denah.data[idxi][idxj].Pasien->rincianObat[i], arr_Obat.data_Obat[j].nama_Obat) == 0)
                {
                    invent_Lambung.data[invent_Lambung.nEff].invent.idObat[idxObat++] = arr_Obat.data_Obat[j].id_Obat;
                    // printf("%d-%d\n", invent_Lambung.data[invent_Lambung.nEff].invent.idObat[idxObat - 1], arr_Obat.data_Obat[j].id_Obat);
                }
            }
        }
        invent_Lambung.data[invent_Lambung.nEff].invent.jumlahObat += count;
        invent_Lambung.nEff++;
    }

    // for (int j = 0; j < invent_Lambung.nEff; j++)
    // {
    //     if (invent_Lambung.data[j].idPasien == denah.data[idxi][idxj].Pasien->data.id)
    //     {
    //         invent_Lambung.data[j].invent.jumlahObat += count;
    //         // printf("%d", invent_Lambung.data[j].invent.jumlahObat);
    //         break;
    //     }
    //     else
    //     {
    //         invent_Lambung.data[invent_Lambung.nEff++].idPasien = denah.data[idxi][idxj].Pasien->data.id;
    //     }
    // }
}
void SortRincianObat(char rincian_Obat[50][100], int count)
{
    // sort sesuai urutan minum
    int temp;
    char temp1[50];
    bool first_found = true;
    bool first_assigned = false;
    int i = 0;
    while (i < count && rincian_Obat[i][0] != '\0')
    {
        for (int j = 0; j < arr_Obat.nEff_Obat; j++)
        {
            int k = i + 1;
            while (k < 20 && rincian_Obat[k][0] != '\0' && i != k)
            {
                for (int l = 0; l < arr_Obat.nEff_Penyakit; l++)
                {
                    if (!first_assigned)
                    {
                        if (strcmp(arr_Obat.data_Obat[j].nama_Obat, rincian_Obat[i]) == 0 && arr_Obat.data_Obat[j].id_Obat == arr_Obat.data_Obat_penyakit[l].id_Obat)
                        {
                            if (first_found)
                            {
                                first_found = false;
                                temp = arr_Obat.data_Obat_penyakit[l].urutan_Minum;
                            }
                            if (!first_found)
                            {
                                if (arr_Obat.data_Obat_penyakit[l].urutan_Minum < temp)
                                {
                                    strcpy(temp1, rincian_Obat[i]);
                                    strcpy(rincian_Obat[i], rincian_Obat[k]);
                                    strcpy(rincian_Obat[k], temp1);

                                    first_found = true;
                                    first_assigned = true;
                                    break;
                                }
                            }
                        }
                    }
                    else
                    {
                        if (strcmp(arr_Obat.data_Obat[j].nama_Obat, rincian_Obat[k]) == 0 && arr_Obat.data_Obat[j].id_Obat == arr_Obat.data_Obat_penyakit[l].id_Obat)
                        {
                            if (first_found)
                            {
                                first_found = false;
                                temp = arr_Obat.data_Obat_penyakit[l].urutan_Minum;
                            }
                            if (!first_found)
                            {
                                if (arr_Obat.data_Obat_penyakit[l].urutan_Minum < temp)
                                {
                                    ;
                                    strcpy(temp1, rincian_Obat[i]);
                                    strcpy(rincian_Obat[i], rincian_Obat[k]);
                                    strcpy(rincian_Obat[k], temp1);

                                    first_found = true;
                                    first_assigned = true;
                                    break;
                                }
                            }
                        }
                    }
                }
                k++;
            }
        }
        i++;
    }
}

void PrintRincianObat(int idxi, int idxj, int count)
{
    for (int i = 0; i < count; i++)
    {
        printf("%d. %s\n", i + 1, denah.data[idxi][idxj].Pasien->rincianObat[i]);
    }
}
// a 1 b 1 a 2 c 1 a 3 c 2 b 2