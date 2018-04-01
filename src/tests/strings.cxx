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

const char* digits[] = {"", "One ", "Two ", "Three ", "Four ", "Five ", "Six ", "Seven ", "Eight ", "Nine "};
const char* teens[] = {"", "Eleven ", "Twelve ", "Thirteen ", "Fourteen ", "Fifteen ", "Sixteen ", "Seventeen ", "Eighteen ", "Nineteen "};
const char* tens[] = {"", "Ten ", "Twenty ", "Thirty ", "Forty ", "Fifty ", "Sixty ", "Seventy ", "Eighty ", "Ninety "};
const char* hundereds[] = {"", "Hundered ", "Thousand "};

int ConvertThreeDigitNumberToText(const std::string input, int index,
        std::string& output, int length)
{
    bool hunderedsPresent = false;

    if(length == 3) {
        output.append(digits[input[index++] - '0']);
        output.append(hundereds[1]);
        length--;
        hunderedsPresent = true;
    }
    if (length == 2) {
        int digit1 = input[index++] - '0';
        int digit2 = input[index] - '0';

        if (hunderedsPresent)
            output.append("and ");

        /* Special case for the teens */
        if (digit1 == 1 && (digit2 >= 1 && digit2 <= 9 )) {
            output.append(teens[digit2]);
        }
        else {
            output.append(tens[digit1]);
            output.append(digits[digit2]);
        }

        return 0;
    }
    else if (length == 1) {
        output.append(digits[input[index] - '0']);
    }

    return 0;
}
/*
 * Convert a number in string format to the text representation of the number
 * Currently this only handles numbers upto 6 digits, but can be extended to
 * larger numerals going into millions and beyond if needed extending the same
 * logic
 */
int NumberToText(void* data)
{
    std::string testInput("123456");
    int index = 0;
    int length = testInput.size();
    std::string output;

    if (length > 6)
        return TEST_SKIPPED;

    if (length > 3) {
        index = 0;
        int partLength = length - 3;

        ConvertThreeDigitNumberToText(testInput, index, output, partLength);

        output.append(hundereds[2]);
        output.append(", ");

        ConvertThreeDigitNumberToText(testInput, index + (partLength), output,
                length - partLength);

    }
    else if (length <=3) {
        index = 0;
        ConvertThreeDigitNumberToText(testInput, index, output, length);
    }

    std::cout << output.append(".") << std::endl;

    return TEST_SUCCESS;
}

int AngleBetweenHandsHelper(int h, int m)
{
    if (h < 0 || h > 12 || m < 0 || m > 60)
        return -1;

    if (h == 12) h = 0;
    if (m == 60) m = 0;

    int tempMinutes = (h * 60) + m;
    /* Convert both the hours and minutes to same units*/
    int hoursAngle = 0.5 * tempMinutes;
    int minutesAngle = 6 * m;
    std::cout << tempMinutes << hoursAngle << " " << minutesAngle << std::endl;

    int angle = std::abs(hoursAngle  - minutesAngle);

    return std::min(angle, 360 - angle);
}

/*
 * This thing should go to someothe file for some misc questions
 */
int AngleBetweenHands(void* data)
{
    std::cout << AngleBetweenHandsHelper(3, 15) << std::endl;

    return TEST_SUCCESS;
}

/*
 * To get decent encodings we use all the lower case and upper case alphabet +
 * the numbers from 0 to 9, this gives us a good 62 chars to play with.
 * This function encodes the givent unsigned long number which could potentially
 * be used a database index and converts the number to a 62 base string.
 */
void TinyURLGenerator(unsigned long num, std::string& output)
{
    const std::string map("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789");

    while (num) {
        output.push_back(map[num % 62]);
        num /= 62;
    }

    std::reverse(output.begin(), output.end());
}

/*
 * Convert the given input which is a 62 base coded string to an unsigned long
 * number, this is the exact inverse of the above function. When the user
 * gives the tinyURL as an input, we should be able to retreive the unsigned long
 * number which could then be used to access the database.
 */
unsigned long TinyURLConvertURLToNum(std::string& input)
{
    unsigned long output = 0;
    int i = 0;

    while(input[i]) {
        if (input[i] >= 'a' && input[i] <= 'z')
            output = output * 62 + (input[i] - 'a');
        else if (input[i] >= 'A' && input[i] <= 'Z')
            output = output * 62 + (input[i] - 'A' + 26);
        else if (input[i] >= '0' && input[i] <= '9')
            output = output * 62 + (input[i] - '0' + 52);
        i++;
    }

    return output;
}

int TinyURL(void* data)
{
    unsigned long number = 12345;
    std::string output;

    TinyURLGenerator(number, output);

    std::cout << "This is the 62 base encoded string for " << number <<": " << output << std::endl;
    std::cout << "The number back now: " << TinyURLConvertURLToNum(output) << std::endl;


    return TEST_SUCCESS;
}

int AToI(void* data)
{
    std::string test("123456");
    int result = 0;

    for(int i = 0; i < test.size(); i++) {
        result = result * 10 + (test[i]  - '0');
    }

    std::cout << result << std::endl;

    return TEST_SUCCESS;
}

/*
 * Only does base 10 conversions for positive numbers; but can be extended to
 * handle other use cases
 * TODO: Need to come up with a way to transfer user inputs to the test cases
 */
int IToA(void* data)
{
    int testInput = 123454;
    std::string output;

    if (!testInput)
        output.insert(output.begin(), '0');

    while (testInput) {
        //std::cout << testInput % 10 << " ";
        output.insert(output.begin(), testInput % 10 + '0');
        testInput /= 10;
    }

    std::cout << output << " " << std::endl;

    return TEST_SUCCESS;
}

int IsPalindrome(void* data)
{
    std::string testString("Sharat");

    int low = 0;
    int high = testString.size() - 1;

    while (low <= high)
        if (testString[low++] != testString[high--]) {
            std::cout << "The given string: " << testString << " is not a palindrome"  << std::endl;
            return TEST_SUCCESS;
       }

    std::cout << "The given string: " << testString << " is a palindrome" << std::endl;

    return TEST_SUCCESS;
}

/*
 * URL encoding, replace spaces with '%20' in the entire string
 */
int ReplaceSpaces(void* data)
{
    std::string testString("This is the best setup ever. ");
    int countSpaces = 0;
    int i = 0;
    int index;

    for (i = 0; i < testString.size(); i++)
        if(testString[i] == ' ')
            countSpaces++;

    /*
     * remove trailing spaces, we do not want to replace them
     */
    while(testString[--i] == ' ') {

        testString.pop_back();
        countSpaces--;
    }

    std::cout << "Original String: " << testString << " "
        << countSpaces << std::endl;

    int newLength = testString.size() + 2 * countSpaces;
    index = newLength - 1;
    testString.resize(newLength);

    for (int j = i; j >= 0; j--) {
        if (testString[j] == ' ') {
            testString[index--] = '0';
            testString[index--] = '2';
            testString[index--] = '%';
        }
        else
            testString[index--] = testString[j];
    }

    std::cout << "URL encoded String: " << testString << std::endl;

    return TEST_SUCCESS;
}

/*
 * @i: index into the input string
 * @j: index into the output buffer
 */
static void StringSpacePermHelper(const std::string& input, std::string buffer,
        int i, int j)
{
    if (i == input.size()) {
        std::cout << buffer << std::endl;
        return;
    }

    /*
     * recurse here, either we add the char from the input
     * or add a space followed by the char
     */
    buffer[j] = input[i];
    StringSpacePermHelper(input, buffer, i + 1, j + 1);

    buffer[j++] = ' ';
    buffer[j] = input[i];
    StringSpacePermHelper(input, buffer, i + 1, j + 2);
}

int StringSpacePerm(void* data)
{
    std::string input("ABC");
    std::string output;
    int n = input.size();

    output.resize((2*n) - 1);

    output[0] = input[0];
    StringSpacePermHelper(input, output, 1, 1);

    return TEST_SUCCESS;
}

const TestFamily* strings_init()
{
    TestFamily *testFamily = new TestFamily("strings", static_cast<int>(10));

    TEST_DEF(trie_helper, TrieHelper);
    TEST_DEF(kmp_search_success, KMPSearchSuccess);
    TEST_DEF(kmp_search_fail, KMPSearchFail);
    TEST_DEF(search_word_in_matrix, SearchWordInMatrix);
    TEST_DEF(number_to_text, NumberToText);
    TEST_DEF(angle_between_hands, AngleBetweenHands);
    TEST_DEF(tiny_url, TinyURL);
    TEST_DEF(atoi, AToI);
    TEST_DEF(itoa, IToA);
    TEST_DEF(is_palindrome, IsPalindrome);
    TEST_DEF(replace_spaces, ReplaceSpaces);
    TEST_DEF(string_space_perm, StringSpacePerm);

    return testFamily;
}
