#include <iostream>
#include <string>
#include <iomanip>
#include "test_framework.h"
#include "trie.h"

//Helper function to print a NxN matrix
static void PrintNxNMatrix(const int arr[][5], int size)
{
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++)
            std::cout << std::setw(3)<< std::right << arr[i][j] << " ";
        std::cout << std::endl;
    }
    std::cout <<  std::endl;
}

//5*5 matrix for now
int arr[5][5] = {
    {1,   2,  3,  4,  5},
    {6,   7,  8,  9, 10},
    {11, 12, 13, 14, 15},
    {16, 17, 18, 19, 20},
    {21, 22, 23, 24, 25},
};


static inline bool InBounds(int x, int y, int& size)
{
    if ((x >= 0 && x < size) && (y >= 0 && y < size))
        return true;
    else
        return false;
}

#define UP 0
#define DOWN 1
#define SIZE 5

static inline void GetNextXY(int &x, int &y, int dir)
{
    if (dir == UP){
        x = x - 1;
        y = y + 1;
    } else if (dir == DOWN) {
        x = x + 1;
        y = y - 1;
    }
}

void PrintMatrixDiagonalUtil(int (&arr)[SIZE][SIZE], int x, int y,
        int& size, int dir) 
{
    if(!InBounds(x, y, size))
        return;

    while (1) {
        int x_t = x, y_t = y;
        std::cout << arr[x][y] << " ";
        
        GetNextXY(x_t, y_t, dir);
        if (!InBounds(x_t, y_t, size))
            break;

        x = x_t;
        y = y_t;
    }
    std::cout << std::endl;

    if (dir == UP) {
        if (y < size - 1)
            y++;
        else if (y == size - 1)
            x++;
        dir = DOWN;
    } else if (dir == DOWN) {
        if (x < size - 1)
            x++;
        else if (x == size - 1)
            y++;
        dir = UP;
    }

    PrintMatrixDiagonalUtil(arr, x, y, size, dir);
}

int PrintMatrixDiagonal(void *data) 
{
    int size = SIZE;
    PrintNxNMatrix(arr, size);
    PrintMatrixDiagonalUtil(arr, 0, 0, size, UP);

    return TEST_SUCCESS;
}

int PrintMatrixSpiral(void *data)
{
    //5*5 matrix for now
    int arr[5][5] = {
        {1,   2,  3,  4,  5},
        {6,   7,  8,  9, 10},
        {11, 12, 13, 14, 15},
        {16, 17, 18, 19, 20},
        {21, 22, 23, 24, 25},
    };

    int k = 0; //starting row index
    int l = 0; //starting col index
    int m = 5; // num rows
    int n = 5; //num cols
    int i = 0;

    while ((k < m) && (l < n)) {
        for (i = l; i < n; i++)
            std::cout << arr[k][i] << " ";
        k++;
        std::cout << "---";

        for (i = k; i < m; i++)
            std::cout << arr[i][n-1] << " ";
        n--;
        std::cout << "---";

        if (k < m) {
            for ( i = n-1; i >= l; i-- )
                std::cout << arr[m-1][i] << " ";
            m--;
            std::cout << "---";
        }

        if (l < n) {
            for (i = m-1; i >= k; i--)
                std::cout << arr[i][l] << " ";
            l++;
            std::cout << "---";
        }
    }
    
    std::cout << std::endl;
    return TEST_SUCCESS;
}
            
// Rotate the Matrix 90 degress clockwise
int MatrixRotate(void *data)
{
    int arr[5][5] = {
        {1,   2,  3,  4,  5},
        {6,   7,  8,  9, 10},
        {11, 12, 13, 14, 15},
        {16, 17, 18, 19, 20},
        {21, 22, 23, 24, 25},
    };

    PrintNxNMatrix(arr, 5);

    int size = 5;
    int layers  = size / 2;

    std::cout << "Number of Layers: " << layers << std::endl << std::endl;

    //Clockwise rotation of NxN matrix
    for (int layer = 0; layer < layers ; layer++) {

        int offset = size - layer - 1;
        int n = 0;
        int temp = 0; //swap buffer

        for (int i = layer; i < offset ; i++, n++) {

            temp = arr[layer][i];

            //From Left to Top
            arr[layer][i] = arr[offset - n][layer];

            // From Bottom to Left
            arr[offset - n][layer] = arr[offset][offset - n];

            // From Right to Bottom
            arr[offset][offset - n] = arr[i][offset];

            //From Top to Right
            arr[i][offset] = temp;
        }
    }

    //Use the Logger module here, maybe ? ?
    std::cout << "After 90 degree rotation" << std::endl;
    PrintNxNMatrix(arr, 5);

    return TEST_SUCCESS;
}
/* Print all unique rows in a binary matric */
int UniqueRow(void *data)
{
#define NRROWS 5
#define NRCOLS 5
    int arr[5][5] = {
        {1, 1, 1, 0, 1},
        {0, 1, 1, 0, 1},
        {1, 0, 1, 0, 1},
        {1, 1, 1, 0, 1},
        {1, 1, 1, 0, 1},
    };

    Trie testTrie;
    std::string testString;
    
    for (int i = 0; i < NRROWS; i++) {

        /*
         * A bit of a hack done here to convert each row of the matrix
         * to a std::string format, so that the trie interface can accept
         * rows
         */
        int temp = 0;
        for (int j = 0; j < NRCOLS; j++) {
            temp = temp * 10 + arr[i][j];
        }

        std::string tempString = std::to_string(temp);

        if (testTrie.SearchWord(tempString)) {
            /*
             * Found a Duplicate row.
             * Maybe do something here? 
             */
        }
        else {
            testTrie.InsertWord(tempString);

            for (int j = 0; j < NRCOLS; j++)
                std::cout << arr[i][j] << " ";
            std::cout << std::endl;
        }
    }

    return TEST_SUCCESS;
}

const TestFamily* matrix_init()
{
    TestFamily *testFamily = new TestFamily("matrix", static_cast<int>(10));

    TEST_DEF(matrix_rotate, MatrixRotate);
    TEST_DEF(print_matrix_spiral, PrintMatrixSpiral);
    TEST_DEF(print_matrix_diagonal, PrintMatrixDiagonal);
    TEST_DEF(unique_row, UniqueRow);

    return testFamily;
}
