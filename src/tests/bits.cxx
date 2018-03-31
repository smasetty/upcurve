#include <iostream>
#include <map>
#include <string>
#include "test_framework.h"

/*
 * Prints the binary form of a decimal number
 */
static void PrintBinaryRepresentation(unsigned int num)
{
    unsigned int number = 0;

    while (num) {
        number = (number * 10) + (num % 2);
        num /= 2;
    }

    std::cout << number << std::endl;
}

/*
 * A program to reverse the bits of a given number
 */
int ReverseBits(void* data)
{

    unsigned int number = 48;
    unsigned int reverseNumber = 0;
    int numBits = sizeof(int) * 8;

    /* Print the binary representation of the input number */
    PrintBinaryRepresentation(number);

    for (int i = 0; i < numBits; i++)
        if (number & (1 << i))
            reverseNumber |= ( 1 << ((numBits - 1)  - i));

    PrintBinaryRepresentation(reverseNumber);

    return TEST_SUCCESS;
}

const TestFamily* bits_init()
{
    TestFamily *testFamily = new TestFamily("bits", static_cast<int>(10));

    TEST_DEF(reverse_bits, ReverseBits);

    return testFamily;
}
