#include <stdio.h>
#include "../header/user.h"
#include "../header/ADT.h"

char ToLower(char c) {
    if (c >= 'A' && c <= 'Z') {
        return c + 32;
    }
    return c;
}

char* RunLengthEncoding (const char* username){
    int len = strlen(username);
    int i = 0;
    char* store = (char*)malloc(20*sizeof(char));
    int k = 0;
    while(i<len){
         int count = 1; //Initial letter count
         for (int j = i; j<len; j++){ // Count how many letters
             if (ToLower(username[j]) == ToLower(username[j+1])){
                 count++; 
             }
             else {
                break; //Break if not the same 
             }
         }
        if(count==1){
            k+=sprintf(&store[k],"%c",ToLower(username[i]));
        }
        else{
            k+=sprintf(&store[k],"%d%c",count,ToLower(username[i]));
        }  //Convert count to string and store in store[]

        i += count; //Add index to new character
    } 
    return store;
 }


void MenuLupaPassword() {
    char username[20];
    char kode[50];

    printf("=====================================================\n");
    printf("                 LUPA PASSWORD PENGGUNA              \n");
    printf("=====================================================\n");

    printf("Username       : ");
    scanf("%s", username);

    if (!IsUserExist(username)) {
        printf("Username tidak terdaftar!\n");
        return;
    }

    // Generate kode verifikasi berdasarkan RLE username
    printf("Kode Unik      : ");
    scanf("%s", kode);

    // Validasi kode verifikasi
    if (strcmp(kode, RunLengthEncoding(username)) == 0) {
        is_Logged_in = true;

        // Ambil data user untuk update password (tanpa perlu password lama)
        GetData(username, "dummy"); // password lama gak dipakai

        printf("\nHalo %s %s, silakan daftar ulang password Anda!\n", user.role, user.username);
        printf("Password Baru  : ");
        scanf("%s", user.password);

        RenewPass(username, user.password);
        printf("Password berhasil diperbarui!\n");
    } else {
        printf("Kode unik salah!\n");
    }

    printf("=====================================================\n");
}


void RenewPass(const char* username, const char* password){
    for(int i = 0; i < arr_User.nEff;i++){
        if(strcasecmp(username,arr_User.arr[i].username)==0){
            strcpy(arr_User.arr[i].password,password);
            break;
        }
    }
}