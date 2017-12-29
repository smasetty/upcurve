#ifndef TEST_FW_H
#define TEST_FW_H

#include <iostream>
#include <list>
#include <iterator>
#include <map>

#define ARRAY_SIZE(a) sizeof(a)/sizeof(a[0])

typedef int (*testFunction)(void *data);

struct Test {
    std::string testName;
    void *data;
    int flags;
    int status;
    testFunction testFunc;
};

#define STR_VALUE(str) #str
#define FUNCTION_NAME(str) STR_VALUE(str)

#define TEST_DEF(name, func) \
    do { \
        struct Test *testInstance = new Test; \
        std::string base = FUNCTION_NAME(name); \
        testInstance->testFunc = func; \
        testInstance->testName.assign(base); \
        testFamily->AddTest(testInstance); \
    }while(0); \

class TestFamily {
public:
    explicit TestFamily(std::string name, int maxTests): familyName(name) ,
        maxTests(maxTests) {};

    void ShowTests() const{
        for (auto i = testList.begin(); i != testList.end(); ++i) {
            std::cout << "test case: " << (*i)->testName << std::endl;
        }
    }

    const std::string& GetFamilyName() const { return familyName; }

    void AddTest(struct Test *test){
        if(!test)
            return;

        testList.push_back(test);
    }
    
    void RunAllTests() const {
        for (auto i = testList.begin(); i != testList.end(); ++i) {
            std::cout << "Running Test: " << (*i)->testName << std::endl; 
            std::cout << (*i)->testFunc(nullptr) << std::endl;
        }
    }

    ~TestFamily() {
        std::cout << "Deleting family object" << std::endl; 
    }; // A more thorough cleanup is required here

private:
    TestFamily(const TestFamily&);
    TestFamily operator=(const TestFamily &);
    std::list<const struct Test*> testList;
    int maxTests;
    std::string familyName;
};


#endif /* ifndef TEST_FW_H */
