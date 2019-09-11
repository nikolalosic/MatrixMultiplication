//============================================================================
// File Name   : HelpFunctions.cpp
// Authors     : Nikola Losic
// Version     : 1.0
// Copyright   : Nikola Losic ©. All rights reserved
// Description : Contains definitions of functions used by test suites
//============================================================================


#include "HelpFunctions.h"


bool compareMatrix(int **a, Mat<int> &b, int rows, int cols) {
    for (int i = 0;i < rows;++i) {
        for (int j = 0;j < cols;++j) {
            if (a[i][j] != b(i, j)) {
                return false;
            }
        }
    }
    return true;
}

int **allocateMatrix(int size) {
    int **a = new int*[size];
    for (int i = 0;i < size;++i) {
        a[i] = new int[size];
    }
    return a;
}

void freeMatrix(int **a, int size) {
    for (int i = 0;i < size;++i) {
        delete[] a[i];
    }
    delete[] a;
}

void copyMatrix(int **a, Mat<int> &b, int size) {
    for (int i = 0;i < size;++i) {
        for (int j = 0;j < size;++j) {
            a[i][j] = b(i, j);
        }
    }
}