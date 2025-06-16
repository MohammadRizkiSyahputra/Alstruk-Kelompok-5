#pragma once
#include <iostream>
#include "../model/Akun.h"
#include <algorithm>
using namespace std;

class Hash{        
    public: 
        struct Node{
            string username{};
            string pin{};
            string nik{};
            string IdNasabah{};
            Node* next{};

            Node(string username, string pin, string nik, string IdNasabah){
                this->username = username;
                this->nik = nik;
                this->pin = pin;
                this->IdNasabah = IdNasabah;
            }   
        };

        static int const TABLE_SIZE = 10;
        Node* hashTable[TABLE_SIZE]{};

        int hashFunction(string username){
            int usernameASCII{};
            for(int i{}; i < username.length(); i++){
                usernameASCII += username[i];
            }
            return usernameASCII % 10;
        }

        int getTableSize() {
        return TABLE_SIZE;
        }

        Node** getTable() {
        return hashTable;
        }
        
        void insertHash(string username, string pin, string nik, string IdNasabah){
            int hashCode = hashFunction(username);
            Node* newNode = new Node(username, pin, nik, IdNasabah);
            Node* travel = hashTable[hashCode];

            if(hashTable[hashCode] == nullptr){
                hashTable[hashCode] = newNode;
            }else{
                travel = hashTable[hashCode];
                while(travel->next != nullptr){
                    travel = travel->next;
                }
                travel->next = newNode;
            }
        }

        void insertAkun(Akun akun) {
            insertHash(akun.username, akun.pin, akun.nik, akun.IdNasabah);
        }

        // Cek Login
        bool isNodeFound(string username, string pin){
            int hashCode = hashFunction(username);
            Node* travel = hashTable[hashCode];
            while(travel != nullptr){
                if(username == travel->username && pin == travel->pin){
                    return true;
                }
                travel = travel->next;
            }
            return false;
        }

        // Cek username dah ada?
        bool isUsernameExist(string username){
            int hashCode = hashFunction(username);
            Node* travel = hashTable[hashCode];
            while(travel != nullptr){
                if(username == travel->username){
                    return true;
                }
                travel = travel->next;
            }
            return false;
        }

        // Cek PIN 
        bool isValidPin(string pin) {
            return pin.length() == 6 && all_of(pin.begin(), pin.end(), ::isdigit);
        }

        bool isNIKExist(string nik) {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            Node* travel = hashTable[i];
            while (travel != nullptr) {
                if (travel->nik == nik) {
                    return true;
                }
                travel = travel->next;
            }
        }
        return false;
    }

        void printHashTable() {
            for (int i = 0; i < TABLE_SIZE; ++i) {
                Node* travel = hashTable[i];
                cout << "Index " << i << ": ";
                while (travel != nullptr) {
                    cout << "{" 
                        << "Username: " << travel->username 
                        << ", PIN: " << travel->pin 
                        << ", NIK: " << travel->nik 
                        << ", ID Nasabah: " << travel->IdNasabah 
                        << "} -> ";
                    travel = travel->next;
                }
                cout << "nullptr" << endl;
            }
        } 

        void printAllAkun() {
        for (int i = 0; i < TABLE_SIZE; ++i) {
        Node* travel = hashTable[i];
        while (travel != nullptr) {
            if (travel->username != "admin") {
                cout << "Username   : " << travel->username << endl;
                cout << "PIN        : " << string(travel->pin.length(), '*') << endl;
                cout << "NIK        : " << travel->nik << endl;
                cout << "ID Nasabah : " << travel->IdNasabah << endl;
                cout << "--------------------------" << endl;
            }
            travel = travel->next;
            }
        }
    }   
        
        // Username konvert ke IDNasabah
        string getIdNasabahByUsername(const string& username) {
            int hashCode = hashFunction(username);
            Node* travel = hashTable[hashCode];
            while (travel != nullptr) {
                if (travel->username == username) {
                    return travel->IdNasabah;
                }
                travel = travel->next;
            }
            return ""; 
        }
};