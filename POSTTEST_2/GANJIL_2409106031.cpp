#include <iostream>
using namespace std;

struct Identitas {
    string nama, nim;
}idn;


struct Data {
    string nama_item;
    int jumlah;
    string tipe;
};

struct Node {
    Data data;
    Node *next;
};

void tampilkan_menu() {
    const int menu_width = 40;
    const string header_title = "GAME INVENTORY MANAGEMENT";
    const string header_id = idn.nama + " - " + idn.nim;
    
    int spasi_title = (menu_width - header_title.length()) / 2;
    int spasi_id = (menu_width - header_id.length()) / 2;

    cout << "\n" << string(menu_width, '=') << "\n";
    cout << "|" << string(spasi_title, ' ') << header_title << string(menu_width - header_title.length() - spasi_title - 2, ' ') << "|\n";
    cout << "|" << string(spasi_id, ' ') << header_id << string(menu_width - header_id.length() - spasi_id - 2, ' ') << "|\n";
    cout << string(menu_width, '=') << "\n";
    cout << "| 1. Tambah Item Baru" << string(menu_width - 22, ' ') << "|\n";
    cout << "| 2. Sisipkan Item" << string(menu_width - 19, ' ') << "|\n";
    cout << "| 3. Hapus Item Terakhir" << string(menu_width - 25, ' ') << "|\n";
    cout << "| 4. Gunakan Item" << string(menu_width - 18, ' ') << "|\n";
    cout << "| 5. Tampilkan Inventory" << string(menu_width - 25, ' ') << "|\n";
    cout << "| 0. Keluar" << string(menu_width - 12, ' ') << "|\n";
    cout << string(menu_width, '=') << "\n";
    cout << "Pilih opsi: ";
};

void add_item(Node *&head);
void place_item(Node *&head);
void del_last(Node *&head);
void use_item(Node *&head);
void show_invent(Node *head);

int main() {
    cout << "Masukkan Nama: ";
    getline(cin, idn.nama);
    cout << "Masukkan NIM: ";
    getline(cin, idn.nim);

    Node *head = nullptr;
    bool loop = true;
    int input;

    while (loop == true) {
        tampilkan_menu();
        cin >> input;
        
        switch (input) {
        case 1:
            add_item(head);
            break;
        case 2:
            place_item(head);
            break;
        case 3:
            del_last(head);
            break;
        case 4:
            use_item(head);
            break;
        case 5:
            show_invent(head);
            break;
        case 0:
            loop = false;
            cout << "\nTerima kasih telah menggunakan program ini!\n";
            break;
        default:
            cout << "\nTerjadi Kesalahan. Pilih opsi yang valid!\n";
            break;
        }   
    }

    while (head != nullptr) {
        Node *temp = head;
        head = head->next;
        delete temp;
    }
    return 0;
}

void add_item(Node *&head) {
    Node *node_baru = new Node;

    cout << "\nMasukkan nama item: ";
    cin.ignore();
    getline(cin, node_baru->data.nama_item);
    
    cout << "Masukkan tipe item (Weapon/Utility/Armor): ";
    getline(cin, node_baru->data.tipe);

    node_baru->data.jumlah = 1;
    node_baru->next = nullptr;

    if (head == nullptr) {
        head = node_baru;

    } else {
        Node *temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = node_baru;
    }
    cout << "Item berhasil ditambahkan!\n";
}

void place_item(Node *&head) {
    Node *node_baru = new Node;
    cout << "\nMasukkan nama item: ";
    cin.ignore();
    getline(cin, node_baru->data.nama_item);

    cout << "Masukkan tipe item (Weapon/Utility/Armor): ";
    getline(cin, node_baru->data.tipe);
    
    node_baru->data.jumlah = 31;
    node_baru->next = nullptr;

    int pos = 2;
    if (pos <= 1 || head == nullptr) {
        node_baru->next = head;
        head = node_baru;

    } else {
        Node *temp = head;
        int cur_pos = 1;
        while (cur_pos < pos - 1 && temp->next != nullptr) {
            temp = temp->next;
            cur_pos++;
        }

        node_baru->next = temp->next;
        temp->next = node_baru;
    }
    cout << "Item berhasil disisipkan pada posisi " << pos << "!\n";
}

void del_last(Node *&head) {
    if (head == nullptr) {
        cout << "\nInventory kosong!\n";
        return;
    }

    if (head->next == nullptr) {
        delete head;
        head = nullptr;
        cout << "\nItem terakhir dihapus!\n";
        return;
    }

    Node *temp = head;
    while (temp->next->next != nullptr) {
        temp = temp->next;
    }

    Node *cur = temp->next;
    temp->next = nullptr;
    delete cur;
    cout << "\nItem terakhir dihapus!\n";
}

void use_item(Node *&head) {
    if (head == nullptr) {
        cout << "\nInventory kosong!\n";
        return;
    }
    
    string nama;
    cout << "\nMasukkan nama item yang ingin digunakan: ";
    cin.ignore();
    getline(cin, nama);

    Node *current = head;
    Node *prev = nullptr;
    while (current != nullptr && current->data.nama_item != nama) {
        prev = current;
        current = current->next;
    }

    if (current == nullptr) {
        cout << "Item tidak ditemukan!\n";
        return;
    }

    current->data.jumlah--;
    cout << "Item " << nama << " digunakan. Jumlah tersisa: " << current->data.jumlah << "\n";

    if (current->data.jumlah == 0) {
        if (prev == nullptr) {
            head = current->next;
        } else {
            prev->next = current->next;
        }
        delete current;
        cout << "Item " << nama << " habis dan dihapus dari inventory!\n";
    }
}

void show_invent(Node *head) {
    if (head == nullptr) {
        cout << "\nInventory kosong!\n";
        return;
    }

    // Tabel
    const int nama_width = 20;
    const int jumlah_width = 8;
    const int tipe_width = 10;

    cout << "\nIsi Inventory:\n";
    cout << string(nama_width + jumlah_width + tipe_width + 7, '-') << "\n";
    cout << "| " << "Nama Item" << string(nama_width - 9, ' ')
         << "| Jumlah" << string(jumlah_width - 6, ' ')
         << "| Tipe" << string(tipe_width - 4, ' ') << "|\n";
    cout << string(nama_width + jumlah_width + tipe_width + 7, '-') << "\n";

    Node *temp = head;
    while (temp != nullptr) {
        string nama = temp->data.nama_item;
        string jumlah_str = to_string(temp->data.jumlah);
        string tipe = temp->data.tipe;

        if (nama.length() > nama_width - 2) {
            nama = nama.substr(0, nama_width - 5) + "...";
        }
        if (tipe.length() > tipe_width - 2) {
            tipe = tipe.substr(0, tipe_width - 5) + "...";
        }

        cout << "| " << nama << string(nama_width - nama.length(), ' ')
             << "| " << jumlah_str << string(jumlah_width - jumlah_str.length(), ' ')
             << "| " << tipe << string(tipe_width - tipe.length(), ' ') << "|\n";
        temp = temp->next;
    }
    cout << string(nama_width + jumlah_width + tipe_width + 7, '-') << "\n";
}