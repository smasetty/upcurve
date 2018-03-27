#include <iostream>
#include "ll_helper.h"

struct Node* GenerateListEven()
{
    struct Node *head = new Node(1);
    head->next = new Node(2);
    head->next->next = new Node(3);
    head->next->next->next = new Node(4);
    head->next->next->next->next = new Node(5);
    head->next->next->next->next->next = new Node(6);

    return head;
}

struct Node* GenerateListOdd()
{
    struct Node *head = new Node(1);
    head->next = new Node(2);
    head->next->next = new Node(3);
    head->next->next->next = new Node(2);
    head->next->next->next->next = new Node(1);

    return head;
}

struct Node* GenerateListLoop()
{
    struct Node *head = new Node(1);
    head->next = new Node(2);
    head->next->next = new Node(3);
    head->next->next->next = new Node(4);
    head->next->next->next->next = new Node(5);
    head->next->next->next->next->next = head;

    return head;
}

/*
 * Generates a list which is not flat in structure, but its sorted in every
 * direction
 */
struct NodeX* GenerateListNotFlat()
{
    struct NodeX* head = new NodeX(5);
    head->down = new NodeX(7);
    head->down->down = new NodeX(8);
    head->down->down->down = new NodeX(30);

    struct NodeX* head2 = new NodeX(10);
    head2->down = new NodeX(20);

    struct NodeX* head3 = new NodeX(19);
    head3->down = new NodeX(22);
    head3->down->down = new NodeX(50);

    struct NodeX* head4 = new NodeX(28);
    head4->down = new NodeX(35);
    head4->down->down = new NodeX(40);
    head4->down->down->down = new NodeX(45);

    head->next = head2;
    head2->next = head3;
    head3->next = head4;

    return head;
}

/*
 * Generate a linked list loop like the following
 *  1->2->3
 *     ^  ^
 *     |  |
 *     5<-4
 */
struct Node* GenerateListLoop1()
{
    struct Node *head = new Node(1);
    head->next = new Node(2);
    head->next->next = new Node(3);
    head->next->next->next = new Node(4);
    head->next->next->next->next = new Node(5);
    head->next->next->next->next->next = head->next;

    return head;
}

struct NodeR* GenerateListRandom()
{
    struct NodeR *head = new NodeR(1);
    head->next = new NodeR(2);
    head->next->next = new NodeR(3);
    head->next->next->next = new NodeR(4);
    head->next->next->next->next = new NodeR(5);

    /* setup the random pointers */
    head->random = head->next->next;
    head->next->random = head->next->next->next;
    head->next->next->random = head->next->next->next->next;
    head->next->next->next->random = head->next->next->next->next->next;
    head->next->next->next->next->random = head->next;

    return head;
}

void DeleteList(struct Node* head)
{
    struct Node* current = head;

    while(current != nullptr) {
        struct Node *temp = current;
        current = current->next;
        delete temp;
    }
}

void PrintList(struct Node* head)
{
    struct Node* current = head;

    while(current != nullptr) {
        std::cout<< current->key << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

void PrintList(struct NodeX* head)
{
    struct NodeX* current = head;

    while(current != nullptr) {
        std::cout<< current->key << " ";
        current = current->down;
    }
    std::cout << std::endl;
}

void PrintList(struct NodeR* head)
{
    struct NodeR* current = head;

    while(current) {
        struct NodeR* temp = current->random;
        std::cout << current->key << " -- r: " << (temp ? temp->key : -1);
        std::cout << std::endl;
        current = current->next;
    }
    std::cout << std::endl;
}

void ReverseList(struct Node** headref)
{
    struct Node* prev = nullptr;
    struct Node* current = *headref;
    struct Node* next;

    while (current != nullptr) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    *headref = prev;
}

void ReverseListRecur(struct Node* current, struct Node* prev,
        struct Node** headref)
{
    if (!current->next) {
        *headref = current;

        current->next = prev;
        return;
    }

    struct Node* next = current->next;
    current->next = prev;
    ReverseListRecur(next, current, headref);
}

bool DetectLoop(struct Node* head)
{
    struct Node* slow = head;
    struct Node* fast = head;

    while(slow && fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast)
            return 1;
    }
    return 0;
}

/*
 * A function to reverse a linked list in groups of given size
 * Ex:  1->2->3->4->5->6->7 and k = 3
 * Ans: 3->2->1->6->5->4->7
 */
struct Node* ReverseListK(struct Node* head, int& k)
{
    struct Node* prev = nullptr;
    struct Node* current = head;
    struct Node* next = nullptr;
    int count = 0;

    while(current != nullptr && count < k) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
        count++;
    }

    /*
     * At this point the current and next pointer point to the k+1th node
     * and head points to the kth node
     */
    if (next != nullptr)
        head->next = ReverseListK(next, k);

    return prev;
}

/*
 * A function to reverse alternate groups of given size
 * Ex:  1->2->3->4->5->6->7 and k = 2
 * Ans: 2->1->3->4->6->5->7
 */
struct Node* ReverseListAltK(struct Node* head, int& k)
{
    struct Node* prev = nullptr;
    struct Node* current = head;
    struct Node* next = nullptr;
    int count = 0;

    while(current != nullptr && count < k) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
        count++;
    }

    /*
     * At this point the current and next pointer point to the k+1th node
     * and head points to the kth node.
     * Make head's next point to the k+1th node
     */
    if (current != nullptr)
        head->next = current;

    /* Skip the next k nodes */
    count = 0;
    while(current!= nullptr && count < (k - 1)) {
        current = current->next;
        count++;
    }

    /* current now points to the 2k node, recurse for the next 2k nodes */
    if (current->next)
        current->next = ReverseListAltK(current->next, k);

    return prev;
}

/*
 * Detect and remove a loop in a linked listi
 * Basic idea is to
 * a) find the node where slow and fast meet
 * b) start ptr1 from head and ptr2 from the node from (a)
 * c) move both the pointers at the same speed, they will meet
 * at the start of the loop node.
 *
 * reasoning:
 * m + n*x + k = 2 * (m + n*y + k)
 * then after solving the equation: m + k = (x - 2y) * n
 * where m is the distance of the loop start from head
 * n is the length of the loop
 * k is the distance of the slow, fast meet from the loop start node
 * x and y are the number of times the slow and fast loop through the loop.
 */
void DetectAndRemoveLoop(struct Node* head)
{
    struct Node* slow = head;
    struct Node* fast = head;

    while(slow && fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {

            std::cout << "we found a loop that can be removed" << std::endl;
            break;
        }
    }

    slow = head;

    /* Stop at the node just before the loop start node */
    while(slow->next != fast->next) {
        slow = slow->next;
        fast = fast->next;
    }

    std::cout << fast->key << std::endl;
    fast->next = nullptr;
}

struct Node* GenerateListNum1()
{
    struct Node *head = new Node(5);
    head->next = new Node(6);
    head->next->next = new Node(3);

    return head;
}


struct Node* GenerateListDen1()
{
    struct Node *head = new Node(8);
    head->next = new Node(4);
    head->next->next = new Node(2);

    return head;
}

struct Node* GenerateListNum2()
{
    struct Node *head = new Node(7);
    head->next = new Node(5);
    head->next->next = new Node(9);
    head->next->next->next = new Node(4);
    head->next->next->next->next = new Node(6);

    return head;
}


struct Node* GenerateListDen2()
{
    struct Node *head = new Node(8);
    head->next = new Node(4);

    return head;
}

/*
 * Add two numbers represented by linked lists
 */
struct Node* LLAdd(struct Node* first, struct Node* second)
{
    struct Node* temp;
    int carry= 0, sum = 0;
    struct Node *result = nullptr, *prev = nullptr;

    while(first != nullptr || second != nullptr) {
        int num = first? first->key: 0;
        int den = second? second->key: 0;

        sum = num + den + carry;

        if (sum >= 10) {
            carry = 1;
            sum %= 10;
        } else
            carry = 0;

        temp = new Node(sum);

        if (result == nullptr)
            result = temp;
        else
            prev->next = temp;

        prev = temp;

        if (first) first = first->next;
        if (second) second = second->next;
    }

    if (carry)
        temp->next = new Node(carry);

    return result;
}


int LLLength(struct Node* head)
{
    struct Node* current = head;
    int count = 0;

    while(current != nullptr) {
        current = current->next;
        count++;
    }

    return count;
}

static void SwapPtr(struct Node **a, struct Node** b)
{
    struct Node* temp = *a;
    *a = *b;
    *b = temp;
}

/*
 * This addition routine with linked lists is how humans add on paper
 */
struct Node* LLAddSameLength(struct Node* first, struct Node* second,
        int &carry)
{
    struct Node* result;
    int sum = 0;

    /*
     * Since the lists are of the same length, checking
     * any of the two pointers would suffice
     */
    if (!first)
        return nullptr;

    result = new Node(0);
    result->next = LLAddSameLength(first->next, second->next, carry);

    sum = first->key + second->key + carry;

    if (sum >= 10) {
        sum %= 10;
        carry = 1;
    }
    else
        carry = 0;

    result->key = sum;

    return result;
}

