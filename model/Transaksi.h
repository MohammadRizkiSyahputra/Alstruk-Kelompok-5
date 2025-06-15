#include "../datastructure/linkedList.h"
#include "Nasabah.h"

struct DataTransaksi {
    int jumlahNominal;
    bool diterima;
    string idNasabah;
    string tanggal;
    DataTransaksi(int num, string id, bool recieved, string tgl);
};

void tambahTransaksi(Nasabah nasabahAkun, Nasabah nasabahTujuan, int num, string tgl) {
    DataTransaksi transaksiAkun = DataTransaksi(num, nasabahTujuan.IdNasabah, tgl);
    DataTransaksi transaksiTujuan = DataTransaksi(-1*num, nasabahAkun.IdNasabah, true, tgl);
    nasabahAkun.listTransaksi.append(transaksiAkun);
    nasabahTujuan.listTransaksi.append(transaksiTujuan);
}

void listTransaksi(Nasabah nasabahAkun) {
    nasabahAkun.listTransaksi::Node* current = nasabahAkun.listTransaksi.getTail();
    while (current) {
        std::cout << 
            "Nasabah Tujuan: " << current->data.idNasabah << '\n' <<
            "Nominal Transfer: " << current->data.jumlahNominal << '\n' <<
            "Arah Transfer: " << (current->data.diterima) ? "Menerima" : "Memberi" << '\n' <<
            "Tanggal Transfer: " << current->data.tanggal << '\n\n';
        current = current->next;
    }
}

void cariTransaksi(Nasabah nasabahAkun) {
    
}