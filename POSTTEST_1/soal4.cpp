#include <iostream>
using namespace std;

void tukar(int **d_ptr_a, int **d_ptr_b) {
    int temp = **d_ptr_a;
    **d_ptr_a = **d_ptr_b;
    **d_ptr_b = temp;
}

int main() {
    int a, b;
    
    cout << "Masukkan nilai pertama (a): ";
    cin >> a;
    cout << "Masukkan nilai kedua (b): ";
    cin >> b;
    
    int *ptr_a = &a;
    int *ptr_b = &b;
    
    cout << "\nSebelum pertukaran:" << endl;
    cout << "a = " << a << ", b = " << b << endl;
    
    tukar(&ptr_a, &ptr_b);
    
    cout << "\nSetelah pertukaran:" << endl;
    cout << "a = " << a << ", b = " << b << endl;
    
    return 0;
}