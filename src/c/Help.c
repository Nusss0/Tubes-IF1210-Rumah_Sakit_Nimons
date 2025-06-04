#include <string.h>
#include <stdio.h>
#include "../header/ADT.h"
#include "../header/user.h"


void MenuHelp () {
    printf("=====================================================\n");
    printf("                      MENU HELP                      \n");
    printf("=====================================================\n\n");

    if (!is_Logged_in) {
        HelpNonLogin();
    }
    else if (strcasecmp(user.role, "DOKTER") == 0) {
        HelpDokter();
    }
    else if (strcasecmp(user.role, "PASIEN") == 0) {
        HelpPasien();
    }
    else if (strcasecmp(user.role, "MANAGER") == 0) {
        HelpManager();
    }

    Footnote();
}


void HelpDokter() {
    printf("Halo Dokter %s. Kamu memanggil command HELP. Kamu pasti sedang kebingungan.\n", user.username);
    printf("Berikut adalah hal-hal yang dapat kamu lakukan sekarang:\n\n");

    printf("    1. DIAGNOSIS       : Melakukan diagnosis penyakit pasien\n");
    printf("    2. NGOBATIN        : Memberikan obat ke pasien yang sudah didiagnosis\n");
    printf("    3. LIHAT_DENAH     : Melihat denah rumah sakit\n");
    printf("    4. LIHAT_RUANGAN   : Melihat informasi tiap ruangan\n");
    printf("    5. LUPA_PASSWORD   : Buat password baru dengan kode unik\n");
    printf("    6. LOGOUT          : Keluar dari akun Anda\n\n");
}

void HelpManager() {
    printf("Halo Manager %s. Kamu memanggil command HELP. Bingung ya? Santai, ini list-nya:\n\n", user.username);

    printf("    1. TAMBAH_DOKTER   : Tambahkan dokter baru ke sistem\n");
    printf("    2. ASSIGN_DOKTER   : Assign dokter ke ruangan tertentu\n");
    printf("    3. PINDAH_DOKTER   : PINDAH dokter ke ruangan tertentu\n");
    printf("    4. LIHAT_USER      : Lihat semua pengguna\n");
    printf("    5. LIHAT_PASIEN    : Lihat daftar pasien\n");
    printf("    6. LIHAT_DOKTER    : Lihat daftar dokter\n");
    printf("    7. CARI_USER       : Cari pengguna berdasarkan ID/username\n");
    printf("    8. LIHAT_ANTRIAN   : Melihat daftar antrian tiap ruangan\n");
    printf("    9. UBAH_DENAH      : Ubah ukuran denah rumah sakit\n");
    printf("    10. LIHAT_DENAH    : Lihat denah rumah sakit\n");
    printf("    11. LIHAT_RUANGAN  : Lihat info tiap ruangan\n");
    printf("    12. LUPA_PASSWORD  : Buat password baru dengan kode unik\n");
    printf("    13. LOGOUT         : Keluar dari akun Anda\n");
    printf("    14. EXIT           : Menutup program\n\n");
}

void HelpPasien() {
    printf("Halo %s. Kamu memanggil command HELP. Bingung ya? Nih yang bisa kamu lakukan:\n\n", user.username);

    printf("    1. DAFTAR_CHECKUP  : Daftar pemeriksaan ke dokter\n");
    printf("    2. ANTRIAN         : Lihat antrian dan status kamu\n");
    printf("    3. MINUM_PENAWAR   : Minum obat yang diberikan dokter\n");
    printf("    4. PULANG          : Keluar dari rumah sakit setelah sehat\n");
    printf("    5. LIHAT_DENAH     : Lihat denah rumah sakit\n");
    printf("    6. LIHAT_RUANGAN   : Lihat info tiap ruangan\n");
    printf("    7. LUPA_PASSWORD   : Buat password baru dengan kode unik\n");
    printf("    8. LOGOUT          : Keluar dari akun Anda\n\n");
}

void HelpNonLogin() {
    printf("Kamu belum login. Silakan login atau daftar dulu!\n\n");
    printf("    1. LOGIN           : Masuk ke akun yang sudah terdaftar\n");
    printf("    2. REGISTER        : Buat akun baru sebagai pasien\n");
    printf("    3. LUPA_PASSWORD   : Ganti password dengan kode unik\n\n");
}
void Footnote() {
    printf("=====================================================\n");
    printf("CATATAN:\n");
    printf("  - Ketik perintah dengan huruf kapital sesuai daftar.\n");
    printf("  - Gunakan input yang valid agar tidak terjadi error.\n");
    printf("  - Ketik EXIT untuk keluar dari sistem.\n");
    printf("=====================================================\n\n");
}
