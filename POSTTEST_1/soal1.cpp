#include <iostream>
using namespace std;

void tukar (int *k3, int size) {
    int *i0 = k3;
    int *i7 = k3 + size - 1;

    while (i0 < i7) {
        int temp = *i0;
        *i0 = *i7;
        *i7 = temp;

        i0++;
        i7--;
    }
}

int main() {
    int k3[7];
    int data = 3;
    
    for(int i = 0; i < 7; i++) {
        k3[i] = data;
        data += 3; 
    }
    
    cout << "Array kelipatan 3 sebelum dibalik:" << endl;
    for(int i = 0; i < 7; i++) {
        cout << k3[i] << " ";
    }
    cout << "\n" << endl;

    tukar(k3,7);
    cout << "Array kelipatan 3 setelah dibalik:" << endl;
    for(int i = 0; i < 7; i++) {
        cout << k3[i] << " ";
    }
    cout << endl;
    
    return 0;
}