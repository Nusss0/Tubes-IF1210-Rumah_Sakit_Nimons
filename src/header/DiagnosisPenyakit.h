#ifndef DIAGNOSIS_PENYAKIT_H
#define DIAGNOSIS_PENYAKIT_H




void GetDataPenyakit();
// read file penyakit.csv dan store data penyakit ke dataPenyakit
void CreateListPenyakit(arrPenyakit* arr,int capacity);
// create list dynamic arrPenyakit
void ReAllocListPenyakit(arrPenyakit* arr, int add);
void MenuDiagnosa();
void DiagnosePasien(int idxi, int idxj);
void AssignPenyakit(const char* username, const char*namaPenyakit);




#endif