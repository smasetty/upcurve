#include <iostream>
#include "tree.h"

struct Node {
    int key;
    struct Node* next;
public:
    Node(int key): key{key}, next{nullptr} {};
};

struct NodeX {
    int key;
    struct NodeX* next;
    struct NodeX* down;
public:
    NodeX(int key): key{key}, next{nullptr}, down{nullptr} {};
};

struct Node* GenerateListEven();
struct Node* GenerateListOdd();
struct Node* GenerateListLoop();
struct Node* GenerateListLoop1();
struct Node* GenerateListNum1();
struct Node* GenerateListNum2();
struct Node* GenerateListDen1();
struct Node* GenerateListDen2();
struct NodeX* GenerateListNotFlat();
void PrintList(struct Node* head);
void PrintList(struct NodeX* head);
void DeleteList(struct Node* head);
void ReverseList(struct Node** headref);
struct Node* ReverseListAltK(struct Node* head, int& k);
struct Node* ReverseListK(struct Node* head, int& k);
void ReverseListRecur(struct Node* current, struct Node* prev,
        struct Node** headref);
bool DetectLoop(struct Node* head);
/*
 * Detect and remove a loop in a linked listi
 */
void DetectAndRemoveLoop(struct Node* head);
struct Node* LLAdd(struct Node* first, struct Node* second);
struct Node* LLAddSameLength(struct Node* first, struct Node* second,
        int &carry);
int LLLength(struct Node* head);
