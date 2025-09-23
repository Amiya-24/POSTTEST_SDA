#include <iostream>
#include <iomanip>
#include <string>
#include <limits>

using namespace std;

// -- 1. MODEL DATA & STRUKTUR DATA --
struct Identitas {
    string nama, nim;
};

struct Data {
    string nama_item;
    int jumlah;
    string tipe;
};

struct Node {
    Data data;
    Node *next;
    Node *prev;
};

struct List_Data {
    Node *head = nullptr;
    Node *tail = nullptr;
};

enum Halaman { MAIN_PAGE, ADD_ITEM, PLACE_ITEM, DEL_LAST, USE_ITEM, SHOW_INVENT, SHOW_INVENT_REV, SHOW_INVENT_DETAIL };

// -- 2. STATE APLIKASI
struct AppState {
    Halaman active_page = MAIN_PAGE;
    List_Data inventory;
    string info = "";
    Identitas idn;
    std::string selected_item = "";
};

// -- 3. KOMPONEN VIEW --
namespace View {
    void clearScreen() {
        #ifdef _WIN32
                system("cls");
        #else
                system("clear");
        #endif
    }

    void render_Header(const AppState &state) {
        cout << "========================================\n";
        cout << "       GAME INVENTORY MANAGEMENT\n";
        cout << "========================================\n";
        cout << "Nama: " << state.idn.nama << "\nNim: " << state.idn.nim << "\n";
        cout << "========================================\n";

    }

    void render_Info_Message(const AppState &state) {
        if (!state.info.empty()) {
            cout << "[INFO] " << state.info << "\n\n";
        }
    }

    void render_Table_Header() {
        std::cout << "Inventory:\n";
        std::cout << std::left;
        std::cout << std::setw(22) << "Nama Item" << "\n";
        std::cout << std::string(40, '-') << "\n";
    }

    void render_Table_Body(const AppState &state) {
        if (state.inventory.head == nullptr) {
            std::cout << "Inventory kosong!\n";

        } else {
            Node *current = state.inventory.head;
            while (current != nullptr) {
                cout << setw(22) << current->data.nama_item << "\n";
                current = current->next;
            }
        }
    }

    void render_Table_Body_Reverse(const AppState &state) {
        if (state.inventory.tail == nullptr) {
            std::cout << "Inventory kosong!\n";

        } else {
            Node *current = state.inventory.tail;
            while (current != nullptr) {
                cout << setw(22) << current->data.nama_item << "\n";
                current = current->prev;
            }
        }
    }

    void render_Table_Body_Detail(const AppState &state) {
        Node *current = state.inventory.head;
        while (current != nullptr && current->data.nama_item != state.selected_item) {
            current = current->next;
        }

        if (current == nullptr) {
            cout << "Item tidak ditemukan!\n";

        } else {
            cout << "--- Detail Item ---\n";
            cout << "Nama Item : " << current->data.nama_item << "\n";
            cout << "Jumlah    : " << current->data.jumlah << "\n";
            cout << "Tipe      : " << current->data.tipe << "\n";
        }
        cout << "\n[0] Kembali ke Menu Utama\n";
        cout << "Pilihan: ";
    }

    void render_Main_Page() {
        cout << "\n--- Menu Utama ---\n";
        cout << "[1] Tambah Item Baru\n";
        cout << "[2] Sisipkan Item\n";
        cout << "[3] Hapus Item Terakhir\n";
        cout << "[4] Gunakan Item\n";
        cout << "[5] Tampilkan Inventory\n";
        cout << "[0] Keluar\n";
        cout << "Pilihan: ";
    }

    void render_Dashboard(const AppState &state) {
        render_Table_Header();
        render_Table_Body(state);
        render_Main_Page();
    }

    void render_Add_Item() {
        cout << "--- Tambah Item Baru ---\n";
        cout << "Masukkan Nama Item: ";
    }

    void render_Place_Item() {
        cout << "--- Sisipkan Item ---\n";
        cout << "Masukkan Nama Item: ";
    }

    void render_Delete_Item() {
        cout << "--- Hapus Item Terakhir ---\n";
        cout << "Tekan enter untuk menghapus item terakhir...";
    }

    void render_Use_Item() {
        cout << "--- Gunakan Item ---\n";
        cout << "Masukkan Nama Item yang akan digunakan: ";
    }

    void show_Invent(){
        cout << "\n--- Pilihan Tampilan Inventory ---\n";
        cout << "[1] Tampilkan dari Depan\n";
        cout << "[2] Tampilkan dari Belakang\n";
        cout << "[3] Tampilkan Detail Item\n";
        cout << "[0] Kembali ke Menu Utama\n";
        cout << "Pilihan: ";
    }

    void render(const AppState &state) {
        clearScreen();
        render_Header(state);
        render_Info_Message(state);

        switch (state.active_page) {
            case MAIN_PAGE:
                render_Dashboard(state);
                break;

            case ADD_ITEM:
                render_Add_Item();
                break;

            case PLACE_ITEM:
                render_Place_Item();
                break;

            case DEL_LAST:
                render_Delete_Item();
                break;

            case USE_ITEM:
                render_Use_Item();
                break;

            case SHOW_INVENT:
                render_Table_Header();
                render_Table_Body(state);
                show_Invent();
                break;

            case SHOW_INVENT_REV:
                render_Table_Header();
                render_Table_Body_Reverse(state);
                show_Invent();
                break;

            case SHOW_INVENT_DETAIL:
                render_Table_Body_Detail(state);
                break;

            default:
                break;
        }
    }
}

// -- 4. KOMPONEN USE CASE --
namespace UseCase {
    int get_item_amount(const AppState &state) {
        if (state.idn.nim.length() >= 2) {
            string last_two_digits = state.idn.nim.substr(state.idn.nim.length() - 2);
            return stoi(last_two_digits);
        }
        return 1;
    }

    int get_insert_position(const AppState &state) {
        if (!state.idn.nim.empty() && isdigit(state.idn.nim.back())) {
            return (state.idn.nim.back() - '0') + 1;
        }
        return 2;
    }

    Node *search_item(List_Data &list, const string &item_name) {
        Node *current = list.head;
        while (current != nullptr) {
            if (current->data.nama_item == item_name) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    void add_item(AppState &state) {
        string nama, tipe;
        int jumlah;

        getline(cin, nama);
        if (nama.empty() || search_item(state.inventory, nama) != nullptr) {
            state.info = "Input tidak valid atau item sudah ada!";

        } else {
            cout << "Masukkan Tipe Item (Weapon/Utility/Armor): ";
            getline(cin, tipe);
            jumlah = get_item_amount(state);

            Node *new_node = new Node;
            new_node->data.nama_item = nama;
            new_node->data.tipe = tipe;
            new_node->data.jumlah = jumlah;
            new_node->next = nullptr;
            new_node->prev = state.inventory.tail;

            if (state.inventory.head == nullptr) {
                state.inventory.head = new_node;
                state.inventory.tail = new_node;

            } else {
                state.inventory.tail->next = new_node;
                state.inventory.tail = new_node;
            }
            state.info = "Item " + nama + " berhasil ditambahkan!";
        }
        state.active_page = MAIN_PAGE;
    }

    void place_item(AppState &state) {
        string nama, tipe;
        int jumlah, position;

        getline(cin, nama);
        if (nama.empty() || search_item(state.inventory, nama) != nullptr) {
            state.info = "Input tidak valid atau item sudah ada!";

        } else {
            cout << "Masukkan Tipe Item (Weapon/Utility/Armor): ";
            getline(cin, tipe);
            jumlah = get_item_amount(state);
            position = get_insert_position(state);

            Node *new_node = new Node;
            new_node->data.nama_item = nama;
            new_node->data.tipe = tipe;
            new_node->data.jumlah = jumlah;
            new_node->next = nullptr;
            new_node->prev = nullptr;

            if (state.inventory.head == nullptr) {
                state.inventory.head = new_node;
                state.inventory.tail = new_node;

            } else if (position <= 1) {
                new_node->next = state.inventory.head;
                state.inventory.head->prev = new_node;
                state.inventory.head = new_node;

            } else {
                Node *current = state.inventory.head;
                int idx = 1;
                
                while (current->next != nullptr && idx < position - 1) {
                    current = current->next;
                    idx++;
                }
                new_node->next = current->next;
                new_node->prev = current;

                if (current->next != nullptr)
                    current->next->prev = new_node;
                current->next = new_node;

                if (new_node->next == nullptr)
                    state.inventory.tail = new_node;
            }
            state.info = "Item " + nama + " berhasil disisipkan!";
        }
        state.active_page = MAIN_PAGE;
    }

    void delete_last(AppState &state) {
        if (state.inventory.tail == nullptr) {
            state.info = "Inventory kosong!";

        } else {
            Node *to_delete = state.inventory.tail;
            string deleted_name = to_delete->data.nama_item;

            if (to_delete == state.inventory.head) {
                state.inventory.head = nullptr;
                state.inventory.tail = nullptr;

            } else {
                state.inventory.tail = to_delete->prev;
                state.inventory.tail->next = nullptr;
            }
            delete to_delete;
            state.info = "Item terakhir (" + deleted_name + ") berhasil dihapus.";
        }
        state.active_page = MAIN_PAGE;
    }

    void use_item(AppState &state) {
        string item_name;
        getline(cin, item_name);

        Node *item_node = search_item(state.inventory, item_name);
        if (item_name.empty() || item_node == nullptr || item_node->data.jumlah <= 0) {
            state.info = "Gagal! Item tidak ditemukan atau jumlah habis.";

        } else {
            item_node->data.jumlah--;
            state.info = "Item " + item_name + " berhasil digunakan.";

            if (item_node->data.jumlah == 0) {
                if (item_node == state.inventory.head) {
                    state.inventory.head = item_node->next;
                }

                if (item_node == state.inventory.tail) {
                    state.inventory.tail = item_node->prev;
                }

                if (item_node->prev != nullptr) {
                    item_node->prev->next = item_node->next;
                }

                if (item_node->next != nullptr) {
                    item_node->next->prev = item_node->prev;
                }
                delete item_node;
                state.info = " Item telah habis dan dihapus dari inventory.";
            }
        }
        state.active_page = MAIN_PAGE;
    }

    void process_Input(AppState &state, const string &input) {
        state.info = "";

        try {
            int choice = stoi(input);
            if (state.active_page == MAIN_PAGE) {
                switch (choice) {
                    case 1:
                        state.active_page = ADD_ITEM;
                        break;

                    case 2:
                        state.active_page = PLACE_ITEM;
                        break;

                    case 3:
                        state.active_page = DEL_LAST;
                        break;

                    case 4:
                        state.active_page = USE_ITEM;
                        break;

                    case 5:
                        state.active_page = SHOW_INVENT;
                        break;

                    case 6:
                        state.active_page = SHOW_INVENT_REV;
                        break;

                    case 0:
                        break;
                    
                    default:
                        state.info = "Pilihan tidak valid!";
                        break;
                }
            } else if (state.active_page == SHOW_INVENT || state.active_page == SHOW_INVENT_REV) {
                if (choice == 1) {
                    state.active_page = SHOW_INVENT;

                } else if (choice == 2) {
                    state.active_page = SHOW_INVENT_REV;

                } else if (choice == 3) {
                    cout << "Masukkan nama item yang ingin dilihat detailnya: ";
                    string nama_item;
                    getline(cin, nama_item);
                    state.selected_item = nama_item;
                    state.active_page = SHOW_INVENT_DETAIL;

                } else if (choice == 0) {
                    state.active_page = MAIN_PAGE;
                    
                } else {
                    state.info = "Pilihan tidak valid!";
                }
            } else if (state.active_page == SHOW_INVENT_DETAIL) {
                if (choice == 0) {
                    state.active_page = MAIN_PAGE;
                }
            }
        } catch (const invalid_argument &e) {
            state.info = "Input harus berupa angka!";
        }
    }
}

// -- 5. MAIN APPLICATION LOOP --
int main() {
    AppState state;
    cout << "Masukkan Nama: ";
    getline(cin, state.idn.nama);
    cout << "Masukkan NIM: ";
    getline(cin, state.idn.nim);

    string input;
    while (true) {
        View::render(state);

        if (state.active_page == MAIN_PAGE || state.active_page == SHOW_INVENT || state.active_page == SHOW_INVENT_REV) {
            getline(cin, input);

            if (state.active_page == MAIN_PAGE && input == "0")
                break;
            UseCase::process_Input(state, input);

        } else if (state.active_page == SHOW_INVENT_DETAIL) {
            getline(cin, input);
            if (input == "0") {
                state.active_page = MAIN_PAGE;
            }

        } else if (state.active_page == ADD_ITEM) {
            UseCase::add_item(state);

        } else if (state.active_page == PLACE_ITEM) {
            UseCase::place_item(state);

        } else if (state.active_page == DEL_LAST) {
            UseCase::delete_last(state);

        } else if (state.active_page == USE_ITEM) {
            UseCase::use_item(state);
        }
    }
    cout << "Terima kasih telah menggunakan aplikasi ini!\n";
    return 0;
}