#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include "../header/Save_Load.h"
#include "../header/ADT.h"

void MenuSave(){
    char op;
    do{
        printf("Apakah Anda mau melakukan penyimpanan file yang sudah diubah? (y/n) : ");
        scanf(" %c",&op);
        if(op == 'Y'||op=='y'){
            Save();
        }
        else return;
    }while(op != 'y' && op != 'n' && op != 'Y' && op != 'N');
}

void Save(){
    char input[100];
    printf("Masukan Nama Folder : ");
    scanf("%s", input);
    char foldername[1000];
    sprintf(foldername,"file/%s",input);
    int status = mkdir(foldername,0777);
    if (status == 0) {
        printf("Folder %s berhasil dibuat.\n", input);
        printf("Saving...\n");
    } 
    else{
        printf("Folder %s sudah ada !\n", input);
        printf("Apakah Anda ingin Overwrite? (y/n) : ");
        char op;
        scanf(" %c",&op);
        do{
            if(op=='y'||op=='Y'){
                printf("Saving...\n");
            }
            else if(op=='n'||'N'){
                printf("\n");
                Save();
                return;
            }
        }while(op != 'y' && op != 'n' && op != 'Y' && op != 'N');
    }
    WriteUser(foldername);
    WriteConfig(foldername);
}

void WriteUser(const char* input){
    char path[1000];
    sprintf(path, "%s/user.csv",input);
    FILE *file = fopen(path,"w");
    if (file == NULL) {
        printf("Gagal membuka file!\n");
        return;
    }
    for(int i = 0;i<arr_User.nEff;i++){
        fprintf(file, "%d,%s,%s,%s,%s,%.2f,%d,%d,%d,%.2f,%d,%.2f,%d,%d,%d,%d\n",
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
            arr_User.arr[i].trombosit,
            arr_User.arr[i].aura
        );
    }
    fclose(file);
}
void WriteConfig(const char* input){
    char path[1000];
    sprintf(path, "%s/config.txt",input);
    FILE *file = fopen(path,"w");
    if (file == NULL) {
        printf("Gagal membuka file!\n");
        return;
    }
    fprintf(file,"%d %d\n",denah.row,denah.col);
    fprintf(file,"%d %d\n",denah.data[0][0].kapasitas,denah.data[0][0].max_Antrian);
    for(int i = 0; i<denah.row;i++){
        for(int j=0;j<denah.col;j++){
            char line[1000];
            line[0] ='\0';
            if(denah.data[i][j].nama_dokter[0] == '-') {
                sprintf(line+strlen(line),"%d ",0);
            }
            else sprintf(line+strlen(line),"%d ",RetID(denah.data[i][j].nama_dokter));
            
            queue *curr = denah.data[i][j].Pasien;
            while (curr != NULL) {
                sprintf(line + strlen(line), "%d", curr->data.id);
                curr = curr->next;
                if (curr != NULL) {
                    sprintf(line + strlen(line), " ");
                }
            }
            sprintf(line + strlen(line), "\n");
            fputs(line, file);
            
        }
    }
    invent_Lambung.nInvent=0;
    invent_Lambung.nLambung=0;
    // Tulis inventori per pasien
    for(int i=0;i<invent_Lambung.nEff;i++){
        if(invent_Lambung.data[i].pulang==true )continue;
        if(invent_Lambung.data[i].invent.idObat[0]!=0) invent_Lambung.nInvent++;
        if(invent_Lambung.data[i].lambung.data.idObat[0] !=0) invent_Lambung.nLambung++;
    }
    int invent = invent_Lambung.nInvent;
    fprintf(file, "%d\n", invent);
    char lineInvent[500];
    for (int j = 0; j < invent_Lambung.nEff; j++) {
        if (invent_Lambung.data[j].idPasien != 0) {
            lineInvent[0] = '\0';
            if(invent_Lambung.data[j].pulang==true)continue;
            sprintf(lineInvent + strlen(lineInvent), "%d", invent_Lambung.data[j].idPasien);
            for (int k = 0; k < invent_Lambung.data[j].invent.jumlahObat; k++) {
                sprintf(lineInvent + strlen(lineInvent), " %d", invent_Lambung.data[j].invent.idObat[k]);
            }
            strcat(lineInvent, "\n");
        }
        fputs(lineInvent, file);
    }
    
    int lambung = invent_Lambung.nLambung;
    fprintf(file, "%d\n", lambung);
    // Tulis lambung per pasien
    char lineLambung[500];
    for (int j = 0; j < invent_Lambung.nEff; j++) {
        if (invent_Lambung.data[j].lambung.top >= 0) {
            lineLambung[0] = '\0';
            if(invent_Lambung.data[j].pulang==true)continue;
            sprintf(lineLambung + strlen(lineLambung), "%d", invent_Lambung.data[j].idPasien);
            for (int k = 0; k <= invent_Lambung.data[j].lambung.top; k++) {
                sprintf(lineLambung + strlen(lineLambung), " %d", invent_Lambung.data[j].lambung.data.idObat[k]);
            }
            strcat(lineLambung, "\n");
            fputs(lineLambung, file);
        }
    }

}

int RetID(const char* username){
    for(int i =0;i<arr_User.nEff;i++){
        if(strcasecmp(arr_User.arr[i].username,username)==0){
            return i+1;
        }
    }
}