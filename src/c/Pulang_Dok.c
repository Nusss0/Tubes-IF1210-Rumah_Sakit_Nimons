#include "../header/ADT.h"
#include "../header/Pulang_Dok.h"
#include "../header/Minum_Obat_Penawar.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

void MenuPulangDok()
{
    int idx = CariData();
    if (idx < 0)
    {
        printf("\n🚫 Anda belum berobat dengan dokter. Silakan berobat terlebih dahulu sebelum pulang.\n");
        return;
    }

    int i = 0, j = 0;
    bool found = false;
    // printf("DEBUG : Udh belum lewat scan denah\n");
    while (i < denah.row && !found)
    {
        j = 0;
        while (j < denah.col && !found)
        {
            if (strcmp(denah.data[i][j].Pasien->data.username, user.username) == 0)
            {
                found = true;
            }
            else j++;
        }
        i++;
        if (found) i--;
    }
    // printf("DEBUG : Udh lewat scan denah\n");
    int id;
    for(int i=0;i<invent_Lambung.nEff;i++){
        if(user.id == invent_Lambung.data[i].idPasien) id = i;
    }
    if (!denah.data[i][j].Pasien->data.is_Diagnosed && invent_Lambung.data[id].invent.idObat[0]==0 && invent_Lambung.data[id].lambung.data.idObat[0]==0)
    {
        printf("\n🩺 Kamu belum menerima diagnosis dari dokter. Jangan buru-buru pulang, ya!\n");
    }
    else if (invent_Lambung.data[idx].invent.jumlahObat > 0 )
    {
        printf("\n💊 Masih ada obat yang belum kamu habiskan. Yuk, diminum dulu sampai habis!\n");
    }
    else if (!invent_Lambung.data[idx].urut && invent_Lambung.data[idx].invent.jumlahObat == 0)
    {
        printf("\n⚠️ Kamu belum bisa pulang!\nSilakan konsultasikan ulang dengan dokter untuk penawar\n");
        // printf("Urutan peminuman obat yang diharapkan: \n");
        // PrintTerurut();
        // printf("Urutan obat yang kamu minum : \n");
        // PrintStack();
    }
    else
    {
        printf("\n✅ Dokter menyatakan kamu telah SEMBUH total!\nSilakan pulang dan jaga kesehatan selalu.\n");
        UpdateQueue();
        for(int x =0;x<arr_User.nEff;x++){
            if(strcmp(user.username,arr_User.arr[x].username)==0){
                ResetData(&arr_User.arr[x]);
                break;
            }
        }
        invent_Lambung.data[idx].pulang = true;
        
    }
}


void UpdateQueue()
{
    int idxi = -1, idxj = -1;
    int idx_found = -1;

    // Cari posisi user di list_antrian
    for (int i = 0; i < list_antrian.nEff; i++) {
        if (strcmp(user.username, list_antrian.data[i].nama_pasien) == 0) {
            idxi = list_antrian.data[i].i;
            idxj = list_antrian.data[i].j;
            idx_found = i;
            break;
        }
    }
    // geser ke kiri semua data
    for (int j = idx_found; j < list_antrian.nEff - 1; j++) {
        list_antrian.data[j] = list_antrian.data[j + 1];
    }
    list_antrian.nEff--;

    // Update linked list queue
    queue* head = denah.data[idxi][idxj].Pasien;
    if (head != NULL) {
        denah.data[idxi][idxj].Pasien = head->next;
        if (denah.data[idxi][idxj].Pasien != NULL) {
            denah.data[idxi][idxj].Pasien->prev = NULL;
        }
        free(head);
    }
}
void UpdateAura(int i, int j)
{
    for (int k = 0; k < arr_User.nEff; k++)
    {
        if (strcmp(denah.data[i][j].nama_dokter, arr_User.arr[k].username) == 0)
        {
            arr_User.arr[k].aura+=1;
            // printf("%s's aura: %d", denah.data[i][j].nama_dokter, arr_User.arr[k].aura);
        }
    }
}
