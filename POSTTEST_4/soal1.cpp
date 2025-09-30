#include <iostream>
#include <string>
using namespace std;

struct Node {
    char data;
    Node* next;
};

void push(Node*& top, char data) {
    Node* newNode = new Node{data, top};
    top = newNode;
}

char pop(Node*& top) {
    if (top == nullptr) return '\0'; // Return null character jika stack kosong
    Node* temp = top;
    char poppedValue = temp->data;
    top = top->next;
    delete temp;
    return poppedValue;
}

string reverseString(string s) {
    Node* stackTop = nullptr; // Stack masih kosong
    string reversed = ""; // Variable untuk menyimpan string terbalik
    for (char c : s) { // Iterasi setiap karakter dalam string
        push(stackTop, c); // Push karakter ke stack 
    }

    while (stackTop != nullptr) { // Selama stack tidak kosong
        reversed += pop(stackTop); // Pop karakter dari stack dan tambahkan ke string reversed
    }
    return reversed; // Mengembalikan string terbalik
}

int main() {
    string text = "Struktur Data";
    cout << "Teks asli: " << text << endl;
    cout << "Teks terbalik: " << reverseString(text) << endl; // Output: ataD rutkurts
    return 0;
}