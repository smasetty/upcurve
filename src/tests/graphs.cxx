#include <iostream>
#include <string>
#include "test_framework.h"

int simple_test(void *data)
{
    std::cout << "This is very simple test case." << std::endl;
    return 0;
}

const TestFamily* graphs_init()
{
    TestFamily *testFamily = new TestFamily("graphs", static_cast<int>(10));
    
    TEST_DEF(first_sample_test, simple_test);

    return testFamily;
}
