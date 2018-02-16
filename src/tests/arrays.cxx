#include <iostream>
#include <string>
#include <vector>
#include "test_framework.h"

/*
 * This is a simple interpretation of Kadane's algorithm
 */
int LargestSum(void *data)
{
    std::vector<int> arr = {-2, -3, 4, -1, -2, 1, 5, -3};
    int maxEndingHere = 0;
    int maxCurrent = 0;
    int start = 0;
    int end = 0;
    int s = 0;

    for (int i = 0; i < arr.size(); i++) {
        maxEndingHere += arr[i];

        if (maxEndingHere < 0) {
            maxEndingHere = 0;
            s++;
        }
        else if (maxCurrent < maxEndingHere) {
            maxCurrent = maxEndingHere;
            start = s;
            end = i;
        }
    }
    
    std::cout << "Largest Sum Contiguous SubArray " << maxCurrent << std::endl;

    for (int i = start; i <= end; i++)
        std::cout << arr[i] << " ";
    std::cout << std::endl;

    return TEST_SUCCESS;
}

/*
 * Replace all zeros in an input number to  '5'
 */

int ReplaceZerosHelper(int num)
{
    if (num == 0)
        return 0;

    int digit = num % 10;
    if (digit == 0)
        digit = 5;

    return ReplaceZerosHelper(num / 10) * 10 + digit;

}

int ReplaceZeros(void* data)
{
    int testNum = 102030;

    std::cout << "original number: " << testNum << " " << "modified number: " <<
        ReplaceZerosHelper(testNum) << std::endl;
    
    return TEST_SUCCESS;
}

const TestFamily* arrays_init()
{
    TestFamily *testFamily = new TestFamily("arrays", static_cast<int>(10));

    TEST_DEF(largest_sum, LargestSum);
    TEST_DEF(replaces_zeros, ReplaceZeros);

    return testFamily;
}
