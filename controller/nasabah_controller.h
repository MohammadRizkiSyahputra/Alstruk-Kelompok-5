#pragma once
#include "../datastructure/tree.h"
#include "../view/MenuNasabah.h"
#include <iostream>
using namespace std;

class MenuNasabahController
{
private:
    BinaryTreeNasabah *tree;
    string username;

public:
    MenuNasabahController(BinaryTreeNasabah *tree, const string &username)
        : tree(tree), username(username) {}

    void run()
    {
        char pilihan;
        bool logout = false;
        while (!logout)
        {
            MenuNasabah::tampilkanMenu(username);
            cin >> pilihan;
            switch (pilihan)
            {
            case '1':
                menuInformasi();
                break;
            case '2':
                menuTransaksi();
                break;
            case '3':
                menuLayananCS();
                break;
            case '0':
                logout = true;
                break;
            default:
                cout << "Pilihan tidak valid.\n";
            }
        }
    }

    void menuInformasi()
    {
        char pilihan;
        do
        {
            MenuNasabah::tampilkanMenuInformasi(username);
            cin >> pilihan;
            switch (pilihan)
            {
            case '1':
                cout << "Fitur cek saldo belum diimplementasikan.\n";
                break;
            case '2':
                cout << "Fitur rekap transaksi belum diimplementasikan.\n";
                break;
            case '0':
                break;
            default:
                cout << "Pilihan tidak valid.\n";
            }
        } while (pilihan != '0');
    }

    void menuTransaksi()
    {
        char pilihan;
        do
        {
            MenuNasabah::tampilkanMenuTransaksi(username);
            cin >> pilihan;
            switch (pilihan)
            {
            case '1':
                cout << "Fitur transfer uang belum diimplementasikan.\n";
                break;
            case '0':
                break;
            default:
                cout << "Pilihan tidak valid.\n";
            }
        } while (pilihan != '0');
    }

    void menuLayananCS()
    {
        char pilihan;
        do
        {
            MenuNasabah::tampilkanMenuLayananCS(username);
            cin >> pilihan;
            switch (pilihan)
            {
            case '1':
            case '2':
            case '3':
            case '4':
                cout << "Fitur layanan CS belum diimplementasikan.\n";
                break;
            case '0':
                break;
            default:
                cout << "Pilihan tidak valid.\n";
            }
        } while (pilihan != '0');
    }
};