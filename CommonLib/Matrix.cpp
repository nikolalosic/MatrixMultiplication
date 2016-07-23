//============================================================================
// File Name   : Matrix.cpp 
// Authors     : Nikola Losic
// Version     : 1.0
// Description : Contains definitions of functions for matrix manipulation
//============================================================================


#include "Matrix.h"
#include "2dArray.h"
#include <fstream>
#include <exception>


void multiplyMatricesStandard(int **c, int **a, int rowA, int colA, int **b, int rowB, int colB, int size) {
    long cSum;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            cSum = 0;
            for (int k = 0; k < size; ++k) {
                cSum += a[rowA + i][colA + k] * b[rowB + k][colB + j];
            }
            c[i][j] = cSum;
        }
    }
}

void addMatrices(int **c, int **a, int rowA, int colA, int** b, int rowB, int colB, int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            c[i][j] = a[rowA + i][colA + j] + b[rowB + i][colB + j];
        }
    }

}

void subMatrices(int **c, int **a, int rowA, int colA, int** b, int rowB, int colB, int size) {
    for (int i = 0; i < size;++i) {
        for (int j = 0; j < size; ++j) {
            c[i][j] = a[rowA + i][colA + j] - b[rowB + i][colB + j];
        }
    }
}

void writeMatrixToFile(int **a, int rows,int cols, std::string fileName) {
    std::ofstream ost;
    ost.open(fileName);
    if (!ost) {
        throw std::runtime_error("Error opening output file " + fileName);
    }
    ost << '[';
    for (int i = 0;i < rows;++i) {
        for (int j = 0;j < cols;++j) {
            ost << a[i][j];
            if (j == cols - 1) {
                if (i == rows - 1) {
                    ost << ']';
                }
                else {
                    ost << ';' << std::endl;
                }
            }
            else {
                ost << ", ";
            }
        }
    }
    ost.close();
}

void readMatrixFromFile(int **a, int rows,int cols, std::string fileName) {
    std::ifstream ist(fileName);
    if (!ist) {
        throw std::runtime_error("Error opening input file " + fileName);
    }
    ist.exceptions(ist.exceptions() | std::ios_base::badbit);
    int currentNum;
    char token;
    ist >> token;

    int row = 0;
    for (int i = 0;i < cols;++i) {
        if (!(ist >> currentNum) || !(ist >> token)) {
            ist.close();
            throw std::runtime_error("Matrix format error, check file " + fileName);
        }
        if (i == cols - 1) {
            if (row == rows - 1) {
                if (token != ']') {
                    ist.close();
                    throw std::runtime_error("Matrix format error, check file " + fileName);
                }
                a[row][i] = currentNum;
                break;
            }
            else if (token != ';') {
                ist.close();
                throw std::runtime_error("Matrix format error, check file " + fileName);
            }
            row++;
            i = -1; /*reset counter, we are loading new row*/
            a[row][i] = currentNum;
            continue;
        }
        else if (token != ',') {
            ist.close();
            throw std::runtime_error("Matrix format error, check file " + fileName);
        }
        a[row][i] = currentNum;
    }




    while (ist >> token) {
        if (!isspace(token)) {
            ist.close();
            throw std::runtime_error("Matrix format error, check file");
        }
    }
    ist.close();
}