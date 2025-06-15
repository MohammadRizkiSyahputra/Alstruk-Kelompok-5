#pragma once
#include <iostream>
#include "../controller/transaksi_controller.h"
#include "../datastructure/tree.h"
#include "../utils/utility.h"
#include "../model/Nasabah.h"

BinaryTreeNasabah tree;

void transfer(Nasabah *nasabahAkun) {
    string label;
    int nominal;
    string idNasabah;
    Nasabah *nasabahTujuan;
    string tanggal;
    std::cout << "Masukkan label transaksi: ";
    label = getSafeLine(label);
    while (true) {
        std::cout << "Masukkan ID nasabah: ";    
        idNasabah = getSafeLine(idNasabah);
        if (tree.findNasabahById(idNasabah)) {
            nasabahTujuan = tree.findNasabahById(idNasabah);
            break;
        } else {
            std::cout << "Tidak ada nasabah dengan ID tersebut. Silahkan coba lagi. \n";
            continue;
        }
    }
    std::cout << "Masukkan nominal: ";
    std::cin >> nominal;
    while (true) {
        std::cout << "Masukkan tanggal: ";
        tanggal = getSafeLine(tanggal);
        if (isValidDateFormat(tanggal)) {
            break;
        } else {
            std::cout << "Tanggal tidak valid\n";
            continue;
        }
        
    }
    tambahTransaksi(*nasabahAkun, *nasabahTujuan, label, nominal, tanggal);
    lihatTransaksi(nasabahAkun->listTransaksi.getHead());
}