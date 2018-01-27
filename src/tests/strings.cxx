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

static void GenerateKMPPatternData(const std::string& pattern,
        int *tempArray)
{
    int i = 1, j = 0;

    tempArray[0] = 0;

    while (i < pattern.length()) {
        if (pattern[i] == pattern[j]) {
            tempArray[i++] = j + 1;
            j++;
        }
        else if (pattern[i] != pattern[j]) {
            if (j == 0) {
                tempArray[i++] = 0;
                continue;
            }

            j = tempArray[--j];
        }
    }
}

static bool KMPSubstringSearch(const std::string& pattern,
        const std::string& input, const int *temp)
{
    int i = 0, j = 0;
    while (i < input.length()) {
        if (input[i] == pattern[j]) {
            i++;
            j++;

            if(j == pattern.length()) {
                std::cout << "We found a match at index " <<
                    i - pattern.length() <<  std::endl;
                return true;
            }
        } else {
            if (j == 0) {
                i++;
                continue;
            } else {
                j = temp[--j];
            }
        }
    }

    std::cout << "No pattern match found :-(" << std::endl;

    return false;
}

int KMPSearchSuccess(void *data) 
{
    //std::string pattern("acacabacacabacacac");
    std::string pattern("abcaby");
    std::string input("abxabcabcaby");
    int* temp = new int[pattern.length()];

    GenerateKMPPatternData(pattern, temp);

    auto status = KMPSubstringSearch(pattern, input, temp); 

    delete temp;

    if (status == true)
        return TEST_SUCCESS;
    else
        return TEST_FAILURE;
}

int KMPSearchFail(void *data) 
{
    std::string pattern("abcaby");
    std::string input("abxabcabcaba");
    int* temp = new int[pattern.length()];

    GenerateKMPPatternData(pattern, temp);

    auto status = KMPSubstringSearch(pattern, input, temp); 

    delete temp;

    if (status == false)
        return TEST_SUCCESS;
    else
        return TEST_FAILURE;
}

const TestFamily* strings_init()
{
    TestFamily *testFamily = new TestFamily("strings", static_cast<int>(10));

    TEST_DEF(trie_helper, TrieHelper);
    TEST_DEF(kmp_search_success, KMPSearchSuccess);
    TEST_DEF(kmp_search_fail, KMPSearchFail);

    return testFamily;
}
