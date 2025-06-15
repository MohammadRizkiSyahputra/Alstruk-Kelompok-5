#pragma once
#include "../datastructure/hash.h"
#include "../datastructure/tree.h"
#include "../controller/admin_controller.h"
#include "../controller/nasabah_controller.h"
#include <iostream>
using namespace std;

class LoginController
{
private:
    int attempt{};
    Hash *hashTable;
    BinaryTreeNasabah *tree;
    CSQueue *csTable1;
    CSQueue *csTable2;
    CSQueue *csTable3;

public:
    LoginController(Hash *hashTable, BinaryTreeNasabah *tree, CSQueue *cs1, CSQueue *cs2, CSQueue *cs3)
    {
        this->hashTable = hashTable;
        this->tree = tree;
        this->csTable1 = cs1;
        this->csTable2 = cs2;
        this->csTable3 = cs3;
    }

    void runLoginProcess()
    {
        string username, pin;

        cout << endl
             << "=== LOGIN ===" << endl;
        cout << "Masukkan username : ";
        cin >> username;

        if (!hashTable->isUsernameExist(username))
        {
            cout << "Akun tidak ditemukan." << endl;
            return;
        }

        cout << "Masukkan PIN      : ";
        cin >> pin;

        // Check for successful login
        if (hashTable->isNodeFound(username, pin))
        {
            attempt = 0;

            if (username == "admin")
            {
                cout << "\nLogin berhasil!" << endl;
                cout << "Selamat datang, " << username << "!" << endl;
                MenuAdminController adminMenu(tree, hashTable, csTable1, csTable2, csTable3);
                adminMenu.run();
            }
            else
            {
                string idNasabah = hashTable->getIdNasabahByUsername(username);
                if (!tree->getStatusAktifById(idNasabah))
                {
                    cout << "\nAkun Anda saat ini dalam status terblokir." << endl;
                    cout << "Silakan hubungi admin untuk bantuan." << endl;
                    return;
                }
                else
                {
                    cout << "\nLogin berhasil!" << endl;
                    cout << "Selamat datang, " << username << "!" << endl;
                    MenuNasabahController nasabahMenu(tree, username, csTable1, csTable2, csTable3);
                    nasabahMenu.run();
                }
            }
        }
        else
        {
            cout << "\nLogin gagal! Username atau PIN salah." << endl;
            attempt++;
            string idNasabah = hashTable->getIdNasabahByUsername(username);

            // Block account after 3 failed attempts
            if (attempt >= 3)
            {
                tree->updateStatusAktifById(idNasabah, false);
                cout << "Akun Anda telah diblokir karena 3x salah memasukkan PIN." << endl;
                cout << "Silakan hubungi admin untuk bantuan." << endl;
                attempt = 0; // Reset counter after blocking
            }
        }
    }
};