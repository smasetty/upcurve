#include <iostream>
#include <string>
#include <iomanip>
#include "test_framework.h"
#include "trie.h"

int TrieHelper(void *data)
{
    Trie testTrie;

    testTrie.InsertWord(std::string("Test"));
    testTrie.InsertWord(std::string("Ten"));
    testTrie.InsertWord(std::string("Sharat"));

    if (testTrie.SearchWord(std::string("Sharat")))
        std::cout << "The word " << std::string("Sharat")
            << " " << "exists\n";
    else
        std::cout << "The word" << std::string("Sharat")
            << " " << "does not exist\n";

    testTrie.DeleteWord(std::string("Sharat"));

    if (testTrie.SearchWord(std::string("Sharat")))
        std::cout << "The word " << std::string("Sharat")
            << " " << "exists\n";
    else
        std::cout << "The word " << std::string("Sharat")
            << " " << "does not exist\n";
    return TEST_SUCCESS;
}

const TestFamily* strings_init()
{
    TestFamily *testFamily = new TestFamily("strings", static_cast<int>(10));

    TEST_DEF(trie_helper, TrieHelper);

    return testFamily;
}
