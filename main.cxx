#include <iostream>
#include <string>
#include "test_framework.h"

typedef std::map<std::string, const TestFamily*> test_families;

typedef const TestFamily* (*InitFunction)(void);

extern const TestFamily* graphs_init(void);

struct TestGroups {
    const char *name;
    InitFunction init;
} groups[] = 
{
    {.init = graphs_init},
};

int simple_test(void *data)
{
    std::cout << "This is very simple test case." << std::endl;
    return 0;
}

const TestFamily* graphs_init()
{
    TestFamily *testFamily = new TestFamily("graphs", static_cast<int>(10));
    
    TEST_DEF(FIRST_TEST_CASE, simple_test);

    return testFamily;
}

int main(int argc, char *argv[])
{
    //process command line arguments
    
    test_families families;

    for (int i = 0; i < ARRAY_SIZE(groups); i++) {
        
        const TestFamily *family;

        family = groups[i].init();
        family->ShowTests();
        family->RunAllTests();

        groups[i].name = family->GetFamilyName().c_str();

        families[groups[i].name] = family;
    }

    // Fix the leaks here
    
    return 1;
}

