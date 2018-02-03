#include <iostream>
#include <string>
#include "test_framework.h"

int simple_array_test(void *data)
{
    std::cout << "This is simple test case." << std::endl;
    return TEST_SUCCESS;
}

const TestFamily* arrays_init()
{
    TestFamily *testFamily = new TestFamily("arrays", static_cast<int>(10));

    TEST_DEF(test1, simple_array_test);

    return testFamily;
}
