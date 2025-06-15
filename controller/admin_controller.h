#pragma once
#include "../datastructure/tree.h"
#include "../view/MenuAdmin.h"
#include <iostream>
using namespace std;

class MenuAdminController
{
private:
    BinaryTreeNasabah *tree;

public:
    MenuAdminController(BinaryTreeNasabah *tree) : tree(tree) {}

    void run()
    {
        char pilihan;
        bool logout = false;
        while (!logout)
        {
            MenuAdmin::tampilkanMenu();
            cin >> pilihan;
            switch (pilihan)
            {
            case '1':
                tree->DisplayInOrderAllNasabah();
                break;
            case '2':
                // Implementasi ubah status nasabah
                cout << "Fitur ubah status nasabah belum diimplementasikan.\n";
                break;
            case '3':
                // Implementasi cari nasabah
                cout << "Fitur cari nasabah belum diimplementasikan.\n";
                break;
            case '4':
                // Implementasi manage antrian nasabah
                cout << "Fitur manage antrian nasabah belum diimplementasikan.\n";
                break;
            case '0':
                logout = true;
                break;
            default:
                cout << "Pilihan tidak valid.\n";
            }
        }
    }
};