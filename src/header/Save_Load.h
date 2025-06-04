#ifndef SAVE_LOAD_H
#define SAVE_LOAD_H

void MenuSave();
/*Proses Main di save*/

void Save();
/*Save File" yang ada serta membuat folder yang diminta*/

void WriteUser(const char* input);
/*Simpan List User ke user.csv baru*/

void WriteConfig(const char* input);
/*Simpan Data Config ke config.txt*/

int RetID(const char* username);
/*Ret ID berdasarkan username*/
#endif