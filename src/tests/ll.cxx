#include <iostream>
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

    return testFamily;
}
