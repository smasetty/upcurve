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

/*
 * Find the next greater element for each element in the array. Use the stack
 * to implement a O(n) solution for the problem.
 */
int NextGreaterElement(void* data)
{
    std::vector<int> arr = {13, 7, 6, 12};
    std::stack<int> s;

    s.push(arr[0]);

    for (int i = 1; i < arr.size(); i++) {
        int next = arr[i];

        if (!s.empty()) {
            int current = s.top();
            s.pop();

            /*
             * For all the elements for which current item is less than length
             * the next item becomes the next greater element for the current
             * item. Keep popping all smaller elements as the next is the NGE
             * for all those popped items.
             */
            while(current < next) {
                std::cout << current << " -> " << next << std::endl;
                current = s.top();
                s.pop();
            }

            if (current > next)
                s.push(current);
        }

        /*
         * Push the next element so we can find the next element in the list
         */
        s.push(next);
    }

    int current = 0;

    /*
     * For all the remainder of items in the stack, there is no NGE, so print
     * -1 for those items.
     */
    while(!s.empty()) {
        current = s.top();
        s.pop();
        std::cout << current << " -> " << "-1" << std::endl;
    }

    return TEST_SUCCESS;
}

bool isMatchingParan(char char1, char char2)
{
    if (char1 == '{' && char2 == '}')
        return true;
    else if (char1 == '[' && char2 == ']')
        return true;
    else if (char1 == '(' && char2 == ')')
        return true;

    return false;
}

bool MatchingParanHelper(std::string testString)
{
    std::stack<char> s;
    int i = 0;

    while(testString[i]) {
        char inputChar = testString[i];
        std::cout << inputChar;

        if (inputChar == '(' || inputChar == '[' || inputChar == '{') 
            s.push(inputChar);

        else if (inputChar == ')' || inputChar == ']' || inputChar == '}') {
            if (s.empty())
                return false;

            char char1 = s.top();
            s.pop();

            if (!isMatchingParan(char1, inputChar))
                return false;
        }
        i++;
    }

    if (!s.empty())
        return false;
    else
        return true;
}

int MatchingParan(void* data)
{
    std::string testString("({[]})");

    if (MatchingParanHelper(testString))
        std::cout << " Input String has matching paranthesis" << std::endl;
    else
        std::cout << " Input String has no matching paranthesis" << std::endl;

    return TEST_SUCCESS;
}

const TestFamily* stack_init()
{
    TestFamily *testFamily = new TestFamily("stack", static_cast<int>(10));

    TEST_DEF(stack_sort, StackSort);
    TEST_DEF(stack_reverse, StackReverse);
    TEST_DEF(next_greater, NextGreaterElement);
    TEST_DEF(matching_paran, MatchingParan);

    return testFamily;
}
