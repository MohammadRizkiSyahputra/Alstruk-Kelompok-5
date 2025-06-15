#pragma once
#include "../datastructure/tree.h"
#include "../view/MenuNasabah.h"
#include "../datastructure/cs_queue.h"
#include "../view/TransaksiView.h"
#include <iostream>


using namespace std;

class MenuNasabahController
{
private:
    BinaryTreeNasabah *tree;
    string username;
    CSQueue *csTable1;
    CSQueue *csTable2;
    CSQueue *csTable3;

public:
    MenuNasabahController(BinaryTreeNasabah *tree, const string &username, CSQueue *cs1, CSQueue *cs2, CSQueue *cs3)
        : tree(tree), username(username), csTable1(cs1), csTable2(cs2), csTable3(cs3) {}

    void run(Nasabah* nasabahAkun, BinaryTreeNasabah* tree)
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
                menuInformasi(nasabahAkun);
                break;
            case '2':
                menuTransaksi(nasabahAkun, tree);
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

    void menuInformasi(Nasabah* nasabahAkun)
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
                lihatListTransaksi(nasabahAkun);
                break;
            case '0':
                break;
            default:
                cout << "Pilihan tidak valid.\n";
            }
        } while (pilihan != '0');
    }

    void menuTransaksi(Nasabah* nasabahAkun, BinaryTreeNasabah* tree)
    {
        char pilihan;
        do
        {
            MenuNasabah::tampilkanMenuTransaksi(username);
            cin >> pilihan;
            switch (pilihan)
            {
            case '1':
                transfer(nasabahAkun, tree);
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
        // Tampilkan status antrian jika sudah pernah booking
        cout << "\nStatus Antrian Anda:\n";
        bool adaAntrian = false;
        for (int i = 1; i <= 3; ++i)
        {
            CSQueue *queue = (i == 1) ? csTable1 : (i == 2) ? csTable2
                                                            : csTable3;
            CSQueueNode *myNode = queue->findByUsername(username);
            if (myNode)
            {
                cout << "Nomor Antrian: " << myNode->queue_id << endl;
                cout << "Tujuan: " << myNode->tujuanCS << endl;
                cout << "Meja CS: " << myNode->cs_table << endl;
                CSQueueNode *active = queue->getActive();
                if (active)
                    cout << "Sedang dipanggil: " << active->queue_id << " (" << active->username << ")\n";
                adaAntrian = true;
                break;
            }
        }
        if (!adaAntrian)
            cout << "Anda belum memiliki antrian layanan CS.\n";

        char pilihan;
        do
        {
            cout << "\n=== Layanan CS ===\n";
            cout << "1. Simpan Pinjam\n";
            cout << "2. Masalah Rekening\n";
            cout << "3. Investasi\n";
            cout << "4. Lainnya\n";
            cout << "5. Kembali\n";
            cout << "Pilih layanan: ";
            cin >> pilihan;
            cin.ignore();

            if (pilihan == '5')
                break;

            string tujuanCS;
            int cs_table = 0;
            if (pilihan == '1')
            {
                tujuanCS = "Simpan Pinjam";
                cs_table = 1;
            }
            else if (pilihan == '2')
            {
                tujuanCS = "Masalah Rekening";
                cs_table = 3;
            }
            else if (pilihan == '3')
            {
                tujuanCS = "Investasi";
                cs_table = 2;
            }
            else if (pilihan == '4')
            {
                cout << "Masukkan tujuan layanan: ";
                getline(cin, tujuanCS);
                cs_table = 3; // Default meja 3 for 'lainnya'
            }
            else
            {
                cout << "Pilihan tidak valid.\n";
                continue;
            }

            // Pilih KCP
            cout << "\nPilih KCP:\n";
            cout << "1. KCP Jakarta\n";
            cout << "2. KCP Bekasi\n";
            cout << "3. KCP Tangerang\n";
            cout << "4. Kembali\n";
            cout << "Pilih: ";
            int kcp;
            cin >> kcp;
            cin.ignore();
            if (kcp == 4)
                continue;
            string kcp_code;
            if (kcp == 1)
                kcp_code = "JKT";
            else if (kcp == 2)
                kcp_code = "BKS";
            else if (kcp == 3)
                kcp_code = "TGR";
            else
            {
                cout << "Pilihan tidak valid.\n";
                continue;
            }

            // Pilih Jam
            cout << "\nPilih Jam:\n";
            for (int i = 8; i <= 15; ++i)
                cout << (i - 7) << ". " << i << ".00\n";
            cout << "9. Kembali\n";
            cout << "Pilih: ";
            int jam;
            cin >> jam;
            cin.ignore();
            if (jam == 9)
                continue;
            if (jam < 1 || jam > 8)
            {
                cout << "Pilihan tidak valid.\n";
                continue;
            }
            int session_code = 7 + jam; // 8..15

            // Enqueue
            CSQueue *queue = (cs_table == 1) ? csTable1 : (cs_table == 2) ? csTable2
                                                                          : csTable3;
            queue->enqueue(username, tujuanCS, kcp_code, session_code, cs_table);

            // Show queue info setelah booking
            CSQueueNode *myNode = queue->tail;
            cout << "\nBooking berhasil!\n";
            cout << "Nomor Antrian: " << myNode->queue_id << endl;
            cout << "Tujuan: " << myNode->tujuanCS << endl;
            cout << "Meja CS: " << myNode->cs_table << endl;
            cout << "==============================" << endl;
            break;
        } while (true);
    }
};
