#include <iostream>
using namespace std;

/*maksud dari singkatan
jml_DU = jumlah diagonal utama
jml_DS = jumlah diagonal sekunder
*/

int main() {
    int matriks[3][3] = {
        {3, 6, 9},
        {1, 4, 2},
        {2, 3, 7}
    };
    int jml_DU = 0;
    int jml_DS = 0;
    
    for(int i = 0; i < 3; i++) {
        jml_DU += matriks[i][i]; 
        jml_DS += matriks[i][2-i];
    }

    cout << "Matriks 3x3:" << endl;
    for (int i = 0; i < 3; i ++) {
        for (int j = 0; j < 3; j ++) {
            cout << matriks[i][j] << " ";
        }
        cout << endl;
    }
    cout << "\nJumlah diagonal utama: " << jml_DU << endl;
    cout << "Jumlah diagonal sekunder: " << jml_DS << endl;
    cout << "Total jumlah diagonal utama + sekunder: " << jml_DU + jml_DS << endl;
    
    return 0;
}