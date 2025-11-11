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
