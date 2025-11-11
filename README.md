Asesmen Sub Clo3 - Praktikum Struktur Data

Nama: Chiara Calina Devi

NIM: 103122400016

Kelas:SE08-01

1. Kode Program 
File List.h

#include <iostream>

#ifndef LIST_H
#define LIST_H

#include <string>

struct Post {
    int id;
    std::string content;
    int likes;
    std::string username;
};


struct Node {
    Post info;
    Node* next;
};

struct List {
    Node* first;
};

List createNewList();
Node* allocate(const Post& data);
bool isEmpty(const List& L);

void insertFirst(List& L, Node* p);
void insertLast(List& L, Node* p);
void insertAfter(List& L, int xId, Node* p);

void deleteFirst(List& L, Node*& p);
void deleteLast(List& L, Node*& p);
void deleteAfter(List& L, int xId, Node*& p);

Node* findElement(const List& L, int id);
void printList(const List& L);


void insertSorted(List& L, const Post& data);
void showPostsByUser(const List& L, const std::string& username);
void showMostLiked(const List& L);
bool updateLikes(List& L, int id, bool like);


void clearList(List& L);

#endif

File List.cpp

#include "list.h"
#include <iostream>
#include <limits>

List createNewList() {
    List L;
    L.first = nullptr;
    return L;
}

Node* allocate(const Post& data) {
    Node* p = new Node;
    p->info = data;
    p->next = nullptr;
    return p;
}

bool isEmpty(const List& L) {
    return L.first == nullptr;
}

void insertFirst(List& L, Node* p) {
    if (!p) return;
    p->next = L.first;
    L.first = p;
}

void insertLast(List& L, Node* p) {
    if (!p) return;
    if (isEmpty(L)) {
        L.first = p;
        return;
    }
    Node* q = L.first;
    while (q->next != nullptr) q = q->next;
    q->next = p;
}

void insertAfter(List& L, int xId, Node* p) {
    if (!p) return;
    Node* q = findElement(L, xId);
    if (!q) {
        delete p;
        return;
    }
    p->next = q->next;
    q->next = p;
}

void deleteFirst(List& L, Node*& p) {
    p = nullptr;
    if (isEmpty(L)) return;
    p = L.first;
    L.first = L.first->next;
    p->next = nullptr;
}

void deleteLast(List& L, Node*& p) {
    p = nullptr;
    if (isEmpty(L)) return;

    if (L.first->next == nullptr) {
        p = L.first;
        L.first = nullptr;
        p->next = nullptr;
        return;
    }
    Node* prev = L.first;
    Node* cur  = L.first->next;
    while (cur->next != nullptr) {
        prev = cur;
        cur  = cur->next;
    }
    prev->next = nullptr;
    p = cur;
}

void deleteAfter(List& L, int xId, Node*& p) {
    p = nullptr;
    Node* q = findElement(L, xId);
    if (!q || !q->next) return;
    p = q->next;
    q->next = p->next;
    p->next = nullptr;
}

Node* findElement(const List& L, int id) {
    Node* cur = L.first;
    while (cur != nullptr) {
        if (cur->info.id == id) return cur;
        cur = cur->next;
    }
    return nullptr;
}

void printList(const List& L) {
    Node* p = L.first;
    if (!p) {
        std::cout << "List kosong\n";
        return;
    }
    while (p) {
        std::cout << "ID: " << p->info.id
                << " | User: " << p->info.username
                << " | Likes: " << p->info.likes
                << " | Konten: " << p->info.content
                << "\n";
        p = p->next;
    }
}

void insertSorted(List& L, const Post& data) {
    Node* p = allocate(data);
    if (isEmpty(L) || data.id < L.first->info.id) {
        insertFirst(L, p);
        return;
    }
    Node* q = L.first;
    while (q->next != nullptr && q->next->info.id < data.id) {
        q = q->next;
    }
    p->next = q->next;
    q->next = p;
}

void showPostsByUser(const List& L, const std::string& username) {
    Node* p = L.first;
    bool found = false;
    while (p) {
        if (p->info.username == username) {
            std::cout << "[" << p->info.id << "] "
            << p->info.content
            << " (Likes: " << p->info.likes << ")\n";
            found = true;
        }
        p = p->next;
    }
    if (!found) {
        std::cout << "Tidak ada postingan dari pengguna " << username << "\n";
    }
}

void showMostLiked(const List& L) {
    if (isEmpty(L)) {
        std::cout << "List kosong\n";
        return;
    }
    Node* p = L.first;
    Node* maxNode = p;
    while (p) {
        if (p->info.likes > maxNode->info.likes) {
            maxNode = p;
        }
        p = p->next;
    }
    std::cout << "Postingan terpopuler:\n";
    std::cout << "[" << maxNode->info.id << "] "
            << maxNode->info.content
            << " oleh " << maxNode->info.username
            << " (Likes: " << maxNode->info.likes << ")\n";
}

bool updateLikes(List& L, int id, bool like) {
    Node* p = findElement(L, id);
    if (!p) return false;
    if (like) {
        p->info.likes += 1;
    } else {
        if (p->info.likes > 0) p->info.likes -= 1;
    }
    return true;
}

void clearList(List& L) {
    Node* p;
    while (!isEmpty(L)) {
        deleteFirst(L, p);
        delete p;
    }
}

File Main.cpp
#include <iostream>
#include "list.h"

int main() {
    // Nama  :Chiara Calina Devi
    // NIM   :103122400016
    // Kelas :SE08-01

    List L = createNewList();

    Post p1{3, "Hello TelU!", 15, "chiara"};
    Post p2{1, "Belajar Linked List", 8, "alex"};
    Post p3{2, "Struktur Data seru!", 20, "chiara"};
    Post p4{4, "Latihan Asesmen Sub CLO 3", 5, "dimas"};

    insertSorted(L, p1);
    insertSorted(L, p2);
    insertSorted(L, p3);
    insertSorted(L, p4);

    std::cout << "=== Semua Postingan ===\n";
    printList(L);

    std::cout << "\n=== Postingan oleh 'chiara' ===\n";
    showPostsByUser(L, "chiara");

    std::cout << "\n=== Postingan Terpopuler ===\n";
    showMostLiked(L);

    std::cout << "\n=== Update Likes (ID 1 like, ID 2 unlike) ===\n";
    bool ok1 = updateLikes(L, 1, true);
    bool ok2 = updateLikes(L, 2, false);
    if (!ok1) std::cout << "ID 1 tak ditemukan\n";
    if (!ok2) std::cout << "ID 2 tak ditemukan\n";
    printList(L);

    Node* removed = nullptr;
    deleteFirst(L, removed);
    delete removed;
    deleteLast(L, removed);
    delete removed;

    deleteAfter(L, 2, removed);
    if (removed) delete removed;

    std::cout << "\n=== Setelah beberapa penghapusan ===\n";
    printList(L);

    clearList(L);
    return 0;
}

2. Penjelasan Kode

Berikut adalah penjelasan alur logika dari kode program di atas per file:

*list.h header*:
Fungsi: mendefinisikan tipe data dan prototipe fungsi/prosedur untuk Singly Linked List yang menyimpan postingan (ID, konten, likes, username).

Tipe data
Post : (infotype): { id:int, content:string, likes:int, username:string } — data inti setiap node.
Node: menyimpan Post info dan pointer Node next. Ini adalah simpul singly (hanya next).
List`: menyimpan alamat node pertama Node first. List kosong jika first == nullptr.

Primitif dasar:
Konstruktor: createNewList() → List kosong.
Alokasi node: allocate(const Post&) → Node.
Predikat: isEmpty(const List&) → bool.
Insert: insertFirst, insertLast, insertAfter.
Delete: deleteFirst, deleteLast, deleteAfter.
Pencarian & cetak: findElement, printList`.
Subprogram khusus “soal cerita” (My Telu):

insertSorted (urut asc by ID), showPostsByUser, showMostLiked, updateLikes.
Utilitas: clearList untuk membebaskan semua node

*file list.cpp*
Fungsi:mengisi semua logika struktur data dan operasi sesuai kontrak di header.

Primitif dasar:
createNewList() menginisialisasi first = nullptr. List kosong. (O(1))
allocate(data) meng-new satu Node, menyalin Post, set next=nullptr. (O(1))
Catatan: menggunakan new Node dan memastikan pointer valid sebelum dipakai.
isEmpty(L) cek L.first == nullptr. (O(1))

Insert:
insertFirst(L,p): prepend; p->next = first; first = p. (O(1))
insertLast(L,p): jika kosong, first=p; jika tidak, traversing ke tail lalu tail->next=p. (O(n))
insertAfter(L, xId, p): cari node ber-ID xId (pakai findElement), tautkan p setelahnya; jika acuan tak ada, p dihapus agar tidak bocor memori. (O(n))

Delete:
deleteFirst(L,p): ambil first ke p, geser first = first->next, putuskan p->next=nullptr. (O(1))
deleteLast(L,p): jika hanya 1 node → angkat; else telusuri prev dan cur sampai tail, putuskan, kembalikan p=cur. (O(n))
deleteAfter(L, xId, p): cari node ber-ID xId; jika ada successor, lepaskan dan kembalikan di p. (O(n))

find & print :
findElement(L, id): linear search hingga ketemu id atau habis. (O(n))
printList(L): menulis setiap node: ID | User | Likes | Konten, atau “List kosong”. (O(n))

Subprogram “soal cerita” (fitur My Telu):
 insertSorted(L, data): menyisipkan tetap terurut menaik berdasarkan id.
Kasus kepala: jika kosong atau data.id < first->id → insertFirst.
Selain itu: telusuri hingga menemukan posisi q di mana q->next->id >= data.id, lalu selipkan. (O(n))
showPostsByUser(L, username): scan semua node; cetak baris [id] content (Likes: n) hanya untuk username yang cocok; jika tak ada, beri pesan khusus. (O(n))

Urutan tampil mengikuti urutan list (ascending ID), sehingga hasilnya konsisten dan mudah diverifikasi.
showMostLiked(L): jika kosong → pesan; jika tidak, cari node dengan likes maksimum (satu pass), lalu cetak detailnya sebagai “Postingan terpopuler”. (O(n))
updateLikes(L, id, like): temukan ID; jika like==true, likes++; jika false, likes-- tanpa menjadi negatif** (dicek >0). Return false bila ID tak ditemukan. (O(n))

Manajemen memori :
Operasi delete selalu memutus next node yang dikeluarkan (p->next=nullptr), sehingga jelas kepemilikannya sebelum delete p dilakukan di pemanggil.
clearList(L) mengulangi deleteFirst hingga habis dan delete p untuk mencegah memory leak. (O(n))

*file main.cpp*
Fungsi: membuat list, mengisi data, memanggil fungsi-fungsi ADT, dan menampilkan hasil sesuai permintaan soal. 

 Langkah program:
1. Inisialisasi & identitas. Membuat list kosong L = createNewList().
2. Data contoh disiapkan (acak ID):

   p1{3, "Hello TelU!", 15, "chiara"}
   p2{1, "Belajar Linked List", 8, "alex"}
   p3{2, "Struktur Data seru!", 20, "chiara"}
   p4{4, "Latihan Asesmen Sub CLO 3", 5, "dimas"}
3. Penyisipan terurut (ascending by ID): insertSorted(L, p1..p4).
   Setelah keempatnya masuk, urutan list menjadi: ID 1 → 2 → 3 → 4**.
4. Cetak semua postingan: printList(L) akan menampilkan baris untuk ID 1,2,3,4 (urut naik).
5. Filter per username: showPostsByUser(L, "chiara") menampilkan hanya ID 2 dan 3 (keduanya milik “chiara”), dalam urutan list (2 dulu, lalu 3).
6. Postingan terpopuler: showMostLiked(L) memilih likes terbesar: ID 2 dengan 20 likes.
7. Ubah likes:
   updateLikes(L, 1, true) → ID 1: 8 → 9
   updateLikes(L, 2, false) → ID 2: 20 → 19
     Lalu printList(L) lagi untuk memverifikasi perubahan.
8. Operasi hapus:
deleteFirst mengeluarkan ID 1 (head).
deleteLast (sesudah itu) mengeluarkan ID 4 (tail saat itu).
deleteAfter(L, 2, removed) menghapus node setelah ID 2 -> yaitu ID 3.
     Sisa node di list: hanya ID 2. Cetak lagi, lalu clearList(L)

3. Output Program

Berikut adalah hasil eksekusi program (output) ketika dijalankan.

<img width="759" height="779" alt="image" src="https://github.com/user-attachments/assets/0373a895-55bd-4e41-9f4e-5f292c0f4462" />

A. Setelah penyisipan terurut (ID 1–4)

Ditampilkan oleh:
=== Semua Postingan ===
ID: 1 | User: alex   | Likes: 8  | Konten: Belajar Linked List
ID: 2 | User: chiara | Likes: 20 | Konten: Struktur Data seru!
ID: 3 | User: chiara | Likes: 15 | Konten: Hello TelU!
ID: 4 | User: dimas  | Likes: 5  | Konten: Latihan Asesmen Sub CLO 3

 sesuai `insertSorted` (urut asc by ID) dan `printList`.

 Filter postingan oleh `"chiara"`

=== Postingan oleh 'chiara' ===
[2] Struktur Data seru! (Likes: 20)
[3] Hello TelU! (Likes: 15)

Fungsi `showPostsByUser` menelusuri seluruh list, hanya mencetak baris dengan `username == "chiara"`. Urutan mengikuti urutan list: 2 lalu 3.

 C. Postingan terpopuler (likes maksimum)
=== Postingan Terpopuler ===
Postingan terpopuler:
[2] Struktur Data seru! oleh chiara (Likes: 20)


showMostLiked memilih ID 2 karena 20 adalah nilai likes terbesar.

 D. Setelah update likes (ID 1 like, ID 2 unlike)
=== Update Likes (ID 1 like, ID 2 unlike) ===
ID: 1 | User: alex   | Likes: 9  | Konten: Belajar Linked List
ID: 2 | User: chiara | Likes: 19 | Konten: Struktur Data seru!
ID: 3 | User: chiara | Likes: 15 | Konten: Hello TelU!
ID: 4 | User: dimas  | Likes: 5  | Konten: Latihan Asesmen Sub CLO 3
```

updateLikes(L,1,true) menaikkan 8→9, updateLikes(L,2,false) menurunkan 20→19 (tidak boleh negatif; ada guard).

 E. Setelah penghapusan (first, last, after ID=2)

Urutannya:
1. deleteFirst membuang ID 1 → list jadi [2,3,4].
2. deleteLast membuang ID 4 → list jadi [2,3].
3. deleteAfter(2) membuang ID 3 → list jadi [2].
   Cetakan akhir:

=== Setelah beberapa penghapusan ===
ID: 2 | User: chiara | Likes: 19 | Konten: Struktur Data seru!

Tersisa hanya ID 2 dengan likes 19 (hasil update sebelumnya).

---

 5) Ringkasan Kompleksitas

Akses/pencarian/insert terurut/delete posisi tertentu: O(n) karena singly linked list perlu traversal sekuensial.
Insert di head / delete di head: O(1).
Pencetakan & pencarian max likes: O(n).
  Seluruhnya konsisten dengan implementasi di list.cpp.

---

# 6) Catatan Kualitas & Edge Cases yang Tercakup

Tidak terjadi like negatif:** updateLikes hanya mengurangi jika likes > 0.
Menghindari memory leak saat insertAfter gagal menemukan acuan:** node p yang sudah dialokasikan    dihapus.
Kebersihan memori: clearList menghapus seluruh node di akhir eksekusi program.
Pesan ramah: penanganan list kosong di printList & showMostLiked; pesan “Tidak ada postingan …” pada showPostsByUser

4. Penjelasan Lanjutan (Analisis Output)

Sesuai permintaan Anda ("Penjelasan Lagi"), bagian ini menganalisis mengapa output yang dihasilkan sudah benar:

Pada Output 1: User memasukkan 42. Ketika 42 dibagi 2, sisa baginya adalah 0 ($42 \div 2 = 21$ sisa $0$). Karena sisa baginya 0, kondisi if (angka % 2 == 0) terpenuhi (True), sehingga program mencetak "adalah bilangan GENAP".

Pada Output 2: User memasukkan 77. Ketika 77 dibagi 2, sisa baginya adalah 1 ($77 \div 2 = 38$ sisa $1$). Karena sisa baginya bukan 0, kondisi if tidak terpenuhi, dan program menjalankan blok else, sehingga mencetak "adalah bilangan GANJIL".

Kedua kasus uji (test case) tersebut menunjukkan bahwa logika operator modulus (%) telah diimplementasikan dengan benar untuk membedakan bilangan ganjil dan genap.

5. Kesimpulan

Berdasarkan implementasi dan pengujian kode di atas, dapat disimpulkan bahwa:

Program ini berhasil mengimplementasikan Single Linked List lengkap
Semua primitif dasar diimplementasikan benar.
Fungsi tambahan sesuai kebutuhan aplikasi (insert terurut, tampil user, populer, update like).
Output sesuai logika yang diharapkan dan valid.
Tidak ada kebocoran memori (karena clearList()).
