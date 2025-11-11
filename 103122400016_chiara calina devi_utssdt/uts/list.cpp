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
