#pragma once

#include "../view/MenuAdmin.h"
#include "../datastructure/tree.h"
#include "../datastructure/hash.h"
#include "../datastructure/antriancs.h"
QueueCS queueCS1, queueCS2, queueCS3;

#include <iostream>
using namespace std;

class MenuAdminController { 
private:
    Hash* hashTable;
    BinaryTreeNasabah* treeNasabah;

public:
    MenuAdminController(Hash* hashTable, BinaryTreeNasabah* treeNasabah) {
        this->hashTable = hashTable;
        this->treeNasabah = treeNasabah;
    }

    void run() {
        char pilihan;
        bool keluar = false;
        while (!keluar) {
            MenuAdmin::tampilkanMenu();
            cin >> pilihan;
            switch (pilihan) {
                case '1':
                    tampilkanSemuaDataNasabah();
                    break;
                case '2':
                    ubahStatusNasabah();
                    break;
                case '3':
                    cariNasabahByRekening();
                    break;
                case '4':
                    manageAntrianCS();
                    break;
                case '5':
                    cout << "Log out berhasil." << endl;
                    keluar = true;
                    break;
                default:
                    cout << "Pilihan tidak valid." << endl;
            }
        }
    }
};

void tampilkanSemuaDataNasabah() {
    cout << "\n=== Daftar Semua Nasabah ===\n";
};

void ubahStatusNasabah() {
    cout << "aaa";
};

void cariNasabahByRekening() {
    cout << "aaa";
};

void manageAntrianCS() {
    while (true) {
        cout << "\n=== Manage Antrian Layanan CS ===\n";
        cout << "1. Antrian CS Meja 1\n2. Antrian CS Meja 2\n3. Antrian CS Meja 3\n4. Kembali\nPilih: ";
        int pilih; cin >> pilih;
        if (pilih == 4) return;
        QueueCS* queue = nullptr;
        if (pilih == 1) queue = &queueCS1;
        else if (pilih == 2) queue = &queueCS2;
        else if (pilih == 3) queue = &queueCS3;
        else { cout << "Pilihan tidak valid.\n"; continue; }

        cout << "\nDaftar Antrian:\n";
        queue->tampil();
        cout << "1. Panggil/Next Antrian\n2. Kembali\nPilih: ";
        int aksi; cin >> aksi;
        if (aksi == 1) {
            queue->dequeue();
            cout << "Antrian berikutnya dipanggil.\n";
        }
    }
}