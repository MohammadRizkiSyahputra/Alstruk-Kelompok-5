#pragma once

#include <iostream>
#include "../controller/admin_controller.h"
#include "../controller/nasabah_controller.h"
#include "../controller/login_controller.h"
#include "../controller/register_controller.h"
#include "../datastructure/hash.h"
#include "../datastructure/tree.h"
#include "../datastructure/datadummy.h"
#include "../datastructure/cs_queue.h"
#include "../view/MainView.h"

using namespace std;

using Node = Hash::Node;

class MainController
{
private:
    Hash hashTable;
    BinaryTreeNasabah tree;
    RegisterController regController;
    LoginController loginController;
    bool exitApp = false;
    CSQueue csTable1, csTable2, csTable3; // For each meja

public:
    MainController()
        : regController(&hashTable, &tree),
          loginController(&hashTable, &tree, &csTable1, &csTable2, &csTable3)
    {
    }

    void run()
    {
        char pilihan;
        MainView::clearScreen();
        loadDummyData(hashTable, tree);

        while (!exitApp)
        {
            MainView::tampilkanMenuUtama();
            cin >> pilihan;

            switch (pilihan)
            {
            case '1':
                regController.RegisterUser();
                break;
            case '2':
                loginController.runLoginProcess();
                break;
            case '3':
                cout << "\n=== HashTable Akun ===" << endl;
                hashTable.printHashTable();

                cout << "\n=== BinaryTree Nasabah ===" << endl;
                tree.DisplayInOrderAllNasabah();
                break;
            case '0':
                exitApp = true;
                break;
            default:
                MainView::tampilkanPesanTidakValid();
            }
        }
    }
};