#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include "test_framework.h"

static void StackSortedInsert(std::vector<int>& st, int key)
{
    /* Toggle between < and > for increasing vs decreating order,
     * may be use a functor here? or a comparator??
     */
    if(st.size() == 0 || st[0] >= key) {
        st.insert(st.begin(), key);
        return;
    }

    /*
     * Ugly hack to remove the front element of a vector, but works fine for now
     */
    int top = st[0];
    st.erase(st.begin());

    StackSortedInsert(st, key);

    st.insert(st.begin(), top);
}

static void StackSortHelper(std::vector<int>& st)
{
    if (st.size() == 0)
        return;

    /*
     * Ugly hack to remove the front element of a vector, but works fine for now
     */
    int top = st[0];
    st.erase(st.begin());

    StackSortHelper(st);

    StackSortedInsert(st, top);

    return;
}

/*
 * Using std::vector to implement stack related ops. Not ideal, but wanted
 * an iterable container.
 */
int StackSort(void *data)
{
    std::vector<int> st;
    st.push_back(12);
    st.push_back(1);
    st.push_back(15);
    st.push_back(7);
    st.push_back(10);

    StackSortHelper(st);
    for(auto it = st.begin(); it != st.end(); it++)
        std::cout << *it << " ";

    std::cout << std::endl;
    return TEST_SUCCESS;
}

static void StackReverseInsert(std::vector<int>& st, int key)
{
    if (st.size() == 0) {
        st.insert(st.begin(), key);
        return;
    }

    int top = st[0];
    st.erase(st.begin());

    StackReverseInsert(st, key);

    st.insert(st.begin(), top);
}

static void StackReverseHelper(std::vector<int>& st)
{
    if (st.size() == 0)
        return;

    int top = st[0];
    st.erase(st.begin());

    StackReverseHelper(st);

    StackReverseInsert(st, top);
}

int StackReverse(void* data)
{
    std::vector<int> st;
    st.push_back(12);
    st.push_back(1);
    st.push_back(15);
    st.push_back(7);
    st.push_back(10);

    for(auto it = st.begin(); it != st.end(); it++)
        std::cout << *it << " ";
    std::cout << std::endl;

    StackReverseHelper(st);

    std::cout << "Reversed stack: " << std::endl;

    for(auto it = st.begin(); it != st.end(); it++)
        std::cout << *it << " ";
    std::cout << std::endl;

    return TEST_SUCCESS;
}

const TestFamily* stack_init()
{
    TestFamily *testFamily = new TestFamily("stack", static_cast<int>(10));

    TEST_DEF(stack_sort, StackSort);
    TEST_DEF(stack_reverse, StackReverse);

    return testFamily;
}
