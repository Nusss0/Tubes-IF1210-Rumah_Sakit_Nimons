#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "../header/ADT.h"
#include "../header/user.h"
#include "../header/DiagnosisPenyakit.h"

#define MAX_LENGTH 50

void GetDataPenyakit()
{
    CreateListPenyakit(&arr_Penyakit, 100);
    FILE *fpenyakit = fopen("file/penyakit.csv", "r");
    if (!fpenyakit)
    {
        printf("File tidak Terbaca\n");
        fclose(fpenyakit);
        return;
    }
    char line[2048];
    char field[22][100];
    fgets(line, sizeof(line), fpenyakit); // skip baca header
    int i = 0;
    while (fgets(line, sizeof(line), fpenyakit))
    {
        GetField(line, field);
        arr_Penyakit.arr[i].id = atoi(field[0]);
        strcpy(arr_Penyakit.arr[i].nama_Penyakit, field[1]);
        arr_Penyakit.arr[i].suhu_Tubuh_Min = atof(field[2]);
        arr_Penyakit.arr[i].suhu_Tubuh_Max = atof(field[3]);
        arr_Penyakit.arr[i].tekanan_Darah_Sistolik_Min = atoi(field[4]);
        arr_Penyakit.arr[i].tekanan_Darah_Sistolik_Max = atoi(field[5]);
        arr_Penyakit.arr[i].tekanan_Darah_Diastolik_Min = atoi(field[6]);
        arr_Penyakit.arr[i].tekanan_Darah_Diastolik_Max = atoi(field[7]);
        arr_Penyakit.arr[i].detak_Jantung_Min = atoi(field[8]);
        arr_Penyakit.arr[i].detak_Jantung_Max = atoi(field[9]);
        arr_Penyakit.arr[i].saturasi_Oksigen_Min = atof(field[10]);
        arr_Penyakit.arr[i].saturasi_Oksigen_Max = atof(field[11]);
        arr_Penyakit.arr[i].kadar_Gula_Darah_Min = atof(field[12]);
        arr_Penyakit.arr[i].kadar_Gula_Darah_Max = atof(field[13]);
        arr_Penyakit.arr[i].berat_Badan_Min = atoi(field[14]);
        arr_Penyakit.arr[i].berat_Badan_Max = atoi(field[15]);
        arr_Penyakit.arr[i].tinggi_Badan_Min = atoi(field[16]);
        arr_Penyakit.arr[i].tinggi_Badan_Max = atoi(field[17]);
        arr_Penyakit.arr[i].kadar_Kolesterol_Min = atoi(field[18]);
        arr_Penyakit.arr[i].kadar_Kolesterol_Max = atoi(field[19]);
        arr_Penyakit.arr[i].trombosit_Min = atoi(field[20]);
        arr_Penyakit.arr[i].trombosit_Max = atoi(field[21]);

        arr_Penyakit.nEff++;
        i++;
    }
    fclose(fpenyakit);
}

void CreateListPenyakit(arrPenyakit *arr, int capacity)
{
    arr->arr = (dataPenyakit *)malloc(capacity * sizeof(dataPenyakit));
    arr->capacity = capacity;
    arr->nEff = 0;
}

void ReAllocListPenyakit(arrPenyakit *arr, int add)
{
    arr->arr = (dataPenyakit *)realloc(arr->arr, (arr->capacity + add) * sizeof(dataPenyakit));
    arr->capacity += add;
}

/*------------------------------------------------------------- F11 - DIAGNOSIS  -------------------------------------------------------------*/

void MenuDiagnosa()
{
    int i = 0;
    int j = 0;
    bool dokfound = false;
    while (i < denah.row)
    {
        j = 0;
        while (j < denah.col)
        {
            if (strcmp(denah.data[i][j].nama_dokter, user.username) == 0)
            {
                dokfound = true;
                break;
            }
            j++;
        }
        if (strcmp(denah.data[i][j].nama_dokter, user.username) == 0)
        {
            break;
        }
        i++;
    }

    if (!dokfound)
    {
        printf("╔══════════════════════════════════════════════════════╗\n");
        printf("║ ❌ Maaf Dok, Anda belum di-Assign ke ruangan manapun ║\n");
        printf("╚══════════════════════════════════════════════════════╝\n\n");
    }
    else
    {

        if (denah.data[i][j].Pasien == NULL)
        {
            printf("╔═══════════════════════════════════════════════╗\n");
            printf("║ ❌ Tidak ada pasien untuk diperiksa saat ini! ║\n");
            printf("╚═══════════════════════════════════════════════╝\n\n");
            return;
        }

        strcpy(denah.data[i][j].Pasien->data.penyakit, "-");
        DiagnosePasien(i, j);

        if (strcmp(denah.data[i][j].Pasien->data.penyakit, "-") == 0)
        {
            printf("🩺 Pasien \"%s\" tidak terdiagnosis penyakit apapun.\n\n",
            denah.data[i][j].Pasien->data.username);
            strcpy(user.penyakit, "sehat");
            strcpy(denah.data[i][j].Pasien->data.penyakit, "sehat");
            denah.data[i][j].Pasien->data.is_Diagnosed = true;
        }
        else if (denah.data[i][j].Pasien->data.is_Diagnosed == true)
        {
            printf("⚠️ Pasien \"%s\" telah pernah didiagnosa sebelumnya.\n\n",
                   denah.data[i][j].Pasien->data.username);
        }
        else
        {
            printf("✅ Pasien \"%s\" berhasil terdiagnosa: %s\n\n",
                   denah.data[i][j].Pasien->data.username,
                   denah.data[i][j].Pasien->data.penyakit);

            denah.data[i][j].Pasien->data.is_Diagnosed = true;
            arr_User.arr[denah.data[i][j].Pasien->data.id - 1].is_Diagnosed = true;
            strcpy(user.penyakit, denah.data[i][j].Pasien->data.penyakit);
        }
    }
}

void DiagnosePasien(int idxi, int idxj)
{
    dataUser dataPasien = denah.data[idxi][idxj].Pasien->data;

    for (int i = 0; i < arr_Penyakit.nEff; i++)
    {
        dataPenyakit p = arr_Penyakit.arr[i];
        if (dataPasien.suhuTubuh >= p.suhu_Tubuh_Min &&
            dataPasien.suhuTubuh <= p.suhu_Tubuh_Max &&
            dataPasien.tekanan_Darah_Sistolik >= p.tekanan_Darah_Sistolik_Min &&
            dataPasien.tekanan_Darah_Sistolik <= p.tekanan_Darah_Sistolik_Max &&
            dataPasien.tekanan_Darah_Diastolik >= p.tekanan_Darah_Diastolik_Min &&
            dataPasien.tekanan_Darah_Diastolik <= p.tekanan_Darah_Diastolik_Max &&
            dataPasien.detak_Jantung >= p.detak_Jantung_Min &&
            dataPasien.detak_Jantung <= p.detak_Jantung_Max &&
            dataPasien.saturasi_Oksigen >= p.saturasi_Oksigen_Min &&
            dataPasien.saturasi_Oksigen <= p.saturasi_Oksigen_Max &&
            dataPasien.kadar_Gula_Darah >= p.kadar_Gula_Darah_Min &&
            dataPasien.kadar_Gula_Darah <= p.kadar_Gula_Darah_Max &&
            dataPasien.berat_Badan >= p.berat_Badan_Min &&
            dataPasien.berat_Badan <= p.berat_Badan_Max &&
            dataPasien.tinggi_Badan >= p.tinggi_Badan_Min &&
            dataPasien.tinggi_Badan <= p.tinggi_Badan_Max &&
            dataPasien.kadar_Kolesterol >= p.kadar_Kolesterol_Min &&
            dataPasien.kadar_Kolesterol <= p.kadar_Kolesterol_Max &&
            dataPasien.trombosit >= p.trombosit_Min &&
            dataPasien.trombosit <= p.trombosit_Max)
        {
            strcpy(denah.data[idxi][idxj].Pasien->data.penyakit, p.nama_Penyakit);
            AssignPenyakit(dataPasien.username, p.nama_Penyakit);

            printf("\n╔════════════════════════════════════════════════╗\n");
            printf("║ 🔍 Hasil Diagnosa untuk: %-20s ║\n", dataPasien.username);
            printf("╚════════════════════════════════════════════════╝\n");
            printf("🦠 Penyakit Teridentifikasi: **%s**\n\n", p.nama_Penyakit);

            printf("📊 Ringkasan Data Vital:\n");
            printf("  • Suhu Tubuh       = %.2f °C      (Rentang: %.2f - %.2f)\n", dataPasien.suhuTubuh, p.suhu_Tubuh_Min, p.suhu_Tubuh_Max);
            printf("  • Tekanan Sistolik = %d mmHg      (Rentang: %d - %d)\n", dataPasien.tekanan_Darah_Sistolik, p.tekanan_Darah_Sistolik_Min, p.tekanan_Darah_Sistolik_Max);
            printf("  • Tekanan Diastolik= %d mmHg      (Rentang: %d - %d)\n", dataPasien.tekanan_Darah_Diastolik, p.tekanan_Darah_Diastolik_Min, p.tekanan_Darah_Diastolik_Max);
            printf("  • Detak Jantung    = %d bpm       (Rentang: %d - %d)\n", dataPasien.detak_Jantung, p.detak_Jantung_Min, p.detak_Jantung_Max);
            printf("  • Oksigen          = %.2f %%      (Rentang: %.2f - %.2f)\n", dataPasien.saturasi_Oksigen, p.saturasi_Oksigen_Min, p.saturasi_Oksigen_Max);
            printf("  • Gula Darah       = %d mg/dL     (Rentang: %d - %d)\n", dataPasien.kadar_Gula_Darah, p.kadar_Gula_Darah_Min, p.kadar_Gula_Darah_Max);
            printf("  • Berat Badan      = %.2f kg      (Rentang: %.2f - %.2f)\n", dataPasien.berat_Badan, p.berat_Badan_Min, p.berat_Badan_Max);
            printf("  • Tinggi Badan     = %d cm        (Rentang: %d - %d)\n", dataPasien.tinggi_Badan, p.tinggi_Badan_Min, p.tinggi_Badan_Max);
            printf("  • Kolesterol       = %d mg/dL     (Rentang: %d - %d)\n", dataPasien.kadar_Kolesterol, p.kadar_Kolesterol_Min, p.kadar_Kolesterol_Max);
            printf("  • Trombosit        = %d x10^3/μL  (Rentang: %d - %d)\n\n", dataPasien.trombosit, p.trombosit_Min, p.trombosit_Max);
            return;
        }
    }
}

void AssignPenyakit(const char *username, const char *namaPenyakit)
{
    for (int i = 0; i < arr_User.nEff; i++)
    {
        if (strcasecmp(arr_User.arr[i].username, username) == 0)
        {
            strcpy(arr_User.arr[i].penyakit, namaPenyakit);
        }
    }
}
