#pragma once
#include <iostream>
#include "../controller/transaksi_controller.h"
#include "../datastructure/tree.h"
#include "../utils/utility.h"
#include "../model/Nasabah.h"

void transfer(Nasabah* nasabahAkun, BinaryTreeNasabah* tree) {
    if (!tree) {
        std::cerr << "[ERROR] tree is nullptr in transfer()\n";
        return;
    }
    string label;
    int nominal;
    string noRek;
    Nasabah* nasabahTujuan = nullptr;
    string tanggal;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    label = getSafeLine("Masukkan label transaksi: ");
    while (true) {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        noRek = getSafeLine("Masukkan nomor rekening nasabah: ");
        if (tree->findByRekening(noRek)) {
            nasabahTujuan = tree->findByRekening(noRek);
            break;
        } else {
            std::cout << "Tidak ada nasabah dengan nomor rekening tersebut. Silahkan coba lagi. \n";
            continue;
        }
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Masukkan nominal: ";
    std::cin >> nominal;
    while (true) {
        std::cout << "Masukkan tanggal: ";
        std::cin >> tanggal;
        if (isValidDateFormat(tanggal)) {
            break;
        } else {
            std::cout << "Tanggal tidak valid\n";
            continue;
        }
        
    }
    tambahTransaksi(nasabahAkun, nasabahTujuan, label, nominal, tanggal);
    lihatTransaksi(nasabahAkun->listTransaksi.getHead());
}

void lihatListTransaksi(Nasabah* nasabahAkun) {
    LinkedList<DataTransaksi>::Node* current = nasabahAkun->listTransaksi.getHead();
    while (current) {
        lihatTransaksi(current);
        current = current->next;
    }
}

void cariTransaksi(Nasabah* nasabahAkun, string label) {
    LinkedList<DataTransaksi>::Node* current = nasabahAkun->listTransaksi.getHead();
    while (current) {
        string currentLabel = current->data.label;
        std::transform(currentLabel.begin(), currentLabel.end(), currentLabel.begin(), ::tolower);
        std::transform(label.begin(), label.end(), label.begin(), ::tolower);

        if (currentLabel.find(label) != string::npos) {
            lihatTransaksi(current);
            current = current->next;
        }
    }
}


