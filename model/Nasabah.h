#pragma once

#include <iostream>
#include "Rekening.h"
#include "Layanan.h"
#include "../datastructure/linkedList.h"
#include "Transaksi.h"

using namespace std;

struct Nasabah {
    string IdNasabah;
    string nik;
    double saldo;
    string NoRekening;
    bool aktif;
    LinkedList<DataTransaksi> listTransaksi;
    
    Nasabah() = default;

    Nasabah(string IdNasabah, string nik, double saldo, string NoRekening, bool aktif = true)
        : IdNasabah(IdNasabah), nik(nik), saldo(saldo), NoRekening(NoRekening), aktif(aktif) {}
};
