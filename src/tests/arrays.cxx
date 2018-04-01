#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <map>
#include <set>
#include "test_framework.h"

/*
 * This is a simple interpretation of Kadane's algorithm
 */
int LargestSum(void *data)
{
    std::vector<int> arr = {-2, -3, 4, -1, -2, 1, 5, -3};
    int maxEndingHere = 0;
    int maxCurrent = 0;
    int start = 0;
    int end = 0;
    int s = 0;

    for (int i = 0; i < arr.size(); i++) {
        maxEndingHere += arr[i];

        if (maxEndingHere < 0) {
            maxEndingHere = 0;
            s++;
        }
        else if (maxCurrent < maxEndingHere) {
            maxCurrent = maxEndingHere;
            start = s;
            end = i;
        }
    }

    std::cout << "Largest Sum Contiguous SubArray " << maxCurrent << std::endl;

    for (int i = start; i <= end; i++)
        std::cout << arr[i] << " ";
    std::cout << std::endl;

    return TEST_SUCCESS;
}

/*
 * Replace all zeros in an input number to  '5'
 */

int ReplaceZerosHelper(int num)
{
    if (num == 0)
        return 0;

    int digit = num % 10;
    if (digit == 0)
        digit = 5;

    return ReplaceZerosHelper(num / 10) * 10 + digit;

}

int ReplaceZeros(void* data)
{
    int testNum = 102030;

    std::cout << "original number: " << testNum << " " << "modified number: " <<
        ReplaceZerosHelper(testNum) << std::endl;

    return TEST_SUCCESS;
}

int LargestHistogram(void* data)
{
    std::vector<int> hist;
    std::stack<int> s;
    hist.push_back(6);
    hist.push_back(2);
    hist.push_back(5);
    hist.push_back(4);
    hist.push_back(5);
    hist.push_back(1);
    hist.push_back(6);
    int n = hist.size();
    std::vector<int> posleft(n), posright(n);

    /*
     * Determine the left edges of each rectangle. For each rectangle, remove
     * the ones on the left of it which are greater in height. This way the
     * ones on the right of it do not have to consider it for their calculations.
     */
    for (int i = 0; i < n; i++) {
        while(!s.empty() && hist[s.top()] >= hist[i])
            s.pop();

        posleft[i] = s.empty() ? 0 : s.top() + 1;

        s.push(i);
    }

    /*
     * Determine the right edges of each rectangle. Similar comment to the one
     * above applies here as well.
     */
    for (int i = n - 1; i >= 0; i--) {
        while(!s.empty() && hist[s.top()] >= hist[i])
            s.pop();

        posright[i] = s.empty() ? n - 1 : s.top() - 1;

        s.push(i);
    }

    int maxArea = 0;

    for(int i = 0; i < n; i++) {
        int right = posright[i];
        int left = posleft[i];
        maxArea = std::max(maxArea, hist[i] * (right - left + 1));
    }

    std::cout << "The max histogram area is" << maxArea << std::endl;

    return TEST_SUCCESS;
}

int LargestHistogramCute(void* data)
{
    std::vector<int> hist;
    std::stack<int> s;
    hist.push_back(6);
    hist.push_back(2);
    hist.push_back(5);
    hist.push_back(4);
    hist.push_back(5);
    hist.push_back(1);
    hist.push_back(6);
    int n = hist.size();
    int maxArea = 0;

    for (int i = 0; i < n; i++) {
        /*
         * Its a bit tricky but a neat implementation. When we pop an element
         * from the stack, we know the right end of the rectangle. So for each
         * popped element we have both the left and the right sides of the
         * rectangle. It then becomes simple to calculate and keep track of the
         * maxArea
         */
        while(!s.empty() && hist[s.top()] >= hist[i]) {
            int height = hist[s.top()];
            s.pop();
            int left = s.empty() ? 0 : s.top() + 1;
            int right = i - 1;

            maxArea = std::max(maxArea, height *(right - left + 1));
        }
        s.push(i);
    }

    std::cout << "This is the maxArea in the histogram: " << maxArea << std::endl;

    return TEST_SUCCESS;
}

struct FuelNode {
    int fuel;
    int distance;
};

int FuelProblemHelper(struct FuelNode* list, int n)
{
    int start = 0;
    int end = 1;
    int remainingFuel = 0;

    remainingFuel += list[start].fuel - list[start].distance;

    /*
     * Simulate a queue implementation by maintaining a start and an end index
     * and iterate the array until either the start equals the end in which
     * case we found a starting node on the circle, or if the fuel is negative
     * in which case we try to find the next possible node as a potential
     * starting point.
     */
    while (end != start || remainingFuel < 0) {

        /*
         * If the remainingFuel is  less than zero, then remove the starting
         * points until the remainingFuel becomes greater than zero, after
         * doing this continue in the normal fashion trying to confirm if the
         * full cirucular path is possible from this new start location
         */
        while (remainingFuel < 0 && start != end) {

            remainingFuel -= list[start].fuel - list[start].distance;
            start  = (start + 1) % n ;

            /*
             * If we reach the original starting point, then we have tried all
             * nodes as potential starting points, so just return a failure
             */
            if (start == 0)
                return -1;
        }

        /* keep adding new nodes to the queue */
        remainingFuel += list[end].fuel - list[end].distance;
        end = (end + 1) % n;
    }

    return start;
}

int FuelProblem(void* data)
{
    struct FuelNode list[] = {{6, 4}, {3, 6}, {7, 3}};
    int ret = FuelProblemHelper(list, ARRAY_SIZE(list));

    if (ret < 0)
        std::cout << "There is no solution to the problem" << std::endl;
    else
        std::cout << "There is a circular route possible starting from: " << ret << std::endl;

    return TEST_SUCCESS;
}

int MinSortedRotatedHelper(std::vector<int>& arr, int low, int high)
{
    /*
     * This happens when the array itself is not rotated, so just return the
     * first element
     */
    if (high < low)
        return arr[0];

    /*
     * If there is only one element left, then just return that element
     */
    if (high == low)
        return arr[low];

    int mid = (low + high) / 2;

    if ((mid < high) && arr[mid + 1] < arr[mid])
        return arr[mid + 1];

    if ((mid > low) && arr[mid] < arr[mid - 1])
        return arr[mid];

    if (arr[high] > arr[mid])
        return MinSortedRotatedHelper(arr, low, mid - 1);
    else
        return MinSortedRotatedHelper(arr, mid + 1, high);
}

int MinSortedRotated(void* data)
{
    std::vector<int> testArray = {5, 6, 1, 2, 3, 4};
    std::cout << "Min element is " << MinSortedRotatedHelper(testArray, 0, testArray.size() - 1) << std::endl;

    std::vector<int> testArray1 = {1, 2, 3, 4};
    std::cout << "Min element is " << MinSortedRotatedHelper(testArray1, 0, testArray1.size() - 1) << std::endl;

    return TEST_SUCCESS;
}

int FirstOccuranceSorted(std::vector<int>& arr, int low, int high,
        const int& key)
{
    if (low > high)
        return -1;

    int mid = (low + high) / 2;

    if ((mid == 0 || key > arr[mid - 1]) && arr[mid] == key)
        return mid;

    if (key > arr[mid])
        return FirstOccuranceSorted(arr, mid + 1, high, key);
    else
        return FirstOccuranceSorted(arr, low, mid - 1, key);
}

/*
 * There is no real need to pass the size of the input array seperately(n),
 * arr.size() would have been sufficient
 */
int LastOccuranceSorted(std::vector<int>& arr, int low, int high, int& key, int n)
{
    if (low > high)
        return -1;

    int mid = (low + high) / 2;

    if ((mid == n -1 || key < arr[mid + 1]) && arr[mid] == key)
        return mid;
    else if (key < arr[mid])
        return LastOccuranceSorted(arr, low, mid - 1, key, n);
    else
        return LastOccuranceSorted(arr, mid + 1, high, key, n);
}

int CountElementsSorted(void* data)
{
    std::vector<int> arr = {1, 1, 2, 2, 2, 2, 3};
    int key = 2;

    int first = FirstOccuranceSorted(arr, 0, arr.size() - 1, key);
    int last = LastOccuranceSorted(arr, 0, arr.size() - 1, key, arr.size());

    std::cout << "The count of element: " << key << " in the array is: " << last - first + 1 << std::endl;

    return TEST_SUCCESS;
}

int SearchRotatedSortedHelper(std::vector<int>& arr, int low, int high,
        int& key)
{
    if (low > high)
        return -1;

    int mid = (low + high) / 2;

    if (arr[mid] == key)
        return mid;

    /*
     * See  if the left part of the array is sorted, then check if the left part
     * really hosts the key, if so recur, otherwise recur on to the other side
     */
    if (arr[low] <= arr[mid]) {
        if (key >= arr[low] && key <= arr[mid])
            return SearchRotatedSortedHelper(arr, low, mid -1, key);
        else
            return SearchRotatedSortedHelper(arr, mid + 1, high, key);
    }

    /*
     * mirror the above code for the other side of the array, we do this since
     * the right side  must be definitely sorted, if the left side was not.
     */
    if (key >= arr[mid] && key <= arr[high])
        return SearchRotatedSortedHelper(arr, mid + 1, high, key);
    else
        return SearchRotatedSortedHelper(arr, low, mid - 1, key);
}

int SearchRotatedSorted(void* data)
{
    std::vector<int> arr = {4, 5, 6, 7, 8, 9, 1, 2, 3};
    int key = 10;

    std::cout << "The key: " <<  key << " is at index: " <<
        SearchRotatedSortedHelper(arr, 0, arr.size() - 1, key) << std::endl;

    return TEST_SUCCESS;
}

/*
 * This pivot can be used to simply binary search algorithm in the cases
 * where the input array is sorted but rotated to some degree.
 * This is a more elaborate version of the find a key in a sorted rotated array.
 * see above for the cuter version of this algorithm.
 */
int FindPivotHelper(std::vector<int>& arr, int low, int high)
{
    if (low > high)
        return -1;
    /* few more base cases here */
    if (low)
        ;

    int mid = (low + high) / 2;

    if (mid > low && arr[mid] < arr[mid - 1])
        return mid - 1;
    if (mid < high && arr[mid] > arr[mid + 1])
        return mid;

    if (arr[mid] < arr[low])
        return FindPivotHelper(arr, low, mid - 1);
    else
        return FindPivotHelper(arr, mid + 1, high);
}

int FindPivot(void* data)
{
    std::vector<int> arr = {4, 5, 6, 7, 8, 9, 1, 2, 3};

    std::cout << "Input Array: ";
    for (auto it = arr.begin(); it != arr.end(); it++)
        std::cout << *it << " ";
    std::cout << std::endl;

    int pivot = FindPivotHelper(arr, 0, arr.size() - 1);
    std::cout << "The pivot in the array is at: " << pivot << " value is: " <<
        arr[pivot] << std::endl;

    return TEST_SUCCESS;
}

bool CheckAnagramHelper(std::string s1, std::string s2)
{
    std::map<char, int> hash;

    if (s1.size() != s2.size())
        return false;

    for(auto i = 0; i < s1.size(); i++)
    {
        hash[s1[i]] += 1;
        hash[s2[i]] -= 1;
    }

    for(auto it = hash.begin(); it != hash.end(); it++)
        if (it->second)
            return false;

    return true;
}

int CheckAnagram(void* data)
{

    std::string s1("cat");
    std::string s2("act");

    if (CheckAnagramHelper(s1, s2))
        std::cout << "The given strings: " << s1 << " and " << s2 << " " << " are anagrams" << std::endl;
    else
        std::cout << "The given strings: " << s1 << " and " << s2 << " " << " are not anagrams" << std::endl;

    return TEST_SUCCESS;
}

bool IsSingleDigit(int num)
{
    return (num >= 0 && num <= 9);
}

bool IsNumPalindromeHelper(int num, int* dupNum)
{

    if (IsSingleDigit(num))
        return num == *dupNum % 10;

    if (!IsNumPalindromeHelper(num/10, dupNum))
        return false;

    *dupNum /= 10;

    /*
     * At this point number will have the ith digit from the front, while
     * the dupNum will have the ith digit from the end
     */
    return ((num % 10) == (*dupNum % 10));
}

int IsNumPalindrome(void* data)
{
    int testNum = 123211234;
    int testNumDup = testNum;

    if (IsNumPalindromeHelper(testNum, &testNumDup))
        std::cout << "The given number: " << testNum << " is a palindrome" << std::endl;
    else
        std::cout << "The given number: " << testNum << " is not a palindrome" << std::endl;

    return TEST_SUCCESS;
}

int ReverseNumber(void* data)
{
    int testNumber = 12345;
    int testNumberCopy = testNumber;
    int result = 0;

    while(testNumber) {
        result = result * 10 + testNumber % 10;
        testNumber /= 10;
    }

    std::cout << "Original Number: " <<  testNumberCopy << " reversed: " << result << std::endl;

    return TEST_SUCCESS;
}

static int GetMedian(int arr[], int n)
{
    if (n == 0)
        return -1;

    if (n % 2 == 0)
        return (arr[n/2 - 1] + arr[n/2] ) / 2;
    else
        return arr[n/2];
}

int MedianSortedHelper(int arr1[], int arr2[], int n)
{
    if (n == 0)
        return -1;
    if (n == 1)
        return (arr1[0] + arr2[0]) / 2;
    if (n == 2)
        return (std::max(arr1[0], arr2[0]) + std::min(arr1[1], arr2[1])) / 2;

    int m1 = GetMedian(arr1, n);
    int m2 = GetMedian(arr2, n);

    if (m1 < m2) {
        if (n % 2 == 0)
            return MedianSortedHelper(arr1 + n/2 - 1, arr2, n - n/2 + 1);
        return MedianSortedHelper(arr1 + n/2, arr2, n - n/2);
    }

    if (n % 2 == 0)
        return MedianSortedHelper(arr2 + n/2 - 1, arr1, n - n/2 + 1);
    return MedianSortedHelper(arr2 + n/2, arr1, n - n/2);
}

int MedianSorted(void* data)
{
    //int arr1[] = {1, 12, 15, 26, 28};
    //int arr2[] = {2, 13, 17, 30, 45};

    int arr1[] = {1, 2, 3, 6};
    int arr2[] = {4, 6, 8, 10};

    std::cout << "Median of the Input arrays is: ";
    std::cout <<  MedianSortedHelper(arr1, arr2, ARRAY_SIZE(arr1)) << std::endl;

    return TEST_SUCCESS;
}


/*
 * Write a method to sort an arrays of 0, 1, 2's.
 * This is a simple implementation of the Dutch National Flag Problem
 */
void SwapVector(std::vector<int>& arr, int l, int r)
{
    int temp = arr[l];
    arr[l] = arr[r];
    arr[r] = temp;
}

int Sort012(void* data)
{
    std::vector<int> arr = {2, 2, 1, 0, 1, 2, 0, 0};
    int low = 0;
    int mid = 0;
    int high = arr.size() - 1;

    while (mid <= high) {
        switch(arr[mid]) {
            case 0:
                SwapVector(arr, low++, mid++);
                break;
            case 1:
                mid++;
                break;
            case 2:
                SwapVector(arr, mid, high--);
        }
    }

    for (auto it = arr.begin(); it != arr.end(); it++)
        std::cout << *it << " ";
    std::cout << std::endl;

    return TEST_SUCCESS;
}

int Sort01(void* data)
{
    std::vector<int> arr = {0, 1, 1, 1, 0, 0, 1, 1};
    int low = 0;
    int high = arr.size() - 1;

    while (low < high) {
        while((low < high) && arr[low] == 0)
            low++;

        while((high > low) && arr[high] == 1)
            high--;

        if (low < high) {
            arr[low++] = 0;
            arr[high--] = 1;
        }
    }

    for (auto it = arr.begin(); it != arr.end(); it++)
        std::cout << *it << " ";
    std::cout << std::endl;

    return TEST_SUCCESS;
}

static int CountSetBits(int n)
{
    int count = 0;

    while(n) {
        if (n & 0x1)
            ++count;
        n >>= 1;
    }

    return count;
}

int CountBits(void* data)
{

    int a = 12;
    int b = 1;

    std::cout << "Number of bit swaps needed to change from A to B: " <<
        CountSetBits(a^b) << std::endl;

    return TEST_SUCCESS;
}

int EquilibriumIndex(void* data)
{
    std::vector<int> arr = {-7, 1, 5, 2, -4, 3, 0};
    int n = arr.size();
    int leftSum = 0;

    int totalSum = 0;

    for (int i = 0; i < n; i++)
        totalSum += arr[i];

    for(int i = 0; i < n; i++) {
        totalSum -= arr[i];

        if (leftSum == totalSum)
            std::cout << "equilibrium index is: " << i << std::endl;

        leftSum += arr[i];
    }

    return TEST_SUCCESS;
}

int FindFour(void* data)
{
    std::vector<int> input = {3, 4, 7, 1, 2, 9, 8};
    int n = input.size();
    std::map<int, std::pair<int, int>> myMap;

    for(int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {

            int sum = input[i] + input[j];

            if (myMap.find(sum) == myMap.end()) {
                myMap[sum] = std::make_pair(i, j);
            }
            else {
                std::pair<int, int> pp = myMap[sum];

                std::cout << input[pp.first] << ", " << input[pp.second] << " --- " <<
                    input[i] << ", " <<input[j] << std::endl;

                //return TEST_SUCCESS;
            }
        }
    }

    return TEST_SUCCESS;
}

const TestFamily* arrays_init()
{
    TestFamily *testFamily = new TestFamily("arrays", static_cast<int>(100));

    TEST_DEF(largest_sum, LargestSum);
    TEST_DEF(replaces_zeros, ReplaceZeros);
    TEST_DEF(largest_histogram, LargestHistogram);
    TEST_DEF(largest_histogram_cute, LargestHistogramCute);
    TEST_DEF(fuel_problem, FuelProblem);
    TEST_DEF(min_sorted, MinSortedRotated);
    TEST_DEF(count_elements_sorted, CountElementsSorted);
    TEST_DEF(search_rotated_sorted, SearchRotatedSorted);
    TEST_DEF(find_pivot, FindPivot);
    TEST_DEF(check_anagram, CheckAnagram);
    TEST_DEF(is_num_palindrome, IsNumPalindrome);
    TEST_DEF(reverse_number, ReverseNumber);
    TEST_DEF(median_sorted, MedianSorted);
    TEST_DEF(sort_012, Sort012);
    TEST_DEF(sort_01, Sort01);
    TEST_DEF(count_bits, CountBits);
    TEST_DEF(eq_idx, EquilibriumIndex);
    TEST_DEF(find_four, FindFour);

    return testFamily;
}
