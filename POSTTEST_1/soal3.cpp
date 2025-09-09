#include <iostream>
#include <string>
using namespace std;


/*maksud dari singkatan
i_T = index Tertinggi
*/

struct Mahasiswa {
    string nama;
    string nim;
    float ipk;
};

int main() {
    // Mahasiswa mhs[5]; // <<<< kalo mau input manual pakai yang ini
    Mahasiswa mhs[5] = {
        {"faiz", "031", 3.67},
        {"fathur", "216", 3.97},
        {"zeydan", "163", 3.65},
        {"amin", "902", 3.62},
        {"bashir", "534", 3.64},
    };
    
    // untuk menginput data mahasiswa secara manual jangan lupa pakai yang dibawah ini 
    // cout << "Masukkan data 5 mahasiswa:" << endl;
    // for(int i = 0; i < 5; i++) {
    //     cout << "\nMahasiswa Ke-" << i+1 << endl;
    //     cout << "Nama: ";
    //     cin.ignore(1, '\n');
    //     getline(cin, mhs[i].nama);
    //     cout << "NIM: ";
    //     getline(cin, mhs[i].nim);
    //     cout << "IPK: ";
    //     cin >> mhs[i].ipk;
    // }
    
    cout << "\nData Mahasiswa:" << endl;
    cout << "----------------------------------------" << endl;
    for(int i = 0; i < 5; i++) {
        cout << "Mahasiswa Ke-" << i+1 << endl;
        cout << "Nama: " << mhs[i].nama << endl;
        cout << "NIM: " << mhs[i].nim << endl;
        cout << "IPK: " << mhs[i].ipk << endl;
        cout << "----------------------------------------" << endl;
    }
    
    int i_T = 0;
    for(int i = 1; i < 5; i++) {
        if(mhs[i].ipk > mhs[i_T].ipk) {
            i_T = i;
        }
    }
    
    cout << "\nMahasiswa dengan IPK tertinggi:" << endl;
    cout << "Nama: " << mhs[i_T].nama << endl;
    cout << "NIM: " << mhs[i_T].nim << endl;
    cout << "IPK: " << mhs[i_T].ipk << endl;
    
    return 0;
}