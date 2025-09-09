#include <iostream>
using namespace std;

/*maksud dari singkatan
k3 = kelipatan 3
i0 = index 0
i7 = index 7
temp = temporary/sementara
*/

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

    tukar(k3,7);
    cout << "\n\nArray kelipatan 3 setelah dibalik:" << endl;
    for(int i = 0; i < 7; i++) {
        cout << k3[i] << " ";
    }
    cout << endl;
    
    return 0;
}