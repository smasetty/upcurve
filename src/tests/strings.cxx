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

    delete[] temp;

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

    delete[] temp;

    if (status == false)
        return TEST_SUCCESS;
    else
        return TEST_FAILURE;
}

#define VECTOR_LENGTH 7
#define NUM_DIRECTIONS 8

static inline bool InBounds(int i, int j)
{
    return (i >=0 && i < VECTOR_LENGTH) && (j >= 0 && j < VECTOR_LENGTH); 
}

bool SearchWordInMatrixUtil(const char array[][VECTOR_LENGTH],
        std::string& word)
{
    auto wordLen = word.length();
    int x_dir[NUM_DIRECTIONS] =  { 1, 1, 0, -1, -1, -1, 0, 1 };
    int y_dir[NUM_DIRECTIONS] =  { 0, 1, 1, 1, 0, -1, -1, -1 };

    //Iterate over all possible array values
    for (int i = 0; i < VECTOR_LENGTH; i++) {
        for (int j = 0; j < VECTOR_LENGTH; j++) {
            // Search in all the possible directions, there are 8 possible
            // directions, make sure to not cross the array bounds. 
            for (int dir = 0; dir < NUM_DIRECTIONS; dir++) {
                int x = i;
                int y = j;
                int k = 0;

                // Compare the actual string here
                for (; k < wordLen; k++) {
                    
                    if (!InBounds(x, y))
                        break;

                    if (array[x][y] != word[k])
                        break;
                    else {
                        x = x + x_dir[dir];
                        y = y + y_dir[dir];
                    }
                }

                if (k == wordLen) {
                    std::cout << "The word " << word << " is at " << i << ", " << j << std::endl; 
                    return true;
                }
            }
        }
    }
    std::cout << "The word " << word << " is not present" << std::endl;
    return false;
}

int SearchWordInMatrix(void *data)
{
    const char array_test[VECTOR_LENGTH][VECTOR_LENGTH] = {
        {'a', 'b', 'v', 'k', 'r', 'v', 'p'},
        {'a', 'i', 'o', 'k', 'r', 'a', 'p'},
        {'a', 'k', 'v', 'n', 'r', 'n', 'o'},
        {'a', 'e', 'v', 'k', 'e', 'v', 'p'},
        {'a', 'b', 'v', 'k', 'r', 't', 'p'},
        {'a', 'b', 'v', 'k', 'a', 'v', 'p'},
        {'a', 'b', 'v', 'k', 't', 'v', 'p'},
    };
    std::string searchString("krap");

    SearchWordInMatrixUtil(array_test, searchString);

    searchString.erase();
    searchString.assign("Sharat");

    SearchWordInMatrixUtil(array_test, searchString);

    searchString.erase();
    searchString.assign("pop");

    SearchWordInMatrixUtil(array_test, searchString);

    searchString.erase();
    searchString.assign("bike");

    SearchWordInMatrixUtil(array_test, searchString);

    return TEST_SUCCESS;
}

const TestFamily* strings_init()
{
    TestFamily *testFamily = new TestFamily("strings", static_cast<int>(10));

    TEST_DEF(trie_helper, TrieHelper);
    TEST_DEF(kmp_search_success, KMPSearchSuccess);
    TEST_DEF(kmp_search_fail, KMPSearchFail);
    TEST_DEF(search_word_in_matrix, SearchWordInMatrix);

    return testFamily;
}
