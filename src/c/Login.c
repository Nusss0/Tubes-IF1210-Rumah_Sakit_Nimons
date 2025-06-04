#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#include "../header/ADT.h"
#include "../header/user.h"
#include "../header/ManageUser.h"


void DynData(char folder[]){
    CreateList(&arr_User,100);
    char path[100];
    sprintf(path,"%s%s%s","file/",folder,"/user.csv");
    FILE* fuser = fopen(path,"r");
    if (!fuser){
        printf("File tidak Terbaca");
        fclose(fuser);
        return;
    }
    char line[2048];
    char field[15][100];
    int i=0;
    int sum_dokter=0;
    
    while(fgets(line,sizeof(line),fuser)){
        GetField(line,field);
        arr_User.arr[i].id = atoi(field[0]);
        strcpy(arr_User.arr[i].username, field[1]);
        strcpy(arr_User.arr[i].password, field[2]);
        strcpy(arr_User.arr[i].role, field[3]);
        strcpy(arr_User.arr[i].penyakit, field[4]);
        arr_User.arr[i].suhuTubuh = atof(field[5]);
        arr_User.arr[i].tekanan_Darah_Sistolik = atoi(field[6]);
        arr_User.arr[i].tekanan_Darah_Diastolik = atoi(field[7]);
        arr_User.arr[i].detak_Jantung = atoi(field[8]);
        arr_User.arr[i].saturasi_Oksigen = atof(field[9]);
        arr_User.arr[i].kadar_Gula_Darah = atoi(field[10]);
        arr_User.arr[i].berat_Badan = atof(field[11]);
        arr_User.arr[i].tinggi_Badan = atoi(field[12]);
        arr_User.arr[i].kadar_Kolesterol = atoi(field[13]);
        arr_User.arr[i].trombosit = atoi(field[14]);
        arr_User.arr[i].aura = atoi(field[15]);
        // printf("%s's aura: %d\n",arr_User.arr[i].username, arr_User.arr[i].aura);
        if(strcmp(arr_User.arr[i].role,"dokter")==0){
            arr_Dokter.data[sum_dokter].id = arr_User.arr[i].id;
            strcpy(arr_Dokter.data[sum_dokter].username, arr_User.arr[i].username);
            arr_Dokter.nEff++;
            sum_dokter++;
        }
        arr_User.nEff ++;
        i++;
    }
    fclose(fuser);
    // for(int i=0;i<arr_User.nEff;i++){
    //     printf("%d. %s\n",arr_User.arr[i].id, arr_User.arr[i].username);
    // }
}

/*------------------------------------------------------------- F01 - LOGIN -------------------------------------------------------------*/ 

void MenuLogin() {
    char username[50];
    char password[50];

    printf("=====================================================\n");
    printf("                     LOGIN USER                      \n");
    printf("=====================================================\n");
    printf("Username : ");
    scanf("%s", username);
    printf("Password : ");
    scanf("%s", password);

    if (GetData(username, password)) {
        system("clear");
        printf(ANSI_COLOR_GREEN);
        printf("=====================================================\n");
        if (strcmp(user.role, "manager") == 0) {
            printf("Selamat pagi, Manager %s!\n", user.username);
        } else if (strcmp(user.role, "dokter") == 0) {
            printf("Selamat pagi, Dokter %s!\n", user.username);
        } else {
            printf("Selamat pagi, %s!\n", user.username);
            printf("Ada keluhan apa hari ini?\n");
        }
        printf("=====================================================\n");
        printf(ANSI_COLOR_RESET);
        is_Logged_in = true;
        printf("\n");
    } else {
        printf("Login gagal! Username atau password salah.\n");
    }
}

/* Meminta Input Username dan Password dari user, memvalidasi kecocokan, lalu Mengembalikan Pesan yang sesuai  */

void CreateList(arrList* arr,int capacity ){
    arr->arr = (dataUser*)malloc(capacity*sizeof(dataUser));
    arr->capacity = capacity;
    arr->nEff=0;
}
void ReAllocList(arrList* arr, int add){
    arr->arr = (dataUser*)realloc(arr->arr,(arr->capacity+add)*sizeof(dataUser));
    arr->capacity +=add;
}

void GetField(const char *line,char field[][100]){
    int field_idx=0, char_idx=0;
    for(int i=0 ; line[i]!='\0'&&line[i]!='\n';i++){  //looping hingga akhir line (baca karakter per karakter pada line)
        if(line[i] == ',' ||line[i] == ' '|| line[i] == ';' ){  //pembatas ditemukan 
            field[field_idx][char_idx]='\0'; //akhir dari char array berupa \0
            field_idx++; //next field
            char_idx=0; //reset char idx
        }
        else{ // jika tidak ditemukan pembatas copy char per char dari line
            field[field_idx][char_idx]=line[i];
            char_idx++;
        }
    }
    field[field_idx][char_idx]='\0'; //buat idxfield terakhir
}

/* Mengambil data perbaris di file .csv dan simpan ke array field*/

int GetData(char* username, const char* password){
    int i=0;
    while (i < arr_User.nEff){
        if(strcasecmp((arr_User.arr[i].username),(username))==0){ //cek apakah username terdapat di file?
            if(strcmp(arr_User.arr[i].password,password)==0 || is_Logged_in==true){  //jika pass bener, copy semua field ke dalam data type user
                //Penyesuaian Data type tiap bagian karena data type default dari csv = string/char
                user.id = arr_User.arr[i].id;
                strcpy(user.username, arr_User.arr[i].username);
                strcpy(user.password, arr_User.arr[i].password);
                strcpy(user.role, arr_User.arr[i].role);
                strcpy(user.penyakit, arr_User.arr[i].penyakit);
                user.suhuTubuh = arr_User.arr[i].suhuTubuh;
                user.tekanan_Darah_Sistolik = arr_User.arr[i].tekanan_Darah_Sistolik;
                user.tekanan_Darah_Diastolik = arr_User.arr[i].tekanan_Darah_Diastolik;
                user.detak_Jantung = arr_User.arr[i].detak_Jantung;
                user.saturasi_Oksigen = arr_User.arr[i].saturasi_Oksigen;
                user.kadar_Gula_Darah = arr_User.arr[i].kadar_Gula_Darah;
                user.berat_Badan = arr_User.arr[i].berat_Badan;
                user.tinggi_Badan = arr_User.arr[i].tinggi_Badan;
                user.kadar_Kolesterol = arr_User.arr[i].kadar_Kolesterol;
                user.trombosit = arr_User.arr[i].trombosit;

                return 1;
            }
            else{ //jika password tidak sama
                printf("Password salah untuk pengguna yang bernama %s!\n",arr_User.arr[i].username);
                return 0;
            }
        }
        i++;
    }
    printf("Tidak ada Manager, Dokter, atau pun Pasien yang bernama %s!\n",username);
    return 0;
}
void ResetData(dataUser *x){
    strcpy(x->penyakit, "-");
    x->suhuTubuh = -1;
    x->tekanan_Darah_Sistolik = -1;
    x->tekanan_Darah_Diastolik = -1;
    x->detak_Jantung = -1;
    x->saturasi_Oksigen = -1;
    x->kadar_Gula_Darah = -1;
    x->berat_Badan = -1;
    x->tinggi_Badan = -1;
    x->kadar_Kolesterol = -1;
    x->trombosit = -1;
    x->is_Diagnosed = false;
}
/* Mengambil data user dari file .csv dan simpan ke variable jika Usernam dan Passsword sesuai*/




