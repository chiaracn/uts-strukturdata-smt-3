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
