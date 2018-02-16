#include <iostream>
#include "test_framework.h"
#include "backtrace.h"

int Subsets(void *data) {
    Subset test(4);
    test.GenerateSubsets();
    return TEST_SUCCESS;
}

const TestFamily* backtrack_init()
{
    TestFamily *testFamily = new TestFamily("backtrack", static_cast<int>(10));

    TEST_DEF(subsets, Subsets);

    return testFamily;
}
