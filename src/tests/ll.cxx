#include <iostream>
#include <unordered_map>
#include <list>
#include "ll_helper.h"
#include "test_framework.h"

int LLReverse(void *data)
{
    struct Node *head = GenerateListEven();
    PrintList(head);
    std::cout<< "Iterative List Reverse" << std::endl;
    ReverseList(&head);
    PrintList(head);
    DeleteList(head);
    return TEST_SUCCESS;
}

int LLReverseRecursive(void *data)
{
    struct Node *head = GenerateListOdd();
    PrintList(head);
    std::cout<< "Tail Recursive List Reverse" << std::endl;
    ReverseListRecur(head, nullptr, &head);
    PrintList(head);
    DeleteList(head);
    return TEST_SUCCESS;
}

int DetectLoopTest(void *data)
{
    struct Node* head = GenerateListLoop();
    if (DetectLoop(head)) {
        std::cout << "The list has a loop" << std::endl;
        return TEST_SUCCESS;
    }
    else {
        std::cout << "The list does not have a loop" << std::endl;
        return TEST_FAILURE;
    }

    DeleteList(head);
    return TEST_SKIPPED;
}

int LLReverseK(void *data)
{
    struct Node* head =  GenerateListEven();
    if (!head)
        return TEST_SKIPPED;
    PrintList(head);

    int k = 3;
    std::cout<< "Reversing the list in groups of size " <<  k << std::endl;
    head = ReverseListK(head, k);
    PrintList(head);

    return TEST_SUCCESS;
}

int LLReverseAltK(void *data)
{
    struct Node* head =  GenerateListEven();
    if (!head)
        return TEST_SKIPPED;
    PrintList(head);

    int k = 3;
    std::cout<< "Reversing the list in alternate groups of size " <<  k << std::endl;
    head = ReverseListAltK(head, k);
    PrintList(head);

    return TEST_SUCCESS;
}

int DetectRemoveLoopTest(void *data)
{
    struct Node* head = GenerateListLoop1();
    if(!head)
        return TEST_SKIPPED;


    DetectAndRemoveLoop(head);
    PrintList(head);
    DeleteList(head);

    return TEST_SUCCESS;
}

int LLAdd1(void *data)
{
    struct Node* first = GenerateListNum1();
    struct Node* second = GenerateListDen1();

    struct Node* result = LLAdd(first, second);
    PrintList(result);

    DeleteList(result);
    DeleteList(first);
    DeleteList(second);

    return TEST_SUCCESS;
}

int LLAdd2(void *data)
{
    struct Node* first = GenerateListNum1();
    struct Node* second = GenerateListDen1();
    int carry = 0;

    struct Node* result = LLAddSameLength(first, second, carry);
    PrintList(result);
    std::cout << carry << std::endl;

    DeleteList(result);
    DeleteList(first);
    DeleteList(second);

    return TEST_SUCCESS;
}

struct NodeX* SortedMerge(struct NodeX* a, struct NodeX* b)
{
    /*
     * If one of the list is empty, return the other one
     */
    if (!a)
        return b;

    /*
     * If one of the list is empty, return the other one
     */
    if (!b)
        return a;

    struct NodeX* result = nullptr;

    /*
     * Add the Node with the smaller key first and recurse down both the lists
     */
    if (a->key < b->key) {
        result = a;
        result->down = SortedMerge(a->down, b);
    }
    else {
        result = b;
        result->down = SortedMerge(a, b->down);
    }

    return result;
}

struct NodeX* Flatten(struct NodeX* head)
{
    if(!head || !head->next)
        return head;

    struct NodeX* rest = Flatten(head->next);

    return SortedMerge(head, rest);
}

int LLFlat(void* data)
{
    struct NodeX* head = GenerateListNotFlat();

    struct NodeX* result = Flatten(head);
    PrintList(result);

    return TEST_SUCCESS;
}

#define CACHE_SIZE 3
void LRUCacheRefer(std::list<int>& list,
        std::unordered_map<int, std::list<int>::iterator>& hash, int key)
{
    /*
     * hash gives us faster access times, first search if the key is present
     * in the cache.
     */
    if (hash.find(key) == hash.end()) {
        /*
         * If the key is not present and the cache size is full, then remove
         * the last element which is the least recently used from both the list
         * and the hash.
         */
        if (list.size() == CACHE_SIZE) {
            int last = list.back();
            list.pop_back();
            hash.erase(last);
        }
    }
    else {

        /*
         * If the key is already present in the cache, then just remove it from
         * the current location and move it to the front of the list
         */
        list.erase(hash[key]);
    }

    /*
     * Add the key to the front of the list.
     */
    list.push_front(key);
    hash[key] = list.begin();

    /*
     * Print for debug purposes, not strictly needed
     */
    for (auto it = list.begin(); it != list.end(); it++)
        std::cout << *it << " ";
    std::cout << std::endl;
}

int LRUCache(void* data)
{
    std::list<int> dq;
    std::unordered_map<int, std::list<int>::iterator> hash;

    LRUCacheRefer(dq, hash, 1);
    LRUCacheRefer(dq, hash, 2);
    LRUCacheRefer(dq, hash, 3);
    LRUCacheRefer(dq, hash, 4);
    LRUCacheRefer(dq, hash, 1);
    LRUCacheRefer(dq, hash, 2);
    LRUCacheRefer(dq, hash, 5);
    LRUCacheRefer(dq, hash, 1);
    LRUCacheRefer(dq, hash, 2);
    LRUCacheRefer(dq, hash, 3);
    LRUCacheRefer(dq, hash, 5);

    return TEST_SUCCESS;
}

bool IsListPalindromeHelper(struct Node** left, struct Node* right)
{
    if (!right)
        return true;

    if (!IsListPalindromeHelper(left, right->next))
        return false;

    bool isPal = (*left)->key == right->key;

    *left = (*left)->next;

    return isPal;
}

int IsListPalindrome(void* data)
{
    struct Node* head = GenerateListOdd();

    bool isPal = IsListPalindromeHelper(&head, head);

    if (isPal)
        std::cout << "The given list is a palindrome" << std::endl;
    else
        std::cout << "The given list is not a palindrome" << std::endl;

    return TEST_SUCCESS;
}

int CloneList(void* data)
{
    std::unordered_map<struct NodeR*, struct NodeR*> map;
    struct NodeR* head = GenerateListRandom();

    /*
     * Print the original list here along with the random pointers
     */
    PrintList(head);
    std::cout << std::endl;

    struct NodeR* origCurr = head;

    /*
     * First create a map of nodes from original to cloned lists
     */
    while(origCurr) {
        map[origCurr] = new NodeR(origCurr->key);
        origCurr = origCurr->next;
    }

    origCurr = head;

    /*
     * recreate next and random pointers for the cloned list  using the mapping
     * created above
     */
    while(origCurr) {
        struct NodeR* cloneCurr = map[origCurr];
        cloneCurr->next = map[origCurr->next];
        cloneCurr->random = map[origCurr->random];
        origCurr = origCurr->next;
    }

    /*
     * Print the cloned list here along with the random pointers
     */
    PrintList(map[head]);
    std::cout << std::endl;

    return TEST_SUCCESS;
}

void Swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int PairSwap(void* data)
{
    struct Node* head = GenerateListEven();
    PrintList(head);

    struct Node* curr = head;

    while(curr != nullptr && curr->next != nullptr) {
        Swap(&curr->key, &curr->next->key);
        curr = curr->next->next;
    }
    PrintList(head);

    return TEST_SUCCESS;
}

const TestFamily* ll_init()
{
    TestFamily *testFamily = new TestFamily("ll", static_cast<int>(10));

    TEST_DEF(ll_reverse, LLReverse);
    TEST_DEF(ll_reverse_recur, LLReverseRecursive);
    TEST_DEF(ll_reverse_k, LLReverseK);
    TEST_DEF(ll_reverse_alt_k, LLReverseAltK);
    TEST_DEF(detect_loop, DetectLoopTest);
    TEST_DEF(detect_remove_loop, DetectRemoveLoopTest);
    TEST_DEF(ll_add_1, LLAdd1);
    TEST_DEF(ll_add_2, LLAdd2);
    TEST_DEF(ll_flat, LLFlat);
    TEST_DEF(lru_cache, LRUCache);
    TEST_DEF(is_list_palindrome, IsListPalindrome);
    TEST_DEF(clone_list, CloneList);
    TEST_DEF(pair_swap, PairSwap);

    return testFamily;
}
