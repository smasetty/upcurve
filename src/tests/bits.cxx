#include <iostream>
#include <string>
#include "test_framework.h"

const TestFamily* bits_init()
{
    TestFamily *testFamily = new TestFamily("bits", static_cast<int>(10));

    return testFamily;
}
