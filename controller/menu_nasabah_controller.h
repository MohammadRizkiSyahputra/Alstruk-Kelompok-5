#pragma once
#include "../view/MenuNasabah.h"
#include "../datastructure/antriancs.h"
#include <string>
#include <iostream>
using namespace std;

class MenuNasabahController {
public:
    void run(const string& nama) {
        char pilihan;
        bool keluar = false;
        while (!keluar) {
            MenuNasabah::tampilkanMenu(nama);
            cin >> pilihan;
            switch (pilihan) {
                case '1':
                    cout << "[INFORMASI] Fitur cek saldo & rekap transaksi (dummy)." << endl;
                    break;
                case '2':
                    cout << "[TRANSAKSI] Fitur transfer uang (dummy)." << endl;
                    break;
                case '3':
                    // Cek apakah sudah pernah booking
                    AntrianCS* antri = queueCS1.findById(idNasabah);
                    if (!antri) antri = queueCS2.findById(idNasabah);
                    if (!antri) antri = queueCS3.findById(idNasabah);
                    if (antri) {
                        cout << "\n=== STATUS ANTRIAN CS ===\n";
                        cout << "Nomor Antrian: " << antri->queueNumber << endl;
                        cout << "Tujuan: " << antri->tujuan << endl;
                        cout << "CS Table: " << antri->csTable << endl;
                        // Tampilkan siapa yang sedang dipanggil
                        AntrianCS* front = (antri->csTable == 1 ? queueCS1.getFront() : antri->csTable == 2 ? queueCS2.getFront() : queueCS3.getFront());
                        if (front)
                            cout << "Sedang dipanggil: " << front->queueNumber << " (" << front->namaNasabah << ")" << endl;
                        else
                            cout << "Belum ada antrian aktif.\n";
                    } else {
                        layananCS(idNasabah, namaNasabah, /*prioritas*/ false); // Ganti prioritas sesuai status_nasabah
                    }
                    break;
                case '4':
                    cout << "Log out berhasil." << endl;
                    keluar = true;
                    break;
                default:
                    cout << "Pilihan tidak valid." << endl;
            }
        }
    }
};

void layananCS(const string& idNasabah, const string& namaNasabah, bool prioritas) {
    while (true) {
        cout << "\n=== LAYANAN CS ===" << endl;
        cout << "1. Simpan Pinjam\n2. Masalah Rekening\n3. Investasi\n4. Lainnya\n5. Kembali\nPilih: ";
        int pilih; cin >> pilih;
        if (pilih == 5) return;

        string tujuan;
        if (pilih == 1) tujuan = "Simpan Pinjam";
        else if (pilih == 2) tujuan = "Masalah Rekening";
        else if (pilih == 3) tujuan = "Investasi";
        else if (pilih == 4) {
            cout << "Masukkan tujuan lain: "; cin.ignore(); getline(cin, tujuan);
        } else {
            cout << "Pilihan tidak valid.\n"; continue;
        }

        cout << "\nPilih KCP:\n1. KCP Jakarta\n2. KCP Bekasi\n3. KCP Tangerang\n4. Kembali\nPilih: ";
        int pilihKCP; cin >> pilihKCP;
        if (pilihKCP == 4) continue;
        string kcp, kcpCode;
        if (pilihKCP == 1) { kcp = "KCP Jakarta"; kcpCode = "JKT"; }
        else if (pilihKCP == 2) { kcp = "KCP Bekasi"; kcpCode = "BKS"; }
        else if (pilihKCP == 3) { kcp = "KCP Tangerang"; kcpCode = "TGR"; }
        else { cout << "Pilihan tidak valid.\n"; continue; }

        cout << "\nPilih Jam:\n";
        for (int i = 8; i <= 15; i++) cout << i-7 << ". " << i << ".00\n";
        cout << "9. Kembali\nPilih: ";
        int pilihJam; cin >> pilihJam;
        if (pilihJam == 9) continue;
        if (pilihJam < 1 || pilihJam > 8) { cout << "Pilihan tidak valid.\n"; continue; }
        string jam = to_string(pilihJam+7) + ".00";
        string sessionCode = to_string(pilihJam+7);

        // Tentukan CS Table
        int csTable = 2;
        if (prioritas) csTable = 1;
        else if (pilih == 2) csTable = 3;
        else if (pilih == 1 || pilih == 3) csTable = 2;

        // Hitung nomor antrian
        QueueCS* queue = (csTable == 1) ? &queueCS1 : (csTable == 2) ? &queueCS2 : &queueCS3;
        int nomor = queue->count + 1;
        string queueNum = kcpCode + "-" + sessionCode + "-" + (nomor < 10 ? "00" : (nomor < 100 ? "0" : "")) + to_string(nomor);

        // Simpan ke queue
        AntrianCS data;
        data.idNasabah = idNasabah;
        data.namaNasabah = namaNasabah;
        data.tujuan = tujuan;
        data.kcp = kcp;
        data.jam = jam;
        data.queueNumber = queueNum;
        data.csTable = csTable;
        queue->enqueue(data);

        cout << "\nReservasi berhasil!\nNomor Antrian Anda: " << queueNum << "\nCS Table: " << csTable << endl;
        break;
    }
}