#pragma once
#include <iostream>
#include "../controller/transaksi_controller.h"
#include "../datastructure/tree.h"
#include "../utils/utility.h"
#include "../model/Nasabah.h"

void transfer(Nasabah* nasabahAkun, BinaryTreeNasabah* tree) {
    if (!tree || !nasabahAkun) {
        std::cerr << "[ERROR] Data nasabah atau tree tidak valid.\n";
        return;
    }

    string label, noRek, tanggal;
    double nominal; 
    Nasabah* nasabahTujuan = nullptr;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    label = getSafeLine("Masukkan label transaksi: ");

    while (true) {
        noRek = getSafeLine("Masukkan nomor rekening tujuan: ");
        if (noRek == nasabahAkun->NoRekening) {
            std::cout << "Anda tidak bisa transfer ke rekening sendiri. Silahkan coba lagi.\n";
            continue;
        }
        
        nasabahTujuan = tree->findByRekening(noRek);
        if (nasabahTujuan) {
            break;
        } else {
            std::cout << "Tidak ada nasabah dengan nomor rekening tersebut. Silahkan coba lagi.\n";
        }
    }

    std::cout << "Masukkan nominal transfer: Rp";
    std::cin >> nominal;

    // VALIDASI SALDO DITAMBAHKAN
    if (nasabahAkun->saldo < nominal) {
        std::cout << "\nTransaksi Gagal. Saldo Anda tidak mencukupi." << std::endl;
        std::cout << "Saldo Anda saat ini: Rp" << fixed << setprecision(2) << nasabahAkun->saldo << std::endl;
        return; // Hentikan proses jika saldo kurang
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    while (true) {
        tanggal = getSafeLine("Masukkan tanggal (DD-MM-YYYY): ");
        if (isValidDateFormat(tanggal)) {
            break;
        } else {
            std::cout << "Format tanggal tidak valid.\n";
        }
    }

    // UPDATE SALDO DITAMBAHKAN 
    nasabahAkun->saldo -= nominal;      // Kurangi saldo pengirim
    nasabahTujuan->saldo += nominal;    // Tambah saldo tujuan

    // Panggil fungsi untuk mencatat transaksi di kedua nasabah
    tambahTransaksi(nasabahAkun, nasabahTujuan, label, nominal, tanggal);

    // --- Konfirmasi Berhasil ---
    std::cout << "\n--- Transfer Berhasil! ---" << std::endl;
    std::cout << "Anda telah mentransfer Rp" << fixed << setprecision(2) << nominal << " ke rekening " << nasabahTujuan->NoRekening << std::endl;
    std::cout << "Sisa saldo Anda: Rp" << nasabahAkun->saldo << std::endl;
    std::cout << "--------------------------" << std::endl;
    std::cout << "Tekan Enter untuk melihat bukti transaksi...";
    std::cin.get();

    // Tampilkan detail transaksi terakhir yang dikirim
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


