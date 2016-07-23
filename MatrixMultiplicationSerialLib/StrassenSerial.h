//============================================================================
// File Name   : StrassenSerial.h 
// Authors     : Nikola Losic
// Version     : 1.0
// Description : Contains declarations of functions for serial version of 
//               Strassen's algorithm for multiplication of matrices
//============================================================================

#pragma once


/**
Multiplies parts of two square matrices using Strassen's algorithm and puts result in third

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
void strassenSerialMultiply(int **c, int **a, int rowA, int colA,
    int **b, int rowB, int colB, int size);


/**
Multiplies square matrices using a serial version of Strassen's algorithm for matrix multiplication

    @param a
        Left matrix
    @param b
        Right matrix
    @param c
        Result matrix
    @param size
        Size of the matrices
*/
void strassenSerial(int **a, int **b, int **c, int size);