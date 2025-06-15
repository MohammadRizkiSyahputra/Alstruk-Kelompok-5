#include "../datastructure/linkedList.h"
#include "Nasabah.h"

struct DataTransaksi {
    string label;
    int jumlahNominal;
    bool diterima;
    string idNasabah;
    string tanggal;
    DataTransaksi(string label, int num, string id, bool recieved, string tanggal) : label(label), jumlahNominal(num), diterima(recieved), idNasabah(id), tanggal(tanggal) {};
};

