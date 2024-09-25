#include <iostream>
#include <string>

using namespace std;

const int max_paket = 100;

struct Paket {
    int resi;
    string nama_pengirim;
    string nama_penerima;
    string alamat_penerima;
    string jenis_barang;
    double berat;
};

struct acc {
    string nama_acc;
    string pass;
};

bool cekUser(const acc daftaracc[], int jumlah_acc, const string& nama_acc) {
    for (int i = 0; i < jumlah_acc; i++) {
        if (daftaracc[i].nama_acc == nama_acc) {
            return true;
        }
    }
    return false;
}

bool validpass(const string& pass) {
    return pass.length() >= 8;
}

void signup(acc daftaracc[], int& jumlah_acc) {
    string nama_acc, pass;

    cout << "==============================" << endl;
    cout << "     M E N U  S I G N U P" << endl;
    cout << "==============================" << endl;

    do {
        cout << "Masukkan Username : ";
        getline(cin, nama_acc);
        if (nama_acc.empty()) {
            cout << "Username tidak boleh kosong!" << endl;
        } else if (cekUser(daftaracc, jumlah_acc, nama_acc)) {
            cout << "Username sudah terdaftar, coba username lain" << endl;
            nama_acc = "";
        }
    } while (nama_acc.empty());

    do {
        cout << "Masukkan Password : ";
        getline(cin, pass);
    } while (!validpass(pass));

    daftaracc[jumlah_acc++] = {nama_acc, pass};
    cout << "Sign Up Berhasil! Username " << nama_acc << " telah terdaftar" << endl;
}

bool login(const acc daftaracc[], int jumlah_acc) {
    string username, pass;
    bool berhasil = false;

    cout << "\n=============================" << endl;
    cout << "     M E N U  L O G I N" << endl;
    cout << "=============================\n\n";

    for (int kesempatan = 0; kesempatan < 3 && !berhasil; kesempatan++) {
        cout << "Masukan username : ";
        getline(cin, username);
        cout << "Masukkan Password : ";
        getline(cin, pass);

        for (int i = 0; i < jumlah_acc; i++) {
            if (daftaracc[i].nama_acc == username && daftaracc[i].pass == pass) {
                berhasil = true;
                break;
            }
        }

        if (berhasil) {
            cout << "Login Berhasil! Selamat datang " << username << endl;
        } else {
            cout << "Username atau Password Salah. Silahkan cek Kembali." << endl;
        }
    }

    return berhasil;
}

void createpaket(Paket paketList[], int& jumlah_paket) {
    if (jumlah_paket >= max_paket) {
        cout << "Daftar paket sudah penuh!" << endl;
        return;
    }

    Paket paket;
    cout << "Masukkan Resi: ";
    cin >> paket.resi;
    cin.ignore();
    cout << "Masukkan Nama Pengirim: ";
    getline(cin, paket.nama_pengirim);
    cout << "Masukkan Nama Penerima: ";
    getline(cin, paket.nama_penerima);
    cout << "Masukkan Alamat Penerima: ";
    getline(cin, paket.alamat_penerima);
    cout << "Masukkan Jenis Barang: ";
    getline(cin, paket.jenis_barang);
    cout << "Masukkan Berat (kg): ";
    cin >> paket.berat;

    paketList[jumlah_paket++] = paket;
    cout << "Paket berhasil ditambahkan!" << endl;
}

void displaypaket(const Paket paketList[], int jumlah_paket) {
    cout << "Data Paket:" << endl;
    for (int i = 0; i < jumlah_paket; i++) {
        const auto& paket = paketList[i];
        cout << "Resi: " << paket.resi << ", Pengirim: " << paket.nama_pengirim 
             << ", Penerima: " << paket.nama_penerima 
             << ", Alamat: " << paket.alamat_penerima 
             << ", Jenis Barang: " << paket.jenis_barang 
             << ", Berat: " << paket.berat << " kg" << endl;
    }
}

void updatepaket(Paket paketList[], int jumlah_paket) {
    int resi;
    cout << "Masukkan Resi Paket yang ingin diupdate: ";
    cin >> resi;

    for (int i = 0; i < jumlah_paket; i++) {
        if (paketList[i].resi == resi) {
            cout << "Masukkan Nama Pengirim: ";
            cin.ignore();
            getline(cin, paketList[i].nama_pengirim);
            cout << "Masukkan Nama Penerima: ";
            getline(cin, paketList[i].nama_penerima);
            cout << "Masukkan Alamat Penerima: ";
            getline(cin, paketList[i].alamat_penerima);
            cout << "Masukkan Jenis Barang: ";
            getline(cin, paketList[i].jenis_barang);
            cout << "Masukkan Berat (kg): ";
            cin >> paketList[i].berat;
            cout << "Paket berhasil diupdate!" << endl;
            return;
        }
    }
    cout << "Paket dengan Resi tersebut tidak ditemukan!" << endl;
}

void deletepaket(Paket paketList[], int& jumlah_paket) {
    int resi;
    cout << "Masukkan Resi Paket yang ingin dihapus: ";
    cin >> resi;

    for (int i = 0; i < jumlah_paket; i++) {
        if (paketList[i].resi == resi) {
            paketList[i] = paketList[jumlah_paket - 1];
            jumlah_paket--;
            cout << "Paket berhasil dihapus!" << endl;
            return;
        }
    }
    cout << "Paket dengan Resi tersebut tidak ditemukan!" << endl;
}

void menucrud(Paket paketList[], int& jumlah_paket) {
    char pilih;

    do {
        cout << "\n======================================" << endl;
        cout << "               M E N U  "<< endl;
        cout << "======================================" << endl;
        cout << " 1. Tambah data paket" << endl;
        cout << " 2. Lihat semua paket" << endl;
        cout << " 3. Update data paket" << endl;
        cout << " 4. Hapus data paket" << endl;
        cout << " 5. Kembali ke menu utama" << endl;
        cout << "======================================" << endl;
        cout << " Masukkan pilihan menu : ";
        cin >> pilih;
        cin.ignore();

        switch (pilih) {
            case '1':
                createpaket(paketList, jumlah_paket);
                break;
            case '2':
                displaypaket(paketList, jumlah_paket);
                break;
            case '3':
                updatepaket(paketList, jumlah_paket);
                break;
            case '4':
                deletepaket(paketList, jumlah_paket);
                break;
            case '5':
                cout << "Kembali ke menu utama..." << endl;
                break;
            default:
                cout << "Pilihan tidak valid!" << endl;
                break;
        }
    } while (pilih != '5');
}

int main() {
    acc daftaracc[max_paket];
    Paket paketList[max_paket];
    int jumlah_acc = 0;
    int jumlah_paket = 0;
    char pilih;

    do {
        cout << "\n==================" << endl;
        cout << "|      Menu      |" << endl;
        cout << "==================" << endl;
        cout << "|   Pilih Menu   |" << endl;
        cout << "==================" << endl;
        cout << "| 1 | Sign Up    |" << endl;
        cout << "| 2 | Login      |" << endl;
        cout << "| 3 | Keluar     |" << endl;
        cout << "==================" << endl;
        cout << "Pilihan (1-3) : ";
        cin >> pilih;
        cin.ignore();

        switch (pilih) {
            case '1':
                signup(daftaracc, jumlah_acc);
                break;
            case '2':
                if (login(daftaracc, jumlah_acc)) {
                    menucrud(paketList, jumlah_paket);
                }
                break;
            case '3':
                cout << "\nTerimakasih telah menggunakan layanan kami :D" << endl;
                break;
            default:
                cout << "Pilihan tidak valid" << endl;
                break;
        }
    } while (pilih != '3');

    return 0;
}