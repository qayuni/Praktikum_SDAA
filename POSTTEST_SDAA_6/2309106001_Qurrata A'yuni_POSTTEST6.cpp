#include <iostream>
#include <string>
#include <stack>
#include <queue>
#include <cmath>

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
const int NO_OF_CHARS = 256;


bool cekUser(const acc daftaracc[], int jumlah_acc, const string& nama_acc);
bool validpass(const string& pass);
void signup(acc daftaracc[], int& jumlah_acc);
bool login(const acc daftaracc[], int jumlah_acc);
void menucrud(Paket *&head);
void addpack(Paket *&head);
void insertSampleData(Paket *&head);
void display(Paket *head);
void updatestatus(Paket *&head);
void deletebyresi(Paket *&head);
void displaySorted(Paket *head, bool ascending);
void mergeSort(Paket** arr, int left, int right);
void merge(Paket** arr, int left, int mid, int right);
void quickSort(Paket** arr, int low, int high);
void badCharHeuristic(string str, int size, int badChar[NO_OF_CHARS]);
void search(Paket *head, string pat);
vector<Paket*> fibsearch(Paket *head, double x, int n);
vector<Paket*> jumpsearch(Paket *head, double x, int n);
int findberat(Paket *head, int idx);
int length(Paket *head);
void displaySearchResults(const vector<Paket*>& hasilPencarian);
void disfibsearch(Paket* head);
void disjumpseacrh(Paket *head);


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
        cout<<"Nama Pengirim   : "<<temp->nama_pengirim<<endl;
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
            cout<<"Nama Pengirim   : "<<current->nama_pengirim<<endl;
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

void insertSampleData(Paket *&head) {
    Paket *paket1 = new Paket{"123456", "Alice", "Bob", "Jl. Sudirman No. 1", "Dokumen", 1.5, "Dikirim", nullptr};
    Paket *paket2 = new Paket{"789012", "Charlie", "David", "Jl. Thamrin No. 2", "Pakaian", 2.0, "Dikirim", nullptr};
    Paket *paket3 = new Paket{"345678", "Eve", "Frank", "Jl. Gatot Subroto No. 3", "Elektronik", 3.0, "Dikirim", nullptr};
    Paket *paket4 = new Paket{"901234", "Grace", "Heidi", "Jl. Rasuna Said No. 4", "Makanan", 1.2, "Dikirim", nullptr};
    Paket *paket5 = new Paket{"567890", "Ivan", "Judy", "Jl. Kuningan No. 5", "Buku", 0.8, "Dikirim", nullptr};

    paket1->next = paket2;
    paket2->next = paket3;
    paket3->next = paket4;
    paket4->next = paket5;
    paket5->next = nullptr;

    head = paket1;

}

int partition(Paket** arr, int low, int high) {
    double pivot = arr[high]->berat;
    int i = (low - 1);
    for (int j = low; j < high; j++) {
        if (arr[j]->berat >= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void merge(Paket** arr, int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Paket** L = new Paket*[n1];
    Paket** R = new Paket*[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    i = 0; 
    j = 0; 
    k = left; 

    while (i < n1 && j < n2) {
        if (L[i]->berat <= R[j]->berat) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }

    while (i < n1)
        arr[k++] = L[i++];

    while (j < n2)
        arr[k++] = R[j++];

    delete[] L;
    delete[] R;
}


void mergeSort(Paket** arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}


void quickSort(Paket** arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}


void displaySorted(Paket *head, bool ascending) {
    if (head == nullptr) {
        cout << "Data masih kosong!" << endl;
        return;
    }


    int count = 0;
    Paket *temp = head;
    while (temp != nullptr) {
        count++;
        temp = temp->next;
    }
    
    Paket **arr = new Paket*[count];
    temp = head;
    for (int i = 0; i < count; i++) {
        arr[i] = temp;
        temp = temp->next;
    }

    if (ascending) {
        mergeSort(arr, 0, count - 1);
        cout << "Data setelah diurutkan (Ascending berdasarkan BERAT):" << endl << endl;
    } else {
        quickSort(arr, 0, count - 1);
        cout << "Data setelah diurutkan (Descending berdasarkan BERAT):" << endl << endl;
    }

    for (int i = 0; i < count; i++) {
        cout << "No.Resi         : " << arr[i]->resi << endl;
        cout << "Nama Pengirim   : " << arr[i]->nama_pengirim << endl;
        cout << "Nama Penerima   : " << arr[i]->nama_penerima << endl;
        cout << "Alamat Penerima : " << arr[i]->alamat_penerima << endl;
        cout << "Jenis Barang    : " << arr[i]->jenis_barang << endl;
        cout << "Berat Barang    : " << arr[i]->berat << " kg" << endl;
        cout << "Status Paket    : " << arr[i]->status << endl << endl;
    }

    delete[] arr;
}

int length (Paket *head) {
	int count = 0;
	Paket *temp = head;
	while (temp != NULL){
		count++;
		temp = temp->next;
	}
	return count;
}

int min(int x, int y){
	return (x<=y) ? x : y;
}

vector<Paket*> fibsearch(Paket *head, double x, int n) {
    vector<Paket*> hasilPencarian;
    Paket *temp = head;
    int fibm2 = 0;
    int fibm1 = 1;
    int fibm = fibm2 + fibm1;

    while (fibm < n) {
        fibm2 = fibm1;
        fibm1 = fibm;
        fibm = fibm2 + fibm1;
    }

    int offset = -1;
    while (fibm > 1) {
        int i = min(offset + fibm2, n - 1);
        temp = head;

        for (int j = 0; j < i; j++) {
            temp = temp->next;
        }

        if (temp->berat < x) {
            fibm = fibm1;
            fibm1 = fibm2;
            fibm2 = fibm - fibm1;
            offset = i;
        } else if (temp->berat > x) {
            fibm = fibm2;
            fibm1 = fibm1 - fibm2;
            fibm2 = fibm - fibm1;
        } else {
            hasilPencarian.push_back(temp);

            Paket *tempBack = temp;
            int backIdx = i - 1;
            while (backIdx >= 0) {
                Paket *temp2 = head;
                for (int j = 0; j < backIdx; j++) {
                    temp2 = temp2->next;
                }
                if (temp2->berat == x) {
                    hasilPencarian.push_back(temp2);
                } else {
                    break;
                }
                backIdx--;
            }

            Paket *tempForward = temp->next;
            while (tempForward != NULL && tempForward->berat == x) {
                hasilPencarian.push_back(tempForward);
                tempForward = tempForward->next;
            }

            return hasilPencarian;
        }
    }

    temp = head;
    for (int j = 0; j < offset + 1; j++) {
        temp = temp->next;
    }

    if (fibm1 && temp->berat == x) {
        hasilPencarian.push_back(temp);

        Paket *tempForward = temp->next;
        while (tempForward != NULL && tempForward->berat == x) {
            hasilPencarian.push_back(tempForward);
            tempForward = tempForward->next;
        }
    }

    return hasilPencarian;
}

int findberat(Paket *head, int idx)
{
    for (int i = 0; i < idx; i++)
    {
        head = head->next;
    }
    return head->berat;
}

vector<Paket*> jumpsearch(Paket *head, double x, int n) {
    vector<Paket*> hasilPencarian;
    int step = sqrt(n);
    int prev = 0;

    while (findberat(head, min(step, n) - 1) < x) {
        prev = step;
        step += sqrt(n);
        if (prev >= n) {
            return hasilPencarian;
        }
    }

    while (findberat(head, prev) < x) {
        prev++;
        if (prev == min(step, n)) {
            return hasilPencarian;
        }
    }

    if (findberat(head, prev) == x) {
        for (int i = prev; i < n && findberat(head, i) == x; i++) {
            Paket *temp = head;
            for (int j = 0; j < i; j++) {
                temp = temp->next;
            }
            hasilPencarian.push_back(temp);
        }
    }

    return hasilPencarian;
}

void badCharHeuristic(string str, int size, int badChar[NO_OF_CHARS])
{
    for (int i = 0; i < NO_OF_CHARS; i++)
    {
        badChar[i] = -1;
    }
    for (int i = 0; i < size; i++)
    {
        badChar[(int)str[i]] = i;
    }
}
 
void search(Paket *head, string pat) {
    int m = pat.size();
    Paket *temp = head;
    bool found = false;

    cout << "\nHasil Pencarian Pengirim yang Mengandung: \"" << pat << "\"" << endl;
    cout << "=========================================" << endl;

    while (temp != NULL) {
        int n = temp->nama_pengirim.size();
        int badChar[NO_OF_CHARS];
        badCharHeuristic(pat, m, badChar);

        int s = 0; 
        while (s <= (n - m)) {
            int j = m - 1;

            while (j >= 0 && pat[j] == temp->nama_pengirim[s + j]) {
                j--;
            }

            if (j < 0) {
                cout << "\nNo.Resi         : " << temp->resi << endl;
                cout << "Nama Pengirim   : " << temp->nama_pengirim << endl;
                cout << "Nama Penerima   : " << temp->nama_penerima << endl;
                cout << "Alamat Penerima : " << temp->alamat_penerima << endl;
                cout << "Jenis Barang    : " << temp->jenis_barang << endl;
                cout << "Berat Barang    : " << temp->berat << " kg" << endl;
                cout << "Status Paket    : " << temp->status << endl << endl;
                
                s += (s + m < n) ? m - badChar[temp->nama_pengirim[s + m]] : 1;
                found = true;
                break;
            } else {
                s += max(1, j - badChar[(int)temp->nama_pengirim[s + j]]);
            }
        }
        temp = temp->next;
    }

    if (!found) {
        cout << "Tidak ada hasil yang ditemukan untuk pengirim \"" << pat << "\"" << endl;
    }
}

void displaySearchResults(const vector<Paket*>& hasilPencarian) {
    if (hasilPencarian.empty()) {
        cout << "Tidak ada hasil yang ditemukan!" << endl;
        return;
    }

    cout << "\nHasil Pencarian: " << endl;
    for (int i = 0; i < hasilPencarian.size(); ++i) {
        cout << "\nData ke-" << i + 1 << ":" << endl;
        cout << "No.Resi         : " << hasilPencarian[i]->resi << endl;
        cout << "Nama Pengirim   : " << hasilPencarian[i]->nama_pengirim << endl;
        cout << "Nama Penerima   : " << hasilPencarian[i]->nama_penerima << endl;
        cout << "Alamat Penerima : " << hasilPencarian[i]->alamat_penerima << endl;
        cout << "Jenis Barang    : " << hasilPencarian[i]->jenis_barang << endl;
        cout << "Berat Barang    : " << hasilPencarian[i]->berat << " kg" << endl;
        cout << "Status Paket    : " << hasilPencarian[i]->status << endl;
    }
}

void disfibsearch(Paket* head) {
    double beratCari;
    cout << "Masukkan Berat Barang yang ingin dicari: ";
    cin >> beratCari;

    int n = length(head);
    
    if (n == 0) {
    	cout << "Data tidak ditemukan!" << endl;
    	return;
	}
	
    vector<Paket*> hasilPencarian = fibsearch(head, beratCari, n);
    displaySearchResults(hasilPencarian);
}

void disjumpsearch(Paket *head){
	double beratCari;
    cout << "Masukkan Berat Barang yang ingin dicari: ";
    cin >> beratCari;

    int n = length(head);

    if (n == 0) {
    	cout << "Data tidak ditemukan!" << endl;
    	return;
	}
	
    vector<Paket*> hasilPencarian = jumpsearch(head, beratCari, n);
    displaySearchResults(hasilPencarian);
}
 

void menucrud(Paket *&head) {
    char pilih;
    string xs;


    insertSampleData(head);

    do {
        cout << "\n======================================" << endl;
        cout << "               M E N U  "<< endl;
        cout << "======================================" << endl;
        cout << " 1. Tambah data paket" << endl;
        cout << " 2. Lihat semua paket" << endl;
        cout << " 3. Update status paket" << endl;
        cout << " 4. Hapus data paket" << endl;
        cout << " 5. Sort Berat (Ascending)" << endl;
        cout << " 6. Sort Berat (Descending)" << endl;
        cout << " 7. Jump Search (Berat)" << endl;
        cout << " 8. Fibonacci Search (Berat)" << endl;
        cout << " 9. Boyer Moore Search (Nama Pengirim)" << endl;
        cout << "10. Kembali ke menu utama" << endl;
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
                displaySorted(head, true);
                break;
            case '6':
                displaySorted(head, false);
                break;
            case '7': {
                displaySorted(head, true);  
                disjumpsearch(head);
                break;
            }
            case '8': {
                displaySorted(head, true);  
                disfibsearch(head);
                break;
            }
            case '9':
                cout << "Cari data berdasarkan Nama Pengirim: ";
                getline(cin, xs);
                search(head, xs);
                break;
            case '10':
                cout << "Kembali ke menu utama" << endl;
                break;
            default:
                cout << "Pilihan tidak valid." << endl;
        }
    } while (pilih != '10');
}
