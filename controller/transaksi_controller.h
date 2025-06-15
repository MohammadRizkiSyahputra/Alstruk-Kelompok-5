#pragma once
#include "../model/Nasabah.h"
#include "../model/Transaksi.h"
#include <algorithm>
#include <iostream>
#include <string>

void tambahTransaksi(Nasabah* nasabahAkun, Nasabah* nasabahTujuan, string label, int num, string tanggal) {
    DataTransaksi transaksiAkun = DataTransaksi(label, num, nasabahTujuan->IdNasabah, false, tanggal);
    DataTransaksi transaksiTujuan = DataTransaksi(label, num, nasabahAkun->IdNasabah, true, tanggal);
    nasabahAkun->listTransaksi.append(transaksiAkun);
    nasabahTujuan->listTransaksi.append(transaksiTujuan);
    
}

void lihatTransaksi(LinkedList<DataTransaksi>::Node* node) {
    string outArah = (node->data.diterima) ? "Menerima" : "Memberi";
    std::cout << 
        "=============================================================\n" <<
        "Label Transfer: " << node->data.label << '\n' <<
        "Nasabah Tujuan: " << node->data.idNasabah << '\n' <<
        "Nominal Transfer: " << node->data.jumlahNominal << '\n' <<
        "Arah Transfer: " << outArah << '\n' <<
        "Tanggal Transfer: " << node->data.tanggal << '\n' <<
        "=============================================================\n";
}
