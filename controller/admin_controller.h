#pragma once
#include "../datastructure/tree.h"
#include "../datastructure/hash.h"
#include "../view/MenuAdmin.h"
#include "../datastructure/cs_queue.h"
#include <limits>
#include <iostream>
#include <iomanip>
using namespace std;

using Node = Hash::Node;

class MenuAdminController
{
private:
    BinaryTreeNasabah *tree;
    Hash *hash;
    CSQueue *csTable1;
    CSQueue *csTable2;
    CSQueue *csTable3;

public:
    MenuAdminController(BinaryTreeNasabah *tree, Hash *hash, CSQueue *cs1, CSQueue *cs2, CSQueue *cs3)
        : tree(tree), hash(hash), csTable1(cs1), csTable2(cs2), csTable3(cs3) {}

    void run()
    {
        char pilihan;
        bool logout = false;
        while (!logout)
        {
            MenuAdmin::tampilkanMenu();
            cin >> pilihan;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            switch (pilihan)
            {
            case '1':
                lihatSemuaDataNasabah();
                break;
            case '2':
                ubahStatusNasabah();
                break;
            case '3':
                cariNasabah();
                break;
            case '4':
                manageAntrianCS();
                break;
            case '0':
                logout = true;
                break;
            default:
                cout << "Pilihan tidak valid.\n";
            }
        }
    }

    void lihatSemuaDataNasabah()
    {
        cout << "\n===== DATA SEMUA NASABAH =====" << endl;
        Node **hashTable = hash->getTable();
        int tableSize = hash->getTableSize();
        bool dataDitemukan = false;
        for (int i = 0; i < tableSize; ++i)
        {
            Node *travel = hashTable[i];
            while (travel != nullptr)
            {

                if (travel->username == "admin")
                {
                    travel = travel->next;
                    continue;
                }

                dataDitemukan = true;
                // Cari data nasabah di tree menggunakan IdNasabah dari hash
                Nasabah *nasabahData = tree->searchNasabah(travel->IdNasabah);

                cout << "----------------------------------------" << endl;
                // Data dari Hash Table
                cout << "IdNasabah      : " << travel->IdNasabah << endl;
                cout << "Username       : " << travel->username << endl;
                cout << "NIK            : " << travel->nik << endl;
                cout << "Pin            : " << string(travel->pin.length(), '*') << endl;

                // Data dari Tree
                if (nasabahData != nullptr)
                {
                    cout << "Nomor Rekening : " << nasabahData->NoRekening << endl;
                    cout << "Saldo          : Rp" << fixed << setprecision(2) << nasabahData->saldo << endl;
                    cout << "Status         : " << (nasabahData->aktif ? "Aktif" : "Blokir") << endl;
                }
                else
                {
                    cout << "Detail rekening (saldo, status) tidak ditemukan." << endl;
                }
                travel = travel->next;
            }
        }

        if (!dataDitemukan)
        {
            cout << "Belum ada data nasabah yang terdaftar.\n";
        }
        cout << "==========================================" << endl;
    }

    void ubahStatusNasabah()
    {
        string noRekening;
        cout << "\n--- Ubah Status Aktivasi Nasabah ---" << endl;
        cout << "Masukkan Nomor Rekening: ";
        getline(cin, noRekening);

        // Cari nasabah di tree berdasarkan nomor rekening
        Nasabah *nasabah = tree->findByRekening(noRekening);

        // Jika nasabah ditemukan
        if (nasabah != nullptr)
        {
            cout << "--- Detail Nasabah ---" << endl;
            cout << "ID Nasabah     : " << nasabah->IdNasabah << endl;
            cout << "Nomor Rekening : " << nasabah->NoRekening << endl;
            string statusSekarang = nasabah->aktif ? "Aktif" : "Blokir";
            cout << "Status Saat Ini: " << statusSekarang << endl;
            cout << "----------------------" << endl;

            char konfirmasi;
            string statusSelanjutnya = nasabah->aktif ? "Blokir" : "Aktif";
            cout << "Ubah status nasabah menjadi '" << statusSelanjutnya << "'? (y/n): ";
            cin >> konfirmasi;
            cin.ignore();

            if (konfirmasi == 'y' || konfirmasi == 'Y')
            {
                // Ubah status (jika true jadi false, jika false jadi true)
                nasabah->aktif = !nasabah->aktif;
                cout << "\nBerhasil! Status nasabah telah diubah menjadi '" << statusSelanjutnya << "'." << endl;
            }
            else
            {
                cout << "\nPerubahan status dibatalkan." << endl;
            }
        }
        else
        {
            // Jika nasabah tidak ditemukan
            cout << "\nError: Nasabah dengan nomor rekening '" << noRekening << "' tidak ditemukan." << endl;
        }
    }

    void cariNasabah()
    {
        string noRekening;
        cout << "\n--- Cari Detail Nasabah ---" << endl;
        cout << "Masukkan Nomor Rekening: ";
        getline(cin, noRekening);

        Nasabah *nasabahData = tree->findByRekening(noRekening);

        // Jika nasabah ditemukan di Tree
        if (nasabahData != nullptr)
        {
            Node *akunData = nullptr;

            // Cari data Akun di Hash Table menggunakan IdNasabah sebagai kunci
            Node **hashTable = hash->getTable();
            int tableSize = hash->getTableSize();

            for (int i = 0; i < tableSize; ++i)
            {
                Node *travel = hashTable[i];
                while (travel != nullptr)
                {
                    if (travel->IdNasabah == nasabahData->IdNasabah)
                    {
                        akunData = travel;
                        break; // Keluar dari while loop jika sudah ketemu
                    }
                    travel = travel->next;
                }
                if (akunData != nullptr)
                {
                    break; // Keluar dari for loop jika sudah ketemu
                }
            }

            cout << "\n--- Detail Nasabah Ditemukan ---" << endl;
            cout << "----------------------------------------" << endl;
            cout << "IdNasabah      : " << nasabahData->IdNasabah << endl;

            // Tampilkan data dari Akun jika ditemukan
            if (akunData != nullptr)
            {
                cout << "Username       : " << akunData->username << endl;
                cout << "NIK            : " << akunData->nik << endl;
                cout << "Pin (masked)   : " << string(akunData->pin.length(), '*') << endl;
            }
            else
            {
                cout << "Data Akun (username, NIK) tidak ditemukan di Hash Table." << endl;
            }

            // Tampilkan data dari Nasabah
            cout << "Nomor Rekening : " << nasabahData->NoRekening << endl;
            cout << "Saldo          : Rp" << fixed << setprecision(2) << nasabahData->saldo << endl;
            cout << "Status         : " << (nasabahData->aktif ? "Aktif" : "Blokir") << endl;
            cout << "----------------------------------------" << endl;
        }
        else
        {
            // Jika nasabah tidak ditemukan di Tree
            cout << "\nError: Nasabah dengan nomor rekening '" << noRekening << "' tidak ditemukan." << endl;
        }
    }

    void manageAntrianCS()
    {
        while (true)
        {
            cout << "\n=== Manage Antrian Layanan CS ===\n";
            cout << "1. Antrian CS Meja 1\n";
            cout << "2. Antrian CS Meja 2\n";
            cout << "3. Antrian CS Meja 3\n";
            cout << "4. Kembali\n";
            cout << "Pilih: ";
            int meja;
            cin >> meja;
            cin.ignore();
            if (meja == 4)
                break;
            CSQueue *queue = (meja == 1) ? csTable1 : (meja == 2) ? csTable2
                                                                  : csTable3;
            cout << "\nDaftar Antrian:\n";
            queue->tampil();
            cout << "Tekan 1 untuk panggil berikutnya, 2 untuk kembali: ";
            int aksi;
            cin >> aksi;
            cin.ignore();
            if (aksi == 1)
            {
                queue->dequeue();
                cout << "Antrian berikutnya dipanggil!\n";
            }
        }
    }
};