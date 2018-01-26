#include <iostream>
#include <string>
#include <iomanip>
#include "test_framework.h"

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

const TestFamily* matrix_init()
{
    TestFamily *testFamily = new TestFamily("matrix", static_cast<int>(10));

    TEST_DEF(matrix_rotate, MatrixRotate);

    return testFamily;
}
