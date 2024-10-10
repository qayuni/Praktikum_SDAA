#include <iostream>
#include <string>
#include <stack>
#include <queue>

using namespace std;

struct acc {
    string nama_acc;
    string pass;
};

struct Paket {
    string resi;
    string nama_pengirim;
    string nama_penerima;
    string alamat_penerima;
    string jenis_barang;
    double berat;
    string status;
    Paket *next;
};

stack<Paket*> paketstack;
queue<Paket*> paketqueue;


bool cekUser(const acc daftaracc[], int jumlah_acc, const string& nama_acc);
bool validpass(const string& pass);
void signup(acc daftaracc[], int& jumlah_acc);
bool login(const acc daftaracc[], int jumlah_acc);
void menucrud(Paket *&head);
void addpack(Paket *&head);
void display(Paket *head);
void updatestatus(Paket *&head);
void deletebyresi(Paket *&head);


int main() {
    acc daftaracc[100];
    Paket  *head = nullptr;
    int jumlah_acc = 0;
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
                    menucrud(head);
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
        cout << "Masukkan Password (min 8 karakter): ";
        getline(cin, pass);
        if (!validpass(pass)) {
            cout << "Password terlalu pendek! Minimal 8 karakter." << endl;
        }
    } while (!validpass(pass));

    daftaracc[jumlah_acc++] = {nama_acc, pass};
    cout << "\n\nSign Up Berhasil! Username \"" << nama_acc << "\" telah terdaftar" << endl;
}


bool login(const acc daftaracc[], int jumlah_acc) {
    string username, pass;
    bool berhasil = false;

    cout << "\n=============================" << endl;
    cout << "     M E N U  L O G I N" << endl;
    cout << "=============================\n\n";

    for (int kesempatan = 0; kesempatan < 3 && !berhasil; kesempatan++) {
        cout << "Masukkan username : ";
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
            cout << "\n\nLogin Berhasil! Selamat datang " << username << endl;
        } else {
            cout << "Username atau Password Salah. Silahkan cek Kembali." << endl;
            if (kesempatan < 2) {
                cout << "Kesempatan tersisa: " << (2 - kesempatan) << endl;
            }
        }
    }

    return berhasil;
}


void addpack(Paket *&head){
    string newResi, newNama_pengirim, newStatus, newNama_penerima, newAlamat_penerima, newJenis_barang;
    double newBerat;

    cout<<"\nMasukkan No.Resi : ";
    cin>>newResi;
    cin.ignore();
    cout << "Masukkan Nama Pengirim : ";
    getline(cin, newNama_pengirim);
    cout << "Masukkan Nama Penerima : ";
    getline(cin, newNama_penerima);
    cout << "Masukkan Alamat Penerima : ";
    getline(cin, newAlamat_penerima);
    cout << "Masukkan Jenis Barang : ";
    getline(cin, newJenis_barang);
    cout << "Masukkan Berat Barang (kg) : ";
    cin >> newBerat;
    cin.ignore();
    cout<<"Masukkan Status paket : ";
    getline(cin, newStatus);

    Paket *newNode = new Paket{newResi, newNama_pengirim, newNama_penerima, newAlamat_penerima, newJenis_barang, newBerat, newStatus, nullptr};

    if (head == nullptr){
        head = newNode;
    } else {
        Paket* temp = head;
        while(temp->next != nullptr){
            temp = temp->next;
        } 
        temp->next = newNode;
    }


    paketstack.push(newNode);
    cout<<"\nData Paket berhasil ditambahkan!\n"<<endl;
}


void display(Paket *head) {
    Paket *temp = head;
    int hitung = 1;

    cout << "\n======================================" << endl;
    cout << "              DATA PAKET  " << endl;
    cout << "======================================" << endl;

    if(temp == nullptr){
        cout<<"Data masih kosong!"<<endl<<endl;
        return;
    }

    while(temp != nullptr){
        cout<<"\nData ke-"<<hitung<<endl<<endl;
        cout<<"No.Resi         : "<<temp->resi<<endl;
        cout<<"Nama Pengirim  : "<<temp->nama_pengirim<<endl;
        cout<<"Nama Penerima   : "<<temp->nama_penerima<<endl;
        cout<<"Alamat Penerima : "<<temp->alamat_penerima<<endl;
        cout<<"Jenis Barang    : "<<temp->jenis_barang<<endl;
        cout<<"Berat Barang    : "<<temp->berat<<" kg"<<endl;
        cout<<"Status Paket    : "<<temp->status<<endl<<endl;

        temp = temp->next;
        hitung++;
    }
}


void updatestatus(Paket *&head){
    if (paketstack.empty()){
        cout<<"\nStack kosong! Tidak ada paket yang dapat diupdate.\n" << endl;
        return;
    }
    
    display(head);

	cout << "======================================" << endl << endl;
    string resi;
    cout << "\nMasukkan No.Resi paket yang ingin diupdate statusnya: ";
    getline(cin, resi);

    bool found = false;
    stack<Paket*> tempStack;


    while(!paketstack.empty()){
        Paket* current = paketstack.top();
        paketstack.pop();
        if(current->resi == resi){
            cout<<"\nData Ditemukan!"<<endl<<endl;
            cout<<"No.Resi         : "<<current->resi<<endl;
            cout<<"Nama Pengirim  : "<<current->nama_pengirim<<endl;
            cout<<"Nama Penerima   : "<<current->nama_penerima<<endl;
            cout<<"Alamat Penerima : "<<current->alamat_penerima<<endl;
            cout<<"Jenis Barang    : "<<current->jenis_barang<<endl;
            cout<<"Berat Barang    : "<<current->berat<<" kg"<<endl;
            cout<<"Status Paket saat ini : "<<current->status<<endl<<endl;

            string newStatus;
            cout<<"Masukkan Status paket baru : ";
            getline(cin, newStatus);
            current->status = newStatus;
            cout<<"\nStatus paket berhasil diubah!\n"<<endl;
            found = true;
        }
        tempStack.push(current);
    }


    while(!tempStack.empty()){
        paketstack.push(tempStack.top());
        tempStack.pop();
    }

    if (!found){
        cout<<"\nData dengan No.Resi \""<<resi<<"\" tidak ditemukan :("<<endl;
    }
}

void deletebyresi(Paket *&head) {
    if (head == nullptr) {
        cout << "\nData masih kosong!" << endl;
        return;
    }
    
    display(head);
    
    cout << "======================================" << endl << endl;
    string resi;
    cout << "\nMasukkan No. Resi yang ingin dihapus: ";
    getline(cin, resi);

    bool found = false;


    Paket* current = head;
    while (current != nullptr) {
        paketqueue.push(current);
        current = current->next;
    }


    head = nullptr;
    Paket* tail = nullptr;

    while (!paketqueue.empty()) {
        Paket* pkg = paketqueue.front();
        paketqueue.pop();
        if (pkg->resi == resi) {
            found = true;
            delete pkg;
            continue;
        }
        
        if (head == nullptr) {
            head = pkg;
            tail = pkg;
            tail->next = nullptr;
        } else {
            tail->next = pkg;
            tail = pkg;
            tail->next = nullptr;
        }
    }

    if (found) {
        cout << "\nData dengan No.Resi \"" << resi << "\" berhasil dihapus!\n" << endl;
    } else {
        cout << "\nData dengan No.Resi \"" << resi << "\" tidak ditemukan!\n" << endl;
    }
}

void menucrud(Paket *&head) {
    char pilih;

    do {
        cout << "\n======================================" << endl;
        cout << "               M E N U  "<< endl;
        cout << "======================================" << endl;
        cout << " 1. Tambah data paket" << endl;
        cout << " 2. Lihat semua paket" << endl;
        cout << " 3. Update status paket" << endl;
        cout << " 4. Hapus data paket" << endl;
        cout << " 5. Kembali ke menu utama" << endl;
        cout << "======================================" << endl;
        cout << " Masukkan pilihan menu : ";
        cin >> pilih;
        cin.ignore();

        switch (pilih) {
            case '1':
                addpack(head);
                break;
            case '2':
                display(head);
                break;
            case '3':
                updatestatus(head);
                break;
            case '4':
                deletebyresi(head);
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

