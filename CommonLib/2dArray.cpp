//============================================================================
// File Name   : 2dArray.cpp 
// Authors     : Nikola Losic
// Version     : 1.0
// Description : Contains definitions of functions for manipulating 2d arrays
//============================================================================

#include "2dArray.h"
#include <iostream>
#include <tbb\scalable_allocator.h>

template<typename T>
void print2dArray(T ** a, int rows, int cols) {
    std::cout << "--------------------------------------" << std::endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols;++j) {
            std::cout << a[i][j] << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << "--------------------------------------" << std::endl;
}

template <typename T>
void init2dArrayToValue(T **a, int rows, int cols, T value) {
    for (int i = 0;i < rows;++i) {
        for (int j = 0; j < cols;++j) {
            a[i][j] = value;
        }
    }
}

template<typename T>
T **allocate2dArray(int nRows, int nCols) {
    //(step 1) allocate memory for array of elements of column
    T **ppi = new T*[nRows];

    //(step 2) allocate memory for array of elements of each row
    T *curPtr = new T[nRows * nCols];

    // Now point the pointers in the right place
    for (int i = 0; i < nRows; ++i) {
        *(ppi + i) = curPtr;
        curPtr += nCols;
    }
    return ppi;
}

template<typename T>
void free2dArray(T** Array) {
    if (Array) {
        delete[] * Array;
        delete[] Array;
        Array = NULL;
    }
}

template <typename T>
void free2dArrayScalable(T** Array) {
    scalable_free(*Array);
    scalable_free(Array);
    Array = NULL;
}

template<typename T>
T **allocate2dArrayScalable(int nRows, int nCols) {
    //(step 1) allocate memory for array of elements of column
    T **ppi = (T**)scalable_malloc(nRows * sizeof(T*));

    //(step 2) allocate memory for array of elements of each row
    T *curPtr = (T*)scalable_malloc(nRows * nCols * sizeof(T));


    // Now point the pointers in the right place
    for (int i = 0; i < nRows; ++i) {
        *(ppi + i) = curPtr;
        curPtr += nCols;
    }
    return ppi;
}

bool compareInteger2dArray(int **a, int **b, int  rows, int cols) {
    for (int i = 0;i < rows;++i) {
        for (int j = 0;j < cols;++j) {
            if (a[i][j] != b[i][j]) {
                return false;
            }
        }
    }
    return true;
}

void initRandomInteger2dArray(int **a, int rows, int cols) {
     
    for (int i = 0;i < rows;++i) {
        for (int j = 0;j < cols;++j) {
            a[i][j] = rand() % 5;
        }
    }
}

int **generateRandomInteger2dArray(int rows, int cols) {
    int **m = allocate2dArrayScalable<int>(rows, cols);
    initRandomInteger2dArray(m, rows, cols);
    return m;
}


