#include <iostream>
#include <limits>

using namespace std;

// Struct yang dibentuk sebagai data di node
struct Identitas
{
    string nama;
    string gender;
    int umur;
};
struct tanggalLahir
{
    int hari,
        bulan,
        tahun;
};
struct Data
{
    int sid;
    Identitas bio;
    tanggalLahir lahir;
    string kelas;
    string position;
};

// Node single linked list, hanya memiliki data dan pointer node next;
struct Node
{
    Data data;
    Node *next;
};

// Prototype

// Prototipe digunakan untuk memberitahu compiler tentang fungsi sebelum fungsi tersebut dipanggil.
// Ini sangat penting jika kita ingin memanggil fungsi yang didefinisikan setelah fungsi lain,
// atau jika urutan pemanggilan tidak linier (misal, main memanggil function2, yang memanggil function1).
// Tanpa prototipe, compiler tidak akan mengenali fungsi yang belum didefinisikan di awal,
// sehingga bisa menyebabkan error saat kompilasi.

// Prototipe juga membantu dalam program besar yang memiliki banyak file,
// di mana satu fungsi bisa dipanggil di file yang berbeda.

// Prosedur CRUD
void Create(Node *&head, int &jumlahRoster, string menu);
void Read(Node *head);
void Update(Node *&head);
void Delete(Node *&head, int &jumlahRoster, string menu);

// Prosedur Manipulasi Single Linked List
void CF(Node *&head, int &jumlahRoster); // Tambah Awal
void CL(Node *&head, int &jumlahRoster); // Tambah Akhir
void CP(Node *&head, int &jumlahRoster); // Tambah Urutan Tertentu
void DF(Node *&head, int &jumlahRoster); // Hapus Awal
void DL(Node *&head, int &jumlahRoster); // Hapus akhir
void DP(Node *&head, int &jumlahRoster); // Hapus urutan Tertentu

// Input dan Error handling untuk input
void inputPilihan(string namaPilihan, const string array[], int panjang, string &data);
Node inputData();
void errorInput(int &input);

int main()
{
    int jumlahRoster = 0, input; // Variabel yang menyimpan panjang/jumlah linked list dan input dari user
    bool loop = true;            // variabel untuk mengatur perulangan
    Node *head = nullptr;        // head yang merupakan awalan dari linked list

    string menuUtama = "\n == Data Roster Karakter ==\n 1. Tambah Data\n 2. Lihat Data\n 3. Ubah Data\n 4. Hapus data\n 5. Keluar\n Masukan pilihan : ";
    string menuTambah = "\n == Tambah Data Roster Karakter ==\n 1. Tambah di awal\n 2. Tambah di akhir\n 3. Tambah urutan tertentu\n Masukan pilihan : ";
    string menuHapus = "\n == Hapus Data Roster Karakter ==\n 1. Hapus urutan pertama\n 2. Hapus urutan akhir\n 3. Hapus urutan tertentu\n Masukan pilihan : ";
    while (loop == true)
    {
        cout << menuUtama;
        cin >> input;
        switch (input)
        {
        case 1:
            Create(head, jumlahRoster, menuTambah);
            break;

        case 2:
            Read(head);
            break;

        case 3:
            Update(head);
            break;

        case 4:
            Delete(head, jumlahRoster, menuHapus);
            break;

        case 5:
            loop = false;
            break;

        default:
            cout << " \n Terjadi Kesalahan\n";
            break;
        }
    }

    return 0;
}

void Create(Node *&head, int &jumlahRoster, string menu)
{
    int input;
    bool loop = true;
    while (loop == true)
    {
        cout << menu;
        cin >> input;
        switch (input)
        {
        case 1:
            CF(head, jumlahRoster);
            loop = false;
            break;

        case 2:
            CL(head, jumlahRoster);
            loop = false;
            break;

        case 3:
            CP(head, jumlahRoster);
            loop = false;
            break;
        case 0:
            loop = false;
        default:
            cout << "Masukan antara 1-3 (0 untuk kembali)!";
            break;
        }
    }
}

void CF(Node *&head, int &jumlahRoster)
{
    Node *nodeBaru = new Node;
    nodeBaru->data = inputData().data;

    nodeBaru->next = head;           // Dalam menambahkan di awal, node baru akan mengambil alamat di heah, menghubungkan Node baru ke linked list
    head = nodeBaru;                 // Lalu head akan menjadi alamat dari Node baru itu, karna telah di tambah di awal
    jumlahRoster = jumlahRoster + 1; // Counter jumlah data bertambah
}

void CL(Node *&head, int &jumlahRoster)
{
    if (head == nullptr) // Error handling jika linked list masih kosong beralih ke addFirst
    {
        CF(head, jumlahRoster);
        return;
    }

    Node *nodeBaru = new Node;
    nodeBaru->data = inputData().data;
    nodeBaru->next = nullptr; // Alamat next Node baru kosong karna akan ditaruh di akhir

    // Jika tidak kosong maka akan traverse ke ujung node dengan perulangan hingga alamat selanjutnya kosong
    Node *temp = head;
    while (temp->next != nullptr)
    {
        temp = temp->next;
    }
    temp->next = nodeBaru;           // alamat node baru di tambahkan ke alamt node terujung yang kosong tadi, menghubungkannya
    jumlahRoster = jumlahRoster + 1; // Counter naik
}

// Menambahkan di urutan/posisi tertentu
void CP(Node *&head, int &jumlahRoster)
{
    int input;
    if (head == nullptr) // Jika linked list masih kosong, hanya ada satu pilihan urutan
    {
        cout << "Urutan ke "
             << "(hanya 1) : "; // Pesan yang ditampilkan meminta input urutan pertama
    }
    else // Jika linked list sudah ada node, tampilkan pilihan urutan 1 sampai jumlahRoster + 1
    {
        cout << "Urutan ke "
             << "(1-" << jumlahRoster + 1 << ") : "; // Pesan yang menampilkan rentang urutan yang valid
    }
    cin >> input;                               // Menerima input urutan dari user
    if (0 < input and input < jumlahRoster + 2) // Memastikan input berada dalam batas yang valid
    {

        if (input == 1) // Jika input urutan adalah 1, berarti node baru akan menjadi head
        {
            CF(head, jumlahRoster);
            return;
        }
        else if (input == jumlahRoster + 1)
        {
            CL(head, jumlahRoster);
            return;
        }

        Node *nodeBaru = new Node;         // Buat node baru untuk disisipkan
        nodeBaru->data = inputData().data; // Isi data node baru dengan data yang dimasukkan user
        Node *temp = head;                 // Mulai dari node head sebagai node sementara

        // Jika urutan bukan 1, cari posisi yang sesuai dalam list
        for (int x = 0; x < input - 2; x++) // Loop untuk mencapai node sebelum posisi yang diminta
        {
            temp = temp->next; // Pindah ke node berikutnya
        }
        nodeBaru->next = temp->next;     // Node baru menunjuk ke node setelahnya (sebelum node di urutan input)
        temp->next = nodeBaru;           // Node sebelumnya sekarang menunjuk ke node baru
        jumlahRoster = jumlahRoster + 1; // Tambah jumlah roster karena node baru ditambahkan
    }
    else // Jika input urutan tidak valid
    {
        cout << "\n Tidak ada urutan " << input << "! \n"; // Tampilkan pesan error jika urutan tidak valid
        return;                                            // Kembalikan tanpa melakukan apa-apa
    }
}

void Read(Node *head)
{
    if (head == nullptr) // Jika linked list kosong, tampilkan pesan bahwa tidak ada data
    {
        cout << ">> LinkedList masih kosong <<" << endl;
        return; // Kembalikan tanpa melakukan apapun
    }

    int no = 1;                       // Variabel untuk menghitung urutan data
    cout << " \n=Roster Karakter=\n"; // Header untuk daftar karakter
    while (head != nullptr)           // Loop melalui seluruh node dalam linked list untuk menampilkan data
    {
        cout << no
             << ". SID       : " << head->data.sid << endl                                                                           // Menampilkan SID dari node saat ini
             << "   Nama      : " << head->data.bio.nama << endl                                                                     // Menampilkan nama karakter
             << "   Gender    : " << head->data.bio.gender << endl                                                                   // Menampilkan gender karakter
             << "   Umur      : " << head->data.bio.umur << endl                                                                     // Menampilkan umur karakter
             << "   Lahir     : " << head->data.lahir.hari << "-" << head->data.lahir.bulan << "-" << head->data.lahir.tahun << endl // Menampilkan tanggal lahir
             << "   kelass     : " << head->data.kelas << endl                                                                         // Menampilkan kelas karakter
             << "   Posisi    : " << head->data.position << endl;                                                                    // Menampilkan posisi karakter
        no++;                                                                                                                        // Increment nomor urutan untuk karakter berikutnya
        head = head->next;                                                                                                           // Pindah ke node berikutnya
    }
    cout << endl;
}

void Update(Node *&head)
{
    if (head == nullptr) // Jika linked list kosong, tidak ada yang bisa di-update
    {
        cout << "\n >> LinkedList masih kosong << \n"
             << endl;
        return;
    }
    string ubah;
    cout << "Masukan nama karakter yang akan diubah : "; // Meminta user memasukkan nama karakter yang ingin diubah
    cin >> ubah;
    Node *temp = head;      // Mulai dari head untuk mencari node dengan nama yang sesuai
    while (temp != nullptr) // Loop melalui linked list
    {
        if (temp->data.bio.nama == ubah) // Jika nama yang dimasukkan cocok dengan nama pada node saat ini
        {
            cout << "Masukan data yang baru : "; // Meminta user memasukkan data baru
            temp->data = inputData().data;       // Perbarui data node dengan input baru
            cout << "Data berhasil diubah" << endl;
            return;
        }
        temp = temp->next; // Lanjutkan ke node berikutnya
    }
    cout << "Data tidak ditemukan" << endl; // Jika nama tidak ditemukan dalam linked list
}

void Delete(Node *&head, int &jumlahRoster, string menu)
{
    if (head == nullptr) // Jika linked list kosong, tidak ada yang bisa dihapus
    {
        cout << "\n >> LinkedList masih kosong << \n"
             << endl;
        return;
    }

    int input;
    bool loop = true;
    while (loop == true) // Loop yang terus berjalan hingga pilihan valid dipilih
    {
        cout << menu;  // Tampilkan menu untuk memilih metode penghapusan
        cin >> input;  // Menerima input pilihan user
        switch (input) // Pilih berdasarkan input user
        {
        case 1:
            DF(head, jumlahRoster); // Hapus node pertama dalam linked list
            loop = false;           // Keluar dari loop setelah operasi berhasil
            break;

        case 2:
            DL(head, jumlahRoster); // Hapus node terakhir dalam linked list
            loop = false;           // Keluar dari loop setelah operasi berhasil
            break;

        case 3:
            DP(head, jumlahRoster); // Hapus node di posisi tertentu dalam linked list
            loop = false;           // Keluar dari loop setelah operasi berhasil
            break;

        case 0:
            loop = false; // Kembali ke menu sebelumnya tanpa melakukan penghapusan
            break;

        default:
            cout << "Masukan antara 1-3 (0 untuk kembali)!"; // Pesan jika input di luar rentang yang valid
            break;
        }
    }
}

void DF(Node *&head, int &jumlahRoster)
{
    Node *cur = head;                // Menyimpan alamat head sebelum di hapus hubungan
    head = head->next;               // Menghapus hubungan node pertama dengan menggeser head ke node berikutnya
    delete cur;                      // Menghapus data di alamat node sebelumnya
    jumlahRoster = jumlahRoster - 1; // Mengurangi jumlah roster karena satu node telah dihapus
    cout << "\n Telah dihapus! \n";  // Memberi tahu user bahwa node telah dihapus
}

void DL(Node *&head, int &jumlahRoster)
{
    if (head->next == nullptr) // Jika hanya ada satu node di linked list beralih ke deletefirst
    {
        DF(head, jumlahRoster);
        return; // Kembali dari fungsi
    }

    Node *temp = head;                  // Node sementara untuk traversing
    while (temp->next->next != nullptr) // Mencari node sebelum node terakhir
    {
        temp = temp->next; // Pindah ke node berikutnya
    }
    Node *cur = temp->next;          // Menyimpan alamat node sebelum di hapus hubungan
    temp->next = nullptr;            // Menghapus node terakhir dengan mengatur next menjadi nullptr
    delete cur;                      // Menghapus data di alamat node sebelumnya
    jumlahRoster = jumlahRoster - 1; // Mengurangi jumlah roster
    cout << "\n Telah dihapus! \n";  // Memberi tahu user bahwa node telah dihapus
}

void DP(Node *&head, int &jumlahRoster)
{
    int input;
    Read(head); // Menampilkan semua karakter sebelum menghapus
    cout << "Hapus urutan ke "
         << "(1-" << jumlahRoster << ") : ";    // Meminta user untuk memasukkan urutan yang akan dihapus
    cin >> input;                               // Menerima input dari user
    if (0 < input and input < jumlahRoster + 1) // Memastikan input berada dalam rentang yang valid
    {
        if (input == 1) // Jika input adalah 1, hapus node pertama
        {
            DF(head, jumlahRoster);
            return;
        }
        else if (input == jumlahRoster + 1)
        {
            DL(head, jumlahRoster);
            return;
        }

        Node *temp = head, *cur = head;     // Pointer Node sementara untuk traversing dan Pointer Node yang ingin dihapus
        for (int x = 0; x < input - 2; x++) // Mencari node sebelum posisi yang ingin dihapus
        {
            temp = temp->next; // Pindah ke node berikutnya
        }
        cur = temp->next;       // Node yang ingin dihapus
        temp->next = cur->next; // Menghubungkan node sebelumnya ke node setelah node yang ingin dihapus
        delete cur;
        jumlahRoster = jumlahRoster - 1; // Mengurangi jumlah roster
        cout << "\n Telah dihapus! \n";  // Memberi tahu user bahwa node telah dihapus
    }
    else // Jika input tidak valid
    {
        cout << "\nTidak ada urutan " << input << "!\n"; // Pesan error jika urutan tidak ada
        return;                                          // Kembali dari fungsi
    }
}

void inputPilihan(string namaPilihan, const string array[], int panjang, string &data)
{
    int input = 1;
    cout << "\n  " << namaPilihan << endl;
    for (int i = 0; i < panjang; i++)
    {
        cout << "   " << i + 1 << ". " << array[i];
        if (i < panjang - 1)
        {
            cout << endl;
        }
    }

    do
    {
        cout << " \nMasukan angka 1-" << panjang << "! \n Input : ";
        cin >> input;
        errorInput(input);
    } while (input <= 0 or input > panjang);
    data = array[input - 1];
}

Node inputData()
{
    Node *dataBaru = new Node;
    int input;
    cout << " \nTambah Data Karakter\n "
         << " SID     : ";
    cin >> dataBaru->data.sid;
    errorInput(dataBaru->data.sid);

    cout << "  Nama    : ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Membersihkan input buffer dari cin sebelumnya
    getline(cin, dataBaru->data.bio.nama);

    const string genders[] = {"Laki-laki", "Perempuan", "Tidak Terdefinisi"};
    inputPilihan("Gender", genders, 3, dataBaru->data.bio.gender);

    cout << "\n  Umur  :  ";
    cin >> dataBaru->data.bio.umur;
    errorInput(dataBaru->data.bio.umur);

    cout << "  Tanggal lahir\n"
         << "   Hari (angka) : ";
    cin >> dataBaru->data.lahir.hari;
    errorInput(dataBaru->data.lahir.hari);
    cout << "   Bulan : ";
    cin >> dataBaru->data.lahir.bulan;
    errorInput(dataBaru->data.lahir.bulan);
    cout << "   Tahun : ";
    cin >> dataBaru->data.lahir.tahun;
    errorInput(dataBaru->data.lahir.tahun);

    const string kelasses[] = {"Saber", "Lancer", "Archer", "Caster", "Rider", "Assassin", "Extra"};
    inputPilihan("kelass", kelasses, 7, dataBaru->data.kelas);

    const string positions[] = {"Front", "Back"};
    inputPilihan("Posisi", positions, 2, dataBaru->data.position);

    cout << " \nBerhasil!\n ";
    return *dataBaru;
}

void errorInput(int &input)
{
    while (true)
    {
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Mohon masukan angka untuk input di atas!\n input :  ";
            cin >> input;
        }
        else
        {
            break;
        }
    }
}