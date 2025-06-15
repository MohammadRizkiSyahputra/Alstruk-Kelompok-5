#pragma once
#include <iostream>
using namespace std;

struct AntrianCS {
    string idNasabah;
    string namaNasabah;
    string tujuan;
    string kcp;
    string jam;
    string queueNumber;
    int csTable;
    AntrianCS* next;
};

struct QueueCS {
    int maks = 100;
    AntrianCS* head = nullptr;
    AntrianCS* tail = nullptr;
    int count = 0;

    void enqueue(const AntrianCS& data) {
        if (count >= maks) {
            cout << "Antrian sudah penuh" << endl;
            return;
        }
        AntrianCS* nodeBaru = new AntrianCS(data);
        nodeBaru->next = nullptr;
        if (head == nullptr) {
            head = tail = nodeBaru;
        } else {
            tail->next = nodeBaru;
            tail = nodeBaru;
        }
        count++;
    }



    void dequeue() {
        if (head == nullptr) {
            cout << "Antrian kosong" << endl;
            return;
        }
        AntrianCS* del = head;
        head = head->next;
        delete del;
        count--;
        if (head == nullptr) tail = nullptr;
    }

    void tampil() {
        AntrianCS* bantu = head;
        int no = 1;
        while (bantu != nullptr) {
            cout << no << ". " << bantu->namaNasabah << " | " << bantu->tujuan
                 << " | " << bantu->kcp << " | " << bantu->jam
                 << " | No Antrian: " << bantu->queueNumber
                 << " | CS Table: " << bantu->csTable << endl;
            bantu = bantu->next;
            no++;
        }
        if (count == 0) cout << "Belum ada antrian." << endl;
    }

    AntrianCS* findById(const string& idNasabah) {
        AntrianCS* bantu = head;
        while (bantu != nullptr) {
            if (bantu->idNasabah == idNasabah) return bantu;
            bantu = bantu->next;
        }
        return nullptr;
    }

    AntrianCS* getFront() {
        return head;
    }
};

extern QueueCS queueCS1, queueCS2, queueCS3;

void manageAntrianCS() {
    while (true) {
        cout << "\n=== Manage Antrian Layanan CS ===\n";
        cout << "1. Antrian CS Meja 1\n2. Antrian CS Meja 2\n3. Antrian CS Meja 3\n4. Kembali\nPilih: ";
        int pilih; cin >> pilih;
        if (pilih == 4) return;
        QueueCS* queue = nullptr;
        if (pilih == 1) queue = &queueCS1;
        else if (pilih == 2) queue = &queueCS2;
        else if (pilih == 3) queue = &queueCS3;
        else { cout << "Pilihan tidak valid.\n"; continue; }

        cout << "\nDaftar Antrian:\n";
        queue->tampil();
        cout << "1. Panggil/Next Antrian\n2. Kembali\nPilih: ";
        int aksi; cin >> aksi;
        if (aksi == 1) {
            queue->dequeue();
            cout << "Antrian berikutnya dipanggil.\n";
        }
    }
}