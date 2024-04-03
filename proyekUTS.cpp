#include <iostream>
#include <iomanip>
#include <cstring>

using namespace std;

// Struktur untuk menyimpan informasi tugas
struct taskManager {
    char task[50]; //judul tugas
    char date[20]; //tenggat waktu(tanggal)
    char time[20]; //tenggat waktu(jam)
};

// Node untuk linked list tugas
struct Node {
    taskManager data; //data tugas yang disimpan dalam node
    Node* next; //pointer ke node berikutnya dalam linked list
};

// Array untuk menyimpan tugas yang selesai
taskManager completeTasks[100];
int completeTasksCount = 0;

//inisiasikan fungsi
void addTask(Node** head, const taskManager& newTask); //untuk menambahkan tugas
void displayTask(Node* head); //untuk menampilkan tugas
void completeTask(Node** head, const char* task); //untuk menandai tugas sebagai selesai
void editTask(Node* head, const char* task); //untuk mengedit tugas
void deleteTask(Node** head, const char* task); //untuk menghapus tugas
void deleteAll(Node** head); //untuk bersihkan semua node dalam linked list

int main() {
    Node* head = NULL; // Pointer ke node pertama dalam linked list
    int pilihan;

    do {
        system("cls");
        // tampilan menu utama
        cout << string(30,'=') << endl;
        cout << string(13,' ') << "MENU\n";
        cout << string(30,'=') << endl;
        cout << "1. Tambah Tugas Baru\n";
        cout << "2. Tandai Tugas selesai\n";
        cout << "3. Tampilkan Daftar Tugas\n";
        cout << "4. Edit Tugas\n";
        cout << "5. Hapus Tugas\n";
        cout << "0. Keluar\n";
        cout << "Pilihan Anda: ";
        cin >> pilihan;

        switch(pilihan) {
            case 1:
                system("cls");
                taskManager newTask;
                // tampilan menu untuk menambahkan tugas
                cout << string(50,'=') << endl;
                cout << string(17,' ') << "TAMBAH TUGAS BARU\n";
                cout << string(50,'=') << endl;
                cout << "Masukkan judul Tugas: ";
                cin.ignore(); // Membersihkan buffer
                cin.getline(newTask.task, sizeof(newTask.task));
                cout << "-Masukkan Tenggat-\n";
                cout << "Tanggal (dd/mm/yyyy): ";
                cin >> newTask.date;
                cout << "Waktu (hh:mm): ";
                cin >> newTask.time;
                addTask(&head, newTask); //memanggil fungsi untuk menambahkan tugas
                cout << "Tugas berhasil ditambahkan.\n\n";
                system("pause");
                break;
            case 2:
            {
                system("cls");
                char task[50];
                // tampilan menu untuk menandai tugas sebagai selesai
                cout << string(50,'=') << endl;
                cout << string(15,' ') << "TANDAI TUGAS SELESAI\n";
                cout << string(50,'=') << endl;
                cout << "Masukkan judul tugas yang sudah selesai: ";
                cin.ignore(); // Membersihkan buffer
                cin.getline(task, sizeof(task));
                completeTask(&head, task); //memanggil fungsi untuk menandai tugas sebagai selesai
                system("pause");
                break;
            }
            case 3:
                system("cls");
                // tampilan menu untuk menampilkan daftar tugas
                cout << string(50,'=') << endl;
                cout << string(19,' ') << "DAFTAR TUGAS\n";
                cout << string(50,'=') << endl;
                displayTask(head); //memanggil fungsi untuk menampilkan daftar tugas
                system("pause");
                break;
            case 4:
            {
                system("cls");
                char task[50];
                // tampilan menu untuk mengedit tugas
                cout << string(50,'=') << endl;
                cout << string(20,' ') << "EDIT TUGAS\n";
                cout << string(50,'=') << endl;
                cout << "Masukkan judul tugas yang ingin diedit: ";
                cin.ignore(); // Membersihkan buffer
                cin.getline(task, sizeof(task));
                editTask(head, task); //memanggil fungsi untuk mengedit tugas
                system("pause");
                break;
            }
            case 5:
            {
                system("cls");
                char task[50];
                // tampilan menu untuk menghapus tugas
                cout << string(50,'=') << endl;
                cout << string(19,' ') << "HAPUS TUGAS\n";
                cout << string(50,'=') << endl;
                cout << "Masukkan judul tugas yang ingin dihapus: ";
                cin.ignore(); // Membersihkan buffer
                cin.getline(task, sizeof(task));
                deleteTask(&head, task); //memanggil fungsi untuk menghapus tugas
                system("pause");
                break;
            }
            case 0:
                cout << "Keluar\n";
                break;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi.\n\n";
                system("pause");
        }
    } while(pilihan != 0);

    // Membersihkan semua node dalam linked list sebelum keluar dari program
    deleteAll(&head);

    return 0;
}

// Fungsi untuk menambahkan tugas ke linked list
void addTask(Node** head, const taskManager& newTask) {
    Node* newNode = new Node;
    newNode->data = newTask; //memaasukkan data tugas ke dalam node baru
    newNode->next = NULL; ///mengatur popinter next node baru menjadi NULL

    //jika linked list kosong, node baru akan menjadi node pertama
    if (*head == NULL) { 
        *head = newNode;
    } else {
        Node* current = *head;
        Node* prev = NULL;
        // mencari tempat yang tepat untuk memasukkan node baru secara berurutan berdasarkan tanggal dan waktu
        while (current != nullptr && (strcmp(current->data.date, newTask.date) < 0 || (strcmp(current->data.date, newTask.date) == 0
        && strcmp(current->data.time, newTask.time) <= 0))) {
            prev = current;
            current = current->next;
        }
        //memasukkan node baru sesuai dengan posisinya
        if (prev == NULL) { 
            newNode->next = *head;
            *head = newNode;
        } else {
            prev->next = newNode;
            newNode->next = current;
        }
    }
}

// Fungsi untuk menandai tugas sebagai selesai berdasarkan judul
void completeTask(Node** head, const char* task) {
    Node* current = *head;
    Node* prev = NULL;
    // mencari tugas berdasarkan judul
    while (current != NULL) { 
        if (strcmp(current->data.task, task) == 0) {
            // jika judul ditemukan, tugas tersebut akan dihapus dari linked list
            if (prev != NULL) { 
                prev->next = current->next;
            } else {
                *head = current->next;
            }
            // Memindahkan tugas yang selesai/dihapus dari linked list ke dalam array
            completeTasks[completeTasksCount++] = current->data;
            delete current; //menghapus node dari memory
            cout << "Selamat!!.\n\n";
            return;
        }
        prev = current;
        current = current->next;
    }
    cout << "tugas tidak ditemukan.\n\n";
}

// Fungsi untuk menampilkan semua tugas dalam bentuk tabel
void displayTask(Node* head) {
    Node* current = head;
    // menampilkan daftar tugas yang belum selesai
    cout << "Tugas anda:\n";
    cout << setfill('-') << setw(50) << "-" << setfill(' ') << endl;
    cout << left << setw(30) << "Tugas" << setw(25) << "Tenggat" << endl;
    cout << setfill('-') << setw(50) << "-" << setfill(' ') << endl;
    while (current != NULL) { 
        cout << left << setw(30) << current->data.task << setw(15) << current->data.date << setw(8) << current->data.time << endl;
        current = current->next;
    }
    // menampilkan data tugas yang sudah selesai
    cout << setfill('-') << setw(50) << "-" << setfill(' ') << endl;
    cout << endl;
    cout << "Tugas selesai:\n";
    cout << setfill('-') << setw(50) << "-" << setfill(' ') << endl;
    cout << left << setw(30) << "Tugas" << setw(25) << "Tenggat" << endl;
    cout << setfill('-') << setw(50) << "-" << setfill(' ') << endl;
    for (int i = 0; i < completeTasksCount; i++) {
        cout << left << setw(30) << completeTasks[i].task << setw(15) << completeTasks[i].date << setw(8) << completeTasks[i].time << endl;
    }
    cout << setfill('-') << setw(50) << "-" << setfill(' ') << endl;
}

// Fungsi untuk mengedit tugas berdasarkan judul
void editTask(Node* head, const char* task) {
    Node* current = head;
    // mencari tugas berdasarkan judul
    while (current != NULL) { 
        if (strcmp(current->data.task, task) == 0) {
            // jika tugas ditemukan, pengguna akan memasukkan informasi tugas yang baru
            cout << "Masukkan judul baru: ";
            // cin.ignore(); // Membersihkan buffer
            cin.getline(current->data.task, sizeof(current->data.task));
            cout << "Masukkan tanggal baru (dd/mm/yyyy): ";
            cin >> current->data.date;
            cout << "Masukkan waktu baru (hh:mm): ";
            cin >> current->data.time;
            cout << "tugas berhasil diedit.\n\n";
            return;
        }
        current = current->next;
    }
    cout << "tugas tidak ditemukan.\n\n";
}

// Fungsi untuk menghapus tugas berdasarkan judul
void deleteTask(Node** head, const char* task) {
    Node* current = *head;
    Node* prev = NULL; 
    // mencari tugas berdasarkan judul
    while (current != NULL) { 
        if (strcmp(current->data.task, task) == 0) {
            // jika tugas ditemukan maka tugas tersebut akan dihapus dari linked list
            if (prev != NULL) { 
                prev->next = current->next;
            } else {
                *head = current->next;
            }
            delete current; //menghapus node dari memory
            cout << "Tugas berhasil dihapus.\n\n";
            return;
        }
        prev = current;
        current = current->next;
    }
    cout << "Tugas tidak ditemukan.\n\n";
}

// Fungsi untuk membersihkan semua node dalam linked list
void deleteAll(Node** head) {
    Node* current = *head;
    while (current != NULL) { 
        Node* temp = current;
        current = current->next;
        delete temp; //menghapus node dari memory
    }
    *head = NULL; //mengatur pointer head menjadi NULL
}
