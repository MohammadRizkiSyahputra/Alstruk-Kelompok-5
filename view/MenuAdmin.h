#pragma once
#include <iostream>
using namespace std;

class MenuAdmin
{
public:
    static void tampilkanMenu()
    {
        cout << "\n===================" << endl;
        cout << "    MENU ADMIN" << endl;
        cout << "===================" << endl;
        cout << "1. Lihat Semua Data Nasabah" << endl;
        cout << "2. Ubah Status Nasabah" << endl;
        cout << "3. Cari Nasabah" << endl;
        cout << "4. Manage Antrian Nasabah" << endl;
        cout << "0. Log out" << endl;
        cout << "Masukkan pilihan: ";
    }
};