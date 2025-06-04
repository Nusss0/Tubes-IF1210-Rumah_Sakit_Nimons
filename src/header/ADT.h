#ifndef ADT_H
#define ADT_H

#include <stdbool.h>

// ADT sederhana :  Data Penyakit
typedef struct
{
    int id;
    char nama_Penyakit[100];
    float suhu_Tubuh_Min;
    float suhu_Tubuh_Max;
    int tekanan_Darah_Sistolik_Min;
    int tekanan_Darah_Sistolik_Max;
    int tekanan_Darah_Diastolik_Min;
    int tekanan_Darah_Diastolik_Max;
    int detak_Jantung_Min;
    int detak_Jantung_Max;
    float saturasi_Oksigen_Min;
    float saturasi_Oksigen_Max;
    int kadar_Gula_Darah_Min;
    int kadar_Gula_Darah_Max;
    float berat_Badan_Min;
    float berat_Badan_Max;
    int tinggi_Badan_Min;
    int tinggi_Badan_Max;
    int kadar_Kolesterol_Min;
    int kadar_Kolesterol_Max;
    int trombosit_Min;
    int trombosit_Max;
} dataPenyakit;

typedef struct
{
    dataPenyakit *arr;
    int capacity;
    int nEff;
} arrPenyakit;

// ADT sederhana :  Data User
typedef struct
{
    int id;
    char username[50];
    char password[50];
    char role[20];
    char penyakit[50];
    float suhuTubuh;
    int tekanan_Darah_Sistolik;
    int tekanan_Darah_Diastolik;
    int detak_Jantung;
    float saturasi_Oksigen;
    int kadar_Gula_Darah;
    float berat_Badan;
    int tinggi_Badan;
    int kadar_Kolesterol;
    int trombosit;
    bool is_Diagnosed;
    bool is_Checked;
    int aura;
    // int banarich;
} dataUser;

typedef struct
{
    dataUser *arr;
    int capacity;
    int nEff;
} arrList;

typedef struct
{
    char username[20];
    int id;
    bool room;
    char nama_ruang[10];
} dataDokter;

typedef struct
{
    dataDokter data[100];
    int nEff;
} arrListDokter;

typedef struct queue
{
    dataUser data;      // data pasien
    char rincianObat[50][100];
    struct queue *next; // next queue
    struct queue *prev; // prev queue
} queue;

typedef struct
{
    char nama_ruang[100];
    char nama_dokter[50];
    int aura;
    int kapasitas;
    int antrian;
    int max_Antrian;
    queue *Pasien;
} dataRuang;

typedef struct
{
    dataRuang **data;
    int col;
    int row;
} denahRuang;

typedef struct
{
    char nama_pasien[20];
    int i;
    int j;      // i dan j menyatakan ruangan
    int urutan; // buat tau dia di antrian ke berapa
} antrian;

typedef struct
{
    antrian data[100];
    int nEff;
} mapAntrian;

typedef struct
{
    int id_Obat;
    char nama_Obat[20];
} dataObat; // id dan urutan minum obat

typedef struct
{
    int id_Obat;
    int id_Penyakit;
    char nama_Penyakit[50];
    int urutan_Minum;
} mapObatPenyakit;

typedef struct
{
    dataObat *data_Obat;
    mapObatPenyakit *data_Obat_penyakit;
    int capacity;
    int nEff_Penyakit;
    int nEff_Obat;
} arrObat; // list obat

typedef struct
{
    int idObat[50]; // asumsi sementara 50 maks jenis obat kayanya harus di dinamiskan later
    int jumlahObat;
    int idPasien;
} InventoryPasien;

typedef struct
{
    int idObat[50]; // asumsi sementara 50 maks jenis obat kayanya harus di dinamiskan later
    int jumlahObat;
    int idPasien;
} DataStack;

typedef struct
{
    DataStack data;
    int top;
    int capacity;
} Lambung;

typedef struct
{
    Lambung lambung;
    InventoryPasien invent;
    int idPasien;
    bool urut;
    int isMinum;
    bool pulang;
} DataPasien;

typedef struct
{
    DataPasien *data;
    int capacity;
    int nEff;
    int nLambung;
    int nInvent;
}   InventLambungPasien;



extern InventLambungPasien invent_Lambung;
extern arrList arr_User; //variabel arrUser secara global
extern dataUser user; //Variabel User secara global
extern arrListDokter arr_Dokter;
extern bool is_Logged_in;  //Menandakan sudah login (dimasukan login checker)
extern denahRuang denah;
extern mapAntrian list_antrian;
extern arrObat arr_Obat;
extern arrPenyakit arr_Penyakit;
#endif