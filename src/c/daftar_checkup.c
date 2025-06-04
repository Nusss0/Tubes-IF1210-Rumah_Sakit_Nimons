#include "../header/ADT.h"
#include "../header/denah.h"
#include "../header/ManageUser.h"
#include "../header/daftar_checkup.h"
#include <stdio.h>

void MenuDaftarCheckup(){
    if(user.is_Checked == true){
        printf("⚠️ Anda sudah melakukan Check-up, silahkan menunggu Giliran Anda !\n\n");
        return;
    }
    printf("Silahkan Masukkan Data Check-Up Anda : \n");
    ValidasiInputData();
    PilihDokter();
    user.is_Checked = true;
}

void PilihDokter() {
    int col = denah.col;
    int row = denah.row;
    int num = 0;
    int list_dokter[100][2];
    int aura_list[100];
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (strcmp(denah.data[i][j].nama_dokter, "-") == 0 || strcmp(denah.data[i][j].nama_dokter, "\0") == 0) continue;
            for (int k = 0; k < arr_User.nEff; k++)
            {
                if (strcmp(denah.data[i][j].nama_dokter, arr_User.arr[k].username) == 0)
                {
                    list_dokter[num][0] = i;
                    list_dokter[num][1] = j;
                    aura_list[num] = arr_User.arr[k].aura;
                    num++;
                    break;
                }
            }
        }
    }
    for (int x = 0; x < num - 1; x++)
    {
        int idx_max = x;
        for (int y = x + 1; y < num; y++)
        {
            if (aura_list[y] > aura_list[idx_max])
            {
                idx_max = y;
            }
        }
        if (idx_max != x)
        {
            // swap aura
            int tmpAura = aura_list[x];
            aura_list[x] = aura_list[idx_max];
            aura_list[idx_max] = tmpAura;
            // swap koordinat (i,j)
            int tmpI = list_dokter[x][0];
            int tmpJ = list_dokter[x][1];
            list_dokter[x][0] = list_dokter[idx_max][0];
            list_dokter[x][1] = list_dokter[idx_max][1];
            list_dokter[idx_max][0] = tmpI;
            list_dokter[idx_max][1] = tmpJ;
        }
    }
    printf("\n===================================\n");
    printf("         Daftar Dokter Aktif       \n");
    printf("===================================\n");
    printf("| %-3s | %-20s | %-10s | %-8s | Aura\n", "No", "Nama Dokter", "Ruangan", "Antrian");
    printf("-------------------------------------------------------------\n");

    for (int idx = 0; idx < num; idx++)
    {
        int i = list_dokter[idx][0];
        int j = list_dokter[idx][1];
        for (int k = 0; k < arr_User.nEff; k++)
        {
            if (strcmp(denah.data[i][j].nama_dokter, arr_User.arr[k].username) == 0)
            {
                printf("| %-3d | %-20s | %-10s | %-8d | %-5d \n", idx + 1, denah.data[i][j].nama_dokter,denah.data[i][j].nama_ruang, (denah.data[i][j].antrian - denah.data[i][j].kapasitas >= 0 ? denah.data[i][j].antrian - denah.data[i][j].kapasitas : 0), arr_User.arr[k].aura);
                break;
            }
        }
    }

    printf("-------------------------------------------------------------\n");

    int no_dokter;
    int idxi, idxj, antrian;

    do {
        printf("Pilih Dokter (1-%d): ", num);
        scanf("%d", &no_dokter);
        if ((no_dokter <= 0 || no_dokter > num)) {
            printf("⚠️  Input Tidak Valid, Silakan Coba Lagi!\n\n");
            continue;
        }

        idxi = list_dokter[no_dokter - 1][0];
        idxj = list_dokter[no_dokter - 1][1];
        antrian = denah.data[idxi][idxj].antrian + 1;

        if (antrian > denah.data[idxi][idxj].max_Antrian) {
            printf("❌ Maaf, Antrian Penuh! Pilih Dokter Lain.\n\n");
            continue;
        }

    } while (no_dokter <= 0 || no_dokter > num || (antrian > denah.data[idxi][idxj].max_Antrian));

    printf("\n✅ Pendaftaran Check-Up Berhasil!\n");
    printf("📋 Anda terdaftar pada:\n");
    printf("   ➤ Dokter : %s\n", denah.data[idxi][idxj].nama_dokter);
    printf("   ➤ Ruangan: %s\n", denah.data[idxi][idxj].nama_ruang);

    denah.data[idxi][idxj].antrian++;
    InsertLink(&denah.data[idxi][idxj].Pasien, user);

    int posisi = denah.data[idxi][idxj].antrian - denah.data[idxi][idxj].kapasitas;
    if (posisi < 0) posisi = 0;
    InsertAntrian(idxi, idxj, user.username, posisi);

    if (posisi > 0) {
        printf("📌 Posisi Antrian Anda: %d\n\n", posisi);
    } else {
        printf("🩺 Anda akan langsung diperiksa!\n\n");
    }
}


void ValidasiInputData() {
    printf("\n===========================================\n");
    printf("     📋 Silakan Masukkan Data Check-Up     \n");
    printf("===========================================\n");

    do {
        printf("🌡️  Suhu Tubuh (°C)          : ");
        scanf("%f", &user.suhuTubuh);
        if (user.suhuTubuh <= 0) printf("⚠️  Suhu tidak boleh nol atau negatif!\n");
    } while (user.suhuTubuh <= 0);

    do {
        printf("💓 Tekanan Darah (sistolik diastolik) : ");
        scanf("%d %d", &user.tekanan_Darah_Sistolik, &user.tekanan_Darah_Diastolik);
        if (user.tekanan_Darah_Sistolik <= 0 || user.tekanan_Darah_Diastolik <= 0)
            printf("⚠️  Tekanan darah harus bernilai positif!\n");
    } while (user.tekanan_Darah_Sistolik <= 0 || user.tekanan_Darah_Diastolik <= 0);

    do {
        printf("❤️ Detak Jantung (bpm)      : ");
        scanf("%d", &user.detak_Jantung);
        if (user.detak_Jantung <= 0) printf("⚠️  Detak jantung tidak valid!\n");
    } while (user.detak_Jantung <= 0);

    do {
        printf("🫁 Saturasi Oksigen (%%)       : ");
        scanf("%f", &user.saturasi_Oksigen);
        if (user.saturasi_Oksigen < 0 || user.saturasi_Oksigen > 100)
            printf("⚠️  Nilai saturasi harus antara 0–100!\n");
    } while (user.saturasi_Oksigen < 0 || user.saturasi_Oksigen > 100);

    do {
        printf("🩸 Kadar Gula Darah (mg/dL) : ");
        scanf("%d", &user.kadar_Gula_Darah);
        if (user.kadar_Gula_Darah <= 0) printf("⚠️  Gula darah tidak valid!\n");
    } while (user.kadar_Gula_Darah <= 0);

    do {
        printf("⚖️  Berat Badan (kg)         : ");
        scanf("%f", &user.berat_Badan);
        if (user.berat_Badan <= 0) printf("⚠️  Berat badan harus > 0!\n");
    } while (user.berat_Badan <= 0);

    do {
        printf("📏 Tinggi Badan (cm)         : ");
        scanf("%d", &user.tinggi_Badan);
        if (user.tinggi_Badan <= 0) printf("⚠️  Tinggi badan harus > 0!\n");
    } while (user.tinggi_Badan <= 0);

    do {
        printf("🥚 Kadar Kolesterol (mg/dL) : ");
        scanf("%d", &user.kadar_Kolesterol);
        if (user.kadar_Kolesterol <= 0) printf("⚠️  Kolesterol tidak valid!\n");
    } while (user.kadar_Kolesterol <= 0);

    do {
        printf("🧬 Trombosit (ribu/µL)       : ");
        scanf("%d", &user.trombosit);
        if (user.trombosit <= 0) printf("⚠️  Nilai trombosit tidak valid!\n");
    } while (user.trombosit <= 0);

    // Update user list yang dinamis
    arr_User.arr[user.id] = user;

    printf("\n✅ Data berhasil disimpan!\n\n");
}


void InsertLink( queue **q, dataUser x){
    queue* newNode = (queue*) malloc(sizeof(queue));
    newNode->data = x;
    newNode->next = NULL;
    newNode->prev = NULL;
    if (*q == NULL)
    {
        *q = newNode;
    }
    else
    {
        queue *curr = *q;
        while (curr->next != NULL)
        {
            curr = curr->next;
        }
        curr->next = newNode;
        newNode->prev = curr;
    }
}

void InsertAntrian(int i, int j, char *nama_pasien, int urutan)
{
    int idx = list_antrian.nEff;
    list_antrian.data[idx].i = i;
    list_antrian.data[idx].j = j;
    list_antrian.data[idx].urutan = urutan;
    strcpy(list_antrian.data[idx].nama_pasien, nama_pasien);
    list_antrian.nEff++;
}

void PrintAntrian()
{
    for (int i = 0; i < denah.row; i++)
    {
        for (int j = 0; j < denah.col; j++)
        {
            queue *curr = denah.data[i][j].Pasien;
            if (curr == NULL)
                continue;
            PrintDataRuangan(denah.data[i][j].nama_ruang);
        }
    }
}

void PrintAntrianSaya()
{
    bool found = false;
    for (int i = 0; i < list_antrian.nEff; i++)
    {
        if (strcasecmp(user.username, list_antrian.data[i].nama_pasien) == 0)
        {
            found = true;
            int idxi = list_antrian.data[i].i;
            int idxj = list_antrian.data[i].j;

            printf("\n📋 === Status Antrian Anda ===\n");
            printf("🏥 Ruangan : %s\n", denah.data[idxi][idxj].nama_ruang);
            printf("👨‍⚕️ Dokter  : %s\n", denah.data[idxi][idxj].nama_dokter);

            if (list_antrian.data[i].urutan <= 0)
            {
                printf("✅ Status  : Anda sedang berada di dalam ruangan.\n");
            }
            else
            {
                printf("⏳ Status  : Menunggu dalam antrian.\n");
                printf("📌 Posisi  : %d dari %d pasien dalam antrian\n", list_antrian.data[i].urutan, denah.data[idxi][idxj].antrian - denah.data[idxi][idxj].kapasitas);
            }
            printf("===============================\n\n");
            break;
        }
    }
    if (!found)
    {
        printf("❌ Anda belum mendaftar Check-Up, silahkan daftar terlebih dahulu.\n\n");
    }
}

void SkipAntrian()
{
    int idxi, idxj;

    for (int i = 0; i < list_antrian.nEff; i++)
    {
        if (strcmp(user.username, list_antrian.data[i].nama_pasien) == 0)
        {
            if (list_antrian.data[i].urutan == 0)
            {
                printf("╔══════════════════════════════════════════════════╗\n");
                printf("║ ❌ Skip Antrian Gagal!                          ║\n");
                printf("║ Kamu sedang berada di DALAM ruangan dokter.     ║\n");
                printf("║ Istirahat dulu ya, jangan buru-buru 😄         ║\n");
                printf("╚══════════════════════════════════════════════════╝\n\n");
                return;
            }
            else if (list_antrian.data[i].urutan == 1)
            {
                printf("╔══════════════════════════════════════════════════╗\n");
                printf("║ ❌ Skip Antrian Gagal!                          ║\n");
                printf("║ Kamu sudah berada di POSISI TERDEPAN antrian.   ║\n");
                printf("║ Siap-siap dipanggil, sabar dikit lagi ya! 🙏   ║\n");
                printf("╚══════════════════════════════════════════════════╝\n\n");
                return;
            }

            idxi = list_antrian.data[i].i;
            idxj = list_antrian.data[i].j;
            queue *head = denah.data[idxi][idxj].Pasien;
            queue *curr = head;
            int count = denah.data[idxi][idxj].kapasitas;
            queue *first = NULL;
            queue *userNode = NULL;

            // Langkah 1: Temukan first dan userNode
            while (curr != NULL)
            {
                count--;
                if (count == 0)
                {
                    first = curr->next; // node pertama di antrian (bukan di dalam ruangan)
                }
                if (strcmp(curr->data.username, user.username) == 0)
                {
                    userNode = curr;
                }
                curr = curr->next;
            }

            // Jika user atau first tidak ditemukan, keluar
            if (userNode == NULL || first == NULL || userNode == first)
                return;

            // Langkah 2: Putuskan userNode dari posisi sekarang
            if (userNode->prev != NULL)
                userNode->prev->next = userNode->next;
            if (userNode->next != NULL)
                userNode->next->prev = userNode->prev;

            // Langkah 3: Sisipkan userNode sebelum first
            userNode->next = first;
            userNode->prev = first->prev;

            if (first->prev != NULL)
                first->prev->next = userNode;
            first->prev = userNode;

            // Langkah 4: Update head kalau perlu
            if (denah.data[idxi][idxj].Pasien == first)
                denah.data[idxi][idxj].Pasien = userNode;
            for (int a = 0; a < list_antrian.nEff; a++)
            {
                if (list_antrian.data[a].i == idxi && list_antrian.data[a].j == idxj)
                {
                    if (list_antrian.data[a].urutan <= 0)
                        continue;
                    else
                        list_antrian.data[a].urutan++;
                }
            }
            list_antrian.data[i].urutan = 1;
            printf("╔══════════════════════════════════════════════════╗\n");
            printf("║ ✅ Skip Antrian Berhasil!                       ║\n");
            printf("║ Kamu sudah berada di POSISI TERDEPAN antrian.  ║\n");
            printf("║ Siap-siap dipanggil, sabar dikit lagi ya! 🙏   ║\n");
            printf("╚══════════════════════════════════════════════════╝\n\n");
            printf("Antrian yg sekarang jadi : %s\n", list_antrian.data[i].nama_pasien);
            return;
        }
    }
}