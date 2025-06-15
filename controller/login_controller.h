#pragma once
#include "../datastructure/hash.h"
#include "../datastructure/tree.h"
#include <iostream>
using namespace std;

class LoginController {
private:
    int attempt{};
    Hash* hashTable;
    BinaryTreeNasabah* tree;

public:
    LoginController(Hash* hashTable, BinaryTreeNasabah* tree) {
        this->hashTable = hashTable;
        this->tree = tree;
    }

    bool loginUser() {
        string username, pin;

        cout << endl << "=== LOGIN NASABAH ===" << endl;
        cout << "Masukkan username : "; cin >> username;

        if(!hashTable->isUsernameExist(username)){
            cout << "Akun tidak ditemukan" << endl;
            return false;
        }

        cout << "Masukkan PIN      : ";
        cin >> pin;

        if (hashTable->isNodeFound(username, pin)){
            cout << "Login berhasil!" << endl;
            cout << "Selamat datang, " << username << "!" << endl;
            return true;
        } else {
            cout << "Login gagal! Username atau PIN salah." << endl;
            attempt++;
            string idNasabah = hashTable->getIdNasabahByUsername(username);
            if(attempt >= 3){
                tree->updateStatusAktifById(idNasabah, false);
                cout << "Akun anda diblokir karena salah 3x ketika memasukkan PIN, silakan hubungi admin." << endl;
            }
            return false;
        }
    }
};