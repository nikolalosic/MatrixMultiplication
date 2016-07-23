//============================================================================
// File Name   : StrassenSerial.cpp
// Authors     : Nikola Losic
// Version     : 1.0
// Description : Contains definitions of functions for serial version of 
//               Strassen's algorithm for multiplication of matrices
//============================================================================

#include "StrassenSerial.h"
#include "Matrix.h"
#include "2dArray.h"
#include "defines.h"


void strassenSerialMultiply(int **c, int **a, int rowA, int colA,
    int **b, int rowB, int colB, int size) {
    if (size <= GRAIN_SIZE) {
        multiplyMatricesStandard(c, a, rowA, colA, b, rowB, colB, size);
    }
    else {
        int newSize = size / 2;

        int **S1 = allocate2dArray<int>(newSize, newSize);
        int **P1 = allocate2dArray<int>(newSize, newSize);
        // S1 = B12 - B22
        subMatrices(S1,b, rowB, colB + newSize, b, rowB + newSize, colB + newSize, newSize);
        // P1 = A11 * S1
        strassenSerialMultiply(P1, a, rowA, colA, S1, 0, 0, newSize);

        int **S2 = S1;  // don't allocate new memory, just point to old unused array
        int **P2 = allocate2dArray<int>(newSize, newSize);
        // S2 = A11 + A12
        addMatrices(S2,a, rowA, colA, a, rowA, colA + newSize, newSize);
        // P2 = S2 * B22
        strassenSerialMultiply(P2, S2, 0, 0, b, rowB + newSize, colB + newSize, newSize);


        int **S3 = S2;
        int **P3 = allocate2dArray<int>(newSize, newSize);
        // S3 = A21 + A22
        addMatrices(S3, a, rowA + newSize, colA, a, rowA + newSize, colA + newSize, newSize);
        // P3 = S3 * B11
        strassenSerialMultiply(P3, S3, 0, 0, b, rowB, colB, newSize);

        int **S4 = S3;
        int **P4 = allocate2dArray<int>(newSize, newSize);
        // S4 = B21 - B11
        subMatrices(S4, b, rowB + newSize, colB, b, rowB, colB, newSize);
        // P4 = A22 * S4
        strassenSerialMultiply(P4, a, rowA + newSize, colA + newSize, S4, 0, 0, newSize);

        int **S5 = S4;
        int **S6 = allocate2dArray<int>(newSize, newSize);
        int **P5 = allocate2dArray<int>(newSize, newSize);
        // S5 = A11 + A22
        addMatrices(S5, a, rowA, colA, a, rowA + newSize, colA + newSize, newSize);
        // S6 = B11 + B22
        addMatrices(S6, b, rowB, colB, b, rowB + newSize, colB + newSize, newSize);
        // P5 = S5 * S6
        strassenSerialMultiply(P5, S5, 0, 0, S6, 0, 0, newSize);


        int **S7 = S5;
        int **S8 = allocate2dArray<int>(newSize, newSize);
        int **P6 = allocate2dArray<int>(newSize, newSize);
        // S7 = A12 - A22
        subMatrices(S7, a, rowA, colA + newSize, a, rowA + newSize, colA + newSize, newSize);
        // S8 = B21 + B22
        addMatrices(S8,b, rowB + newSize, colB, b, rowB + newSize, colB + newSize, newSize);
        // P6 = S7 * S8
        strassenSerialMultiply(P6, S7, 0, 0, S8, 0, 0, newSize);


        int **S9 = S7;
        int **S10 = S8;
        int **P7 = allocate2dArray<int>(newSize, newSize);
        // S9 = A11 - A21
        subMatrices(S9, a, rowA, colA, a, rowA + newSize, colA, newSize);
        // S10 = B11 + B12
        addMatrices(S10, b, rowB, colB, b, rowB, colB + newSize, newSize);
        // P7 = S9 * S10
        strassenSerialMultiply(P7, S9, 0, 0, S10, 0, 0, newSize);
        free2dArray<int>(S9);
        free2dArray<int>(S10);

        for (int i = 0; i < newSize; i++) {
            for (int j = 0; j < newSize; j++) {
                c[i][j] = P5[i][j] + P4[i][j] - P2[i][j] + P6[i][j];
                c[i][j + newSize] = P1[i][j] + P2[i][j];
                c[i + newSize][j] = P3[i][j] + P4[i][j];
                c[i + newSize][j + newSize] = P5[i][j] + P1[i][j] - P3[i][j] - P7[i][j];
            }
        }

        // free used memory
        free2dArray<int>(P1);
        free2dArray<int>(P2);
        free2dArray<int>(P3);
        free2dArray<int>(P4);
        free2dArray<int>(P5);
        free2dArray<int>(P6);
        free2dArray<int>(P7);
    }
}

void strassenSerial(int **a, int **b, int **c, int size) {
    strassenSerialMultiply(c, a, 0, 0, b, 0, 0, size); // pass call with correct parameters
}
