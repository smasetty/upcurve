#include <iostream>
#include "test_framework.h"
#include "backtrace.h"

int Subsets(void *data) {
    Subset test(4);
    test.GenerateSubsets();
    return TEST_SUCCESS;
}

int StringPermutations(void *data) {
    std::string testString("SHAR");
    StringPerm test(testString);
    test.GeneratePermutations();
    return TEST_SUCCESS;
}

#define NR_ROWS 4
#define NR_COLS 4

static bool QueenSafe(int (&arr)[NR_ROWS][NR_COLS], int row, int col)
{
    int i, j;
    /* Check the same row, onto the left side */
    for (int i = 0; i < col; i++)
        if (arr[row][i])
            return false;

    /* Upper left diagonal */
    for(i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (arr[i][j])
            return false;

    /* Lower left diagonal */
    for(i = row, j = col; i < NR_ROWS && j >= 0; i++, j--)
        if (arr[i][j])
            return false;

    /* Safe position for the Queen */
    return true;
}

static bool NQueensBacktrack(int (&arr)[NR_ROWS][NR_COLS], int col)
{
    if (col >= NR_COLS)
        return true;

    for (int i = 0; i < NR_ROWS; i++) {

        if (QueenSafe(arr, i, col)) {
            /* Try placing the Queen at this slot, after it is deemed safe */
            arr[i][col] = 1;

            if (NQueensBacktrack(arr, col + 1))
                return true;

            /*
             * backtrack and reset to 0, if this step did not yield results
             */
            arr[i][col] = 0;
        }
    }

    return false;
}

int NQueens(void* data)
{
    int arr[NR_ROWS][NR_COLS] = {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
    };

    if (NQueensBacktrack(arr, 0)) {
        for (int i = 0; i < NR_ROWS; i++) {
            for (int j = 0; j < NR_COLS; j++)  {
                std::cout << arr[i][j] <<  " ";
            }
            std::cout << std::endl;
        }
    }

    return TEST_SUCCESS;
}

const TestFamily* backtrack_init()
{
    TestFamily *testFamily = new TestFamily("backtrack", static_cast<int>(10));

    TEST_DEF(subsets, Subsets);
    TEST_DEF(string_perm, StringPermutations);
    TEST_DEF(n_queens, NQueens);

    return testFamily;
}
