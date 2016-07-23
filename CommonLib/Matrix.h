//============================================================================
// File Name   : Matrix.h 
// Authors     : Nikola Losic
// Version     : 1.0
// Description : Contains declarations of functions for matrix manipulation
//============================================================================

#pragma once
#include <string>

/**
Multiplies parts of two square matrices using O(n^3) algorithm and puts result in third
    
    @param c
        Result matrix
    @param a
        Left matrix
    @param rowA
        Row of the left matrix where its part starts
    @param colA
        Column of the left matrix where its part starts
    @param b
        Right Matrix
    @param rowB
        Row of the right matrix where its part starts
    @param colB
        Column of the right matrix where its part starts
    @param size
        Size of the matrices
*/
void multiplyMatricesStandard(int **c, int **a, int rowA, int colA, int **b, int rowB, int colB, int size);

/**
Adds parts of two square matrices using O(n^3) algorithm and puts result in third
    
    @param c
        Result matrix
    @param a
        Left matrix
    @param rowA
        Row of the left matrix where its part starts
    @param colA
        Column of the left matrix where its part starts
    @param b
        Right Matrix
    @param rowB
        Row of the right matrix where its part starts
    @param colB
        Column of the right matrix where its part starts
    @param size
        Size of the matrices
*/
void addMatrices(int **c, int **a, int rowA, int colA, int** b, int rowB, int colB, int size);

/**
Substracts parts of two square matrices using O(n^3) algorithm and puts result in third
    
    @param c
        Result matrix
    @param a
        Left matrix
    @param rowA
        Row of the left matrix where its part starts
    @param colA
        Column of the left matrix where its part starts
    @param b
        Right Matrix
    @param rowB
        Row of the right matrix where its part starts
    @param colB
        Column of the right matrix where its part starts
    @param size
        Size of the matrices
*/
void subMatrices(int **c, int **a, int rowA, int colA, int** b, int rowB, int colB, int size);

/**
Writes matrix to file in next format:
    [1, 2, 3, 4;
     5, 6, 7, 8;
     9, 10, 11, 12;
     13, 14, 15, 16] 

    @param a 
        Matrix to save
    @param rows
        Number of rows in the matrix
    @param cols
        Number of columns in the matrix
    @param fileName
        Name of the file where matrix will be saved
*/
void writeMatrixToFile(int **a, int rows, int cols, std::string fileName);

/**
Reads matrix from the file and puts it in the result matrix. Format of the matrix in file is:
    [1, 2, 3, 4;
     5, 6, 7, 8;
     9, 10, 11, 12;
     13, 14, 15, 16]

    @param a
        Result matrix
    @param rows
        Number of rows in the matrix
    @param cols
        Number of columns in the matrix
    @param fileName
        Name of the file where matrix is stored
*/
void readMatrixFromFile(int **a, int rows, int cols, std::string fileName);
