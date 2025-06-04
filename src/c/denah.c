#include "../header/ADT.h"
#include "../header/denah.h"
#include "../header/user.h"
#include "../header/daftar_checkup.h"
#include "../header/ManageUser.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

void StateConfig(char folder[]){
    char path[100];
    sprintf(path,"%s%s%s","file/",folder,"/config.txt");
    FILE* config = fopen(path,"r");
    if (config == NULL) {
        printf("Gagal membuka file konfigurasi!\n");
        return;
    }
    char line[100];
    char field[50][100];
    fgets(line,sizeof(line),config);
    GetField(line,field);
    denah.row = atoi(field[0]);
    denah.col = atoi(field[1]);
    AllocDenah(denah.row,denah.col);
    fgets(line,sizeof(line),config);
    GetField(line,field);
    denah.data[0][0].kapasitas = atoi(field[0]);
    denah.data[0][0].max_Antrian = atoi(field[1]);
    for(int i=0;i<denah.row;i++){
        for(int j=0;j<denah.col;j++){
            //reset Field
            for(int a =0; a<(denah.data[0][0].kapasitas+denah.data[0][0].max_Antrian+1);a++){
                strcpy(field[a],"0");
            }
            //INISIALISASI
            denah.data[i][j].antrian = 0;      
            denah.data[i][j].kapasitas = denah.data[0][0].kapasitas;
            denah.data[i][j].max_Antrian = denah.data[0][0].max_Antrian;
            denah.data[i][j].Pasien = NULL;
            fgets(line,sizeof(line),config);
            GetField(line,field);
            if(field[0][0] == '0') {
                strcpy(denah.data[i][j].nama_dokter ,"-");
                continue;
            }
            strcpy(denah.data[i][j].nama_dokter , arr_User.arr[atoi(field[0])-1].username);
            for(int k=0;k<arr_Dokter.nEff;k++){
                if (strcasecmp(denah.data[i][j].nama_dokter , arr_Dokter.data[k].username)==0) {
                    arr_Dokter.data[k].room = true;
                    char temp[100];
                    sprintf(temp, "%c%d", 'A' + i, j + 1);
                    strcpy(arr_Dokter.data[k].nama_ruang, temp);
                    break;
                }

            }
            int k =1;
            while(field[k][0]!='0') {
                InsertLink(&denah.data[i][j].Pasien,arr_User.arr[atoi(field[k])-1]);
                denah.data[i][j].antrian++;
                int temp = denah.data[i][j].antrian - denah.data[i][j].kapasitas;
                if(temp<0) temp=0;
                InsertAntrian(i,j,arr_User.arr[atoi(field[k])-1].username,temp);
                k++;
            }
            printf("\n");
            
        }
    }
}

void resetField(char field[][100], int b){
    for(int j=0;j<=b;j++){
        strcpy(field[j],"0");
    }

}

void CreateDenah(char folder[]){
    StateConfig(folder);
    int col,row;
    col = denah.col;
    row = denah.row;
    AssignRuang(row,col);
    // capacity = denah.data[0][0].kapasitas;
    // printf("Input Column : ");
    // scanf("%d",&col);
    // printf("Input Row : ");
    // scanf("%d",&row);
    // printf("\n");
}
void AllocDenah(int row,int col){
    denah.data = (dataRuang**) malloc(row*sizeof(dataRuang*));
    for(int i=0;i<row;i++){
        denah.data[i] = (dataRuang*) malloc(col*sizeof(dataRuang));
    }
    denah.col =col;
    denah.row = row;
}
void ReAllocDenah(int row, int col){
    denah.data = (dataRuang**) realloc(denah.data,row*sizeof(dataRuang*));
    for(int i=0;i<row;i++){
        denah.data[i] = (dataRuang*) realloc(denah.data[i],col*sizeof(dataRuang));
    }
    denah.col =col;
    denah.row = row;
}
void AssignRuang(int row,int col){
    char str1 ='A';
    int str2 =1;
    for(int i = 0 ; i<row;i++){
        for(int j = 0; j<col;j++){
            sprintf(denah.data[i][j].nama_ruang,"%c%d",str1,str2);
            str2++;
        }
        str1++;
        str2 =1;
    }
}

void PrintPembatas(){
    for(int i=0;i<denah.col;i++){
        printf("+-----");
        if(i==denah.col-1) printf("+");
    }
    printf("\n");
}

void PrintDenah(){
    PrintPembatas();
    for(int i =0;i<denah.row;i++){
        for(int j =0;j<denah.col;j++){
            printf("| %-3s ",denah.data[i][j].nama_ruang);
            if(j==denah.col-1) printf("|\n");
        }
        PrintPembatas();
    }
}

void RemakeDenah(int row,int col){
    //asumsi denah sudah ada karena sebelum rumahsakit dibuat, sudah diassign oleh manager terlebih dahulu
    if(IsDocterInRoom(col,row)){
        return;
    }
    else{
        denah.col = col;
        denah.row = row;
        ReAllocDenah(row,col);
        AssignRuang(row,col);
        PrintDenah();
        printf("===========================================================\n");
        printf("🏥 Denah rumah sakit berhasil diubah!\n");
        printf("📐 Ukuran baru: %d baris × %d kolom\n", row, col);
        printf("===========================================================\n\n");

    }
}
void PindahDokter(char ruang1[], char ruang2[]){
    char dokter1[100];
    char dokter2[100];
    int Si,Sj,Di,Dj;
    for(int i=0;i<denah.row;i++){
        for(int j=0;j<denah.col;j++){
            if(strcmp(ruang1,denah.data[i][j].nama_ruang)==0) {
                strcpy(dokter1,denah.data[i][j].nama_dokter);
                if(dokter1[0]=='\0' || dokter1[0]=='-'){
                    printf("=====================================================\n");
                    printf("⚠️  Tidak ada dokter di ruangan %s untuk dipindahkan.\n", ruang1);
                    printf("=====================================================\n");
                    return;
                }
                Si = i;
                Sj = j;
            }
        }
    }
    for(int i=0;i<denah.row;i++){
        for(int j=0;j<denah.col;j++){

            if(strcmp(ruang2,denah.data[i][j].nama_ruang)==0) {
                strcpy(dokter2,denah.data[i][j].nama_dokter);
                if(IsRoomOccupied(ruang2,dokter2)) return;
                Di =i;
                Dj = j;
            }
        }
    }
    printf("=====================================================\n");
    printf("✅ Dokter %s berhasil dipindahkan ke ruangan %s.\n", dokter1, ruang2);
    printf("=====================================================\n\n");
    strcpy(denah.data[Di][Dj].nama_dokter,denah.data[Si][Sj].nama_dokter);
    strcpy(denah.data[Si][Sj].nama_dokter,"-");
    denah.data[Di][Dj].antrian = denah.data[Si][Sj].antrian ;
    denah.data[Si][Sj].antrian = 0;
    denah.data[Di][Dj].kapasitas = denah.data[Si][Sj].kapasitas;
    denah.data[Di][Dj].max_Antrian = denah.data[Si][Sj].max_Antrian;
    denah.data[Di][Dj].Pasien = denah.data[Si][Sj].Pasien;
    denah.data[Si][Sj].Pasien = NULL;
}

bool IsDocterInRoom(int col, int row){
    if (col > denah.col && row > denah.row) return false;

    for (int i = 0; i < denah.row; i++) {
        for (int j = 0; j < denah.col; j++) {
            if (i >= row || j >= col) {
                if (denah.data[i][j].nama_dokter[0] != '\0') {
                    printf("===========================================================\n");
                    printf("⚠️  Tidak dapat mengubah ukuran denah!\n");
                    printf("🏥 Ruangan %s masih ditempati oleh dr. %s\n", 
                           denah.data[i][j].nama_ruang, denah.data[i][j].nama_dokter);
                    printf("📝 Silakan pindahkan dokter terlebih dahulu.\n");
                    printf("===========================================================\n\n");
                    return true;
                }
            }
        }
    }

    return false;
}


void PrintDataRuangan(char* ruang){
    int i =((int)ruang[0])-65;
    int j= ((int)ruang[1])-49;
    if(i<0 || j<0 || j>=denah.col || i>=denah.row){
        printf("Ruangan Tidak Terdaftar !\n\n");
        return;
    }
    dataRuang data = denah.data[i][j];
    printf("\n");
    printf("----------------- Detail Ruangan %s -----------------\n",data.nama_ruang);
    printf("Kapasitas : %d\n",data.kapasitas);
    printf("Dokter : %s\n",data.nama_dokter);
    printf("Pasien di dalam ruangan : \n");

    queue* curr = data.Pasien;
    if (curr == NULL) {
        printf("Tidak Ada Pasien Dalam Antrian !\n\n");
        return;
    }
    int seq=1;
    while(curr!=NULL){
        if(seq == data.kapasitas+1) printf("Pasien di Antrian : \n");
        printf("%d. %s\n",seq,curr->data.username);
        curr = curr->next;
        seq++;
    }
    printf("\n");
}