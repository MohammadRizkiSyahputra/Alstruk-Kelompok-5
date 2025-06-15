#pragma once
#include <iostream>
using namespace std;

class MenuNasabah {
    public:
        static void tampilkanMenu(const string& nama) {
            cout << "\n======================" << endl;
            cout << "   MENU NASABAH (" << nama << ")" << endl;
            cout << "======================" << endl;
            cout << "1. Informasi" << endl;
            cout << "2. Transaksi" << endl;
            cout << "3. Layanan CS" << endl;
            cout << "4. Log Out" << endl;
            cout << "Masukkan pilihan: ";
        }
};