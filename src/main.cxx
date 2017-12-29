#include <iostream>
#include <string>
#include "test_framework.h"
#include "test_groups.h"

typedef std::map<std::string, const TestFamily*> test_families;

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

