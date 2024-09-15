#include <iostream>

using namespace std;


void mhanoi(int piringan, char asal, char sementara, char tujuan) {
    if (piringan == 1) {
        cout << "Memindahkan piringan 1 dari " << asal << " ke " << tujuan << endl;
        return;
    }
    mhanoi(piringan - 1, asal, tujuan, sementara);
    cout << "Memindahkan piringan " << piringan << " dari " << asal << " ke " << tujuan << endl;
    mhanoi(piringan - 1, sementara, asal, tujuan);
}

int main() {
    int piringan;
    bool valid;

    do {
        cout << "Masukkan jumlah piringan menara hanoi yang ingin diselesaikan: ";
        cin >> piringan;

        if (cin.fail()) {
            cout << "Input harus bilangan bulat!" << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            valid = false;
        } else {
            valid = true;
        }
    } while (!valid);

    cout << "Penyelesaian menara hanoi adalah seperti berikut: " << endl;
    mhanoi(piringan, 'A', 'B', 'C');

    return 0;
}

