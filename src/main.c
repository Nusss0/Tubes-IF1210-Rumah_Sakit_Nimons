// Include any necessary headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>

#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#include "header/ADT.h"
#include "header/user.h"
#include "header/ManageUser.h"
#include "header/denah.h"
#include "header/Save_Load.h"
#include "header/daftar_checkup.h"
#include "header/ngobatin.h"
#include "header/DiagnosisPenyakit.h"
#include <dirent.h> 
#include "header/Minum_Obat_Penawar.h"
#include "header/Pulang_Dok.h"

dataUser user; // definisi
bool is_Logged_in = false; // definis;
arrList arr_User;
arrListDokter arr_Dokter;
denahRuang denah;
mapAntrian list_antrian;
arrPenyakit arr_Penyakit; 
arrObat arr_Obat;
InventLambungPasien invent_Lambung;

bool IsNotManager(){
    if (strcasecmp(user.role,"manager")){
        printf("Maaf, Anda tidak bisa mengakses fitur ini !\n");
        return true;
    }
    return false; //UBAH FALSE NNTI
}
bool IsNotDokter(){
    if (strcasecmp(user.role,"dokter")){
        printf("Maaf, Anda tidak bisa mengakses fitur ini !\n");
        return true;
    }
    return false;
}
bool IsNotLoggedIn(){
    if (is_Logged_in==false){
        printf("Maaf, Anda perlu Login terlebih dahulu !\n");
        return true;
    }
    return false; //UBAH FALSE NNTI
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: ./main <folder>\n");
        return 1;
    }

    char *folder = argv[1];

    // Cek apakah folder file/<folder> itu valid
    char fullFolderPath[256];
    sprintf(fullFolderPath, "file/%s", folder);

    DIR *dir = opendir(fullFolderPath);
    if (dir == NULL) {
        printf("[!] Folder \"%s\" tidak ditemukan di dalam folder 'file/'\n", folder);
        return 1;
    }
    closedir(dir);
    //INISIALISASI DATA AWAL
    list_antrian.nEff =0;
    arr_Dokter.nEff=0;
    user.is_Checked = false;
    DynData(folder);
    CreateDenah(folder);
    GetDataPenyakit();
    GetDataObat();
    SortList(1,1);
    GetDataInventLambung(folder);
    // printf("Init nEff : %d\n",invent_Lambung.nEff);
    // InitLambung();
    system("clear");
    char op[20];
    do{
        printf(ANSI_COLOR_BLUE);
        printf("=====================================================\n");
        printf("        SELAMAT DATANG DI RUMAH SAKIT NIMONS         \n");
        printf("=====================================================\n");
        printf(ANSI_COLOR_GREEN);
        printf("Ketik perintah \"HELP\" untuk melihat daftar perintah.\n");
        printf(ANSI_COLOR_RESET);
        printf("-----------------------------------------------------\n");
        printf(">> INPUT : ");
        scanf("%s",op);
        //MAIN
        if(strcasecmp(op,"LOGIN")==0) {
            if(is_Logged_in == true){
                printf("Anda Sudah Login !\n");
                continue;
            }
            system("clear");
            MenuLogin();
        }

        else if(strcasecmp(op,"LUPA_PASSWORD")==0){
            system("clear");
            MenuLupaPassword();
        }
        else if(strcasecmp(op,"HELP")==0){
            system("clear");
            MenuHelp();
        }
        else if(strcasecmp(op,"REGISTER")==0){
            system("clear");
            MenuRegister();
        }
        else if(strcasecmp(op,"LIHAT_DENAH")==0){
            system("clear");
            PrintDenah();
        }
        else if(strcasecmp(op,"LIHAT_RUANGAN")==0){
            char ruang[5];
            scanf("%s",ruang);
            PrintDataRuangan(ruang);
        }
        
        
        
        
        /*--------------------LOGGED IN ONLY-----------------------------------*/
        else if(strcasecmp(op,"LOGOUT")==0){
            if(IsNotLoggedIn()==false){
                printf("Sampai Jumpa, %s %s!\n",user.role,user.username);
                ResetData(&user);
                is_Logged_in = false;
            }
        }
        else if(strcasecmp(op,"DAFTAR_CHECKUP")==0){
            if(IsNotLoggedIn()==false && strcmp(user.role,"pasien")==0){
                system("clear");
                MenuDaftarCheckup();
            }
            else if(strcmp(user.role,"dokter")==0) {
                printf("Kau menyembuhkan semua orang... hingga lupa bagaimana rasanya disembuhkan.\n\n");
                printf("Maaf, Anda tidak bisa mengakses fitur ini💔💔💔.\n");
            }
        }
        else if(strcasecmp(op,"ANTRIAN")==0){
            if(IsNotLoggedIn()==false && strcmp(user.role,"pasien")==0){
                system("clear");
                PrintAntrianSaya();
            }
            else printf("Maaf, Anda bukan User!\n\n");
        }
        else if(strcasecmp(op,"MINUM_OBAT")==0){
            if(IsNotLoggedIn()==false && strcmp(user.role,"pasien")==0){
                system("clear");
                MenuMinumObat();
            }
            else printf("Maaf, Anda bukan User!\n\n");
        }
        else if(strcasecmp(op,"MINUM_PENAWAR")==0){
            if(IsNotLoggedIn()==false && strcmp(user.role,"pasien")==0){
                system("clear");
                MenuMinumPenawar();
            }
            else printf("Maaf, Anda bukan User!\n\n");
        }
        else if(strcasecmp(op,"PULANG_DOK")==0){
            if(IsNotLoggedIn()==false && strcmp(user.role,"pasien")==0){
                system("clear");
                MenuPulangDok();
            }
            else printf("Maaf, Anda bukan User!\n\n");
        }
/*----------------DOKTER ONLY------------------------------------------*/
        else if(strcasecmp(op,"DIAGNOSIS")==0){
            if (!IsNotLoggedIn() && !IsNotDokter())
            {
                system("clear");
                MenuDiagnosa();
            }
        }
        else if(strcasecmp(op,"NGOBATIN")==0){
            if (!IsNotLoggedIn() && !IsNotDokter())
            {
                system("clear");
                MenuNgobatin();
            }
        }
/*----------------MANAGER ONLY------------------------------------------*/
        else if(strcasecmp(op,"LIHAT_USER")==0) {
            if (!IsNotLoggedIn() && !IsNotManager())
            {
                system("clear");
                MenuLihatUser("all");
            }
        }
        else if(strcasecmp(op,"LIHAT_PASIEN")==0) {
            if (!IsNotLoggedIn() && !IsNotManager())
            {
                system("clear");
                MenuLihatUser("pasien");
            }
        }
        else if(strcasecmp(op,"LIHAT_DOKTER")==0) {
            if (!IsNotLoggedIn() && !IsNotManager())
            {
                system("clear");
                MenuLihatUser("dokter");
            }
        }
        else if(strcasecmp(op,"CARI_USER")==0) {
            if (!IsNotLoggedIn() && !IsNotManager())
            {
                system("clear");
                MenuCariUser();
            }
        }
        
        else if(strcasecmp(op,"TAMBAH_DOKTER")==0) {
            if (!IsNotLoggedIn() && !IsNotManager())
            {
                system("clear");
                MenuTambahDokter();
            }
        }
        else if(strcasecmp(op,"PINDAH_DOKTER")==0) {
            char ruang1[100];
            char ruang2[100];
            scanf("%s %s",ruang1,ruang2);
            if (!IsNotLoggedIn() && !IsNotManager())
            {
                system("clear");
                PindahDokter(ruang1,ruang2);
            }
        }
        else if(strcasecmp(op,"ASSIGN_DOKTER")==0) {
            if (!IsNotLoggedIn() && !IsNotManager())
            {
                system("clear");
                MenuAssignDokter();
            }
        }
        else if(strcasecmp(op,"UBAH_DENAH")==0) {
            if (!IsNotLoggedIn() && !IsNotManager())
            {
                int row,col;
                scanf("%d %d",&row,&col);
                system("clear");
                RemakeDenah(row,col);
            }
        }
        else if(strcasecmp(op,"LIHAT_ANTRIAN")==0) {
            if (!IsNotLoggedIn() && !IsNotManager())
            {
                system("clear");
                PrintAntrian();
            }
        }
        
        

    }while(strcasecmp(op,"EXIT"));
    MenuSave();
    return 0;
}