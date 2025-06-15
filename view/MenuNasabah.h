#pragma once
#include <iostream>
using namespace std;

class MenuNasabah
{
public:
    static void tampilkanMenu(const string &nama)
    {
        cout << "\n======================" << endl;
        cout << "   MENU NASABAH (" << nama << ")" << endl;
        cout << "======================" << endl;
        cout << "1. Informasi" << endl;
        cout << "2. Transaksi" << endl;
        cout << "3. Layanan CS" << endl;
        cout << "0. Log Out" << endl;
        cout << "Masukkan pilihan: ";
    }

    static void tampilkanMenuTransaksi(const string &nama)
    {
        cout << "\n======================" << endl;
        cout << "   MENU Transaksi (" << nama << ")" << endl;
        cout << "======================" << endl;
        cout << "1. Transfer Uang" << endl;
        cout << "0. Kembali" << endl;
        cout << "Masukkan pilihan: ";
    }

    static void tampilkanMenuInformasi(const string &nama)
    {
        cout << "\n======================" << endl;
        cout << "   Selamat datang di menu Informasi, (" << nama << ")" << endl;
        cout << "======================" << endl;
        cout << "1. Cek Saldo" << endl;
        cout << "2. Rekap Transaksi" << endl;
        cout << "0. Kembali" << endl;
        cout << "Masukkan pilihan: ";
    }

    static void tampilkanMenuLayananCS(const string &nama)
    {
        cout << "\n======================" << endl;
        cout << "   Selamat datang di Layanan CS, (" << nama << ")" << endl;
        cout << "======================" << endl;
        cout << "1. Simpan Pinjam" << endl;
        cout << "2. Masalah Rekening" << endl;
        cout << "3. Investasi" << endl;
        cout << "4. Lainnya" << endl;
        cout << "0. Kembali" << endl;
        cout << "Masukkan pilihan: ";
    }
};
