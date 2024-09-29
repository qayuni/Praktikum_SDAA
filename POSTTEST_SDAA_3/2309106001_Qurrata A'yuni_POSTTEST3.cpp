#include <iostream>
#include <string>

using namespace std;

//Single linked list
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

struct acc {
    string nama_acc;
    string pass;
};

void adddirst(Paket *&head);
void menucrud(Paket *&head);
void display(Paket *head);
void updatestatus(Paket *&head);
void deletebyresi(Paket *&head);

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
    cout << "\n\nSign Up Berhasil! Username " << nama_acc << " telah terdaftar" << endl;
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
            cout << "\n\nLogin Berhasil! Selamat datang " << username << endl;
        } else {
            cout << "Username atau Password Salah. Silahkan cek Kembali." << endl;
        }
    }

    return berhasil;
}

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


void addfirst(Paket *&head) {
    string newResi, newNama_pengirim, newStatus, newNama_penerima, newAlamat_penerima, newJenis_barang;
    double newBerat;
    char loop;

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
    cin.ignore();

    Paket *newNode = new Paket{newResi, newNama_pengirim, newNama_penerima, newAlamat_penerima, newJenis_barang, newBerat, newStatus, nullptr};


	newNode->next = head;
    head = newNode;

    cout << "\nData Berhasil ditambahkan!\n" << endl;
}

void display(Paket *head){
	Paket *temp = head;
	int hitung = 1;
	
	     cout << "\n======================================" << endl;
        cout << "              DATA PAKET  "<< endl;
        cout << "======================================" << endl;
	
	if(temp == nullptr){
		cout<<"Data masih kosong!"<<endl<<endl;
		return;
	}
	
	while(temp != nullptr){
		cout<<"\nData ke-"<<hitung<<endl<<endl;
		cout<<"No.Resi : "<<temp->resi<<endl;
		cout<<"Nama Pengirim : "<<temp->nama_pengirim<<endl;
		cout<<"Nama Penerima : "<<temp->nama_penerima<<endl;
		cout<<"Alamat Penerima : "<<temp->alamat_penerima<<endl;
		cout<<"Jenis Barang : "<<temp->jenis_barang<<endl;
		cout<<"Berat Barang : "<<temp->berat<<endl;
		cout<<"Status Paket : "<<temp->status<<endl<<endl;
		
		temp = temp->next;
		hitung++;
	}
}

void updatestatus(Paket *&head){
	string resi;
	
	display(head);
	
	cout<<"\nMasukkan No.resi : ";
	cin>>resi;
	
	Paket *temp  = head;
	bool found = false;
	
	
	while(temp != nullptr){
		if(temp->resi == resi){
			found = true;
			break;
		}
		temp = temp->next;
	}
	
	if (found){
		cout<<"\nData Ditemukan!"<<endl<<endl;
		cout<<"Masukkan Status paket : ";
		cin>>temp->status;
		cout<<endl<<endl;
		cout<<"\nStatus paket berhasil diubah!"<<endl;
	} else {
		cout<<"\nData tidak ditemukan :("<<endl;
	}
}

void deletebyresi(Paket *&head) {
    string resi;
    
    display(head);
    
    cout<<"\nMasukkan No. Resi yang ingin dihapus: ";
    cin>>resi;
    cin.ignore();

    Paket *temp = head;
    Paket *prev = nullptr;

    
    while (temp != nullptr) {
        if (temp->resi == resi) {
            if (prev == nullptr) {
                head = temp->next;
            } else {
                prev->next = temp->next;
            }
            delete temp;
            cout << "\nData dengan No. Resi " << resi << " berhasil dihapus!" << endl;
            return;
        }
        prev = temp;
        temp = temp->next;
    }

    cout << "\nData dengan No. Resi " << resi << " tidak ditemukan!" << endl; // If not found
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
                addfirst(head);
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
