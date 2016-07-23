//============================================================================
// File Name   : StrassenParallel.cpp
// Authors     : Nikola Losic
// Version     : 1.0
// Description : Contains definitions of functions and class, needed for 
//               executing a tbb task, for parallel version of Strassen's 
//               algorithm for multiplication of matrices
//============================================================================


#include "StrassenParallel.h"
#include "2dArray.h"
#include "Matrix.h"
#include "defines.h"

tbb::task* StrassenParallel::execute() {
    if (size <= GRAIN_SIZE) {
        multiplyMatricesStandard(c, a, rowA, colA, b, rowB, colB, size);
        //strassenSerialMultiply(c, a, rowA, colA, b, rowB, colB, size);
    }
    else {
        int newSize = size / 2;
        
        // First 4 tasks
        // We are splitting tasks to save memory
        set_ref_count(5);
        
        int **S1 = allocate2dArrayScalable<int>(newSize, newSize);
        int **P1 = allocate2dArrayScalable<int>(newSize, newSize);
        // S1 = B12 - B22
        subMatrices(S1, b, rowB, colB + newSize, b, rowB + newSize, colB + newSize, newSize);
        // P1 = A11 * S1
        tbb::task &P1Task = *new(allocate_child()) StrassenParallel(P1, a, rowA, colA, S1, 0, 0, newSize);
        spawn(P1Task);

        int **S2 = allocate2dArrayScalable<int>(newSize, newSize);
        int **P2 = allocate2dArrayScalable<int>(newSize, newSize);
        // S2 = A11 + A12
        addMatrices(S2, a, rowA, colA, a, rowA, colA + newSize, newSize);
        // P2 = S2 * B22
        tbb::task &P2Task = *new(allocate_child()) StrassenParallel(P2, S2, 0, 0, b, rowB + newSize, colB + newSize, newSize);
        spawn(P2Task);

        int **S3 = allocate2dArrayScalable<int>(newSize, newSize);
        int **P3 = allocate2dArrayScalable<int>(newSize, newSize);
        // S3 = A21 + A22
        addMatrices(S3, a, rowA + newSize, colA, a, rowA + newSize, colA + newSize, newSize);
        // P3 = S3 * B11
        tbb::task &P3Task = *new(allocate_child()) StrassenParallel(P3, S3, 0, 0, b, rowB, colB, newSize);
        spawn(P3Task);

        int **S4 = allocate2dArrayScalable<int>(newSize, newSize);
        int **P4 = allocate2dArrayScalable<int>(newSize, newSize);
        // S4 = B21 - B11
        subMatrices(S4, b, rowB + newSize, colB, b, rowB, colB, newSize);
        // P4 = A22 * S4
        tbb::task &P4Task = *new(allocate_child()) StrassenParallel(P4, a, rowA + newSize, colA + newSize, S4, 0, 0, newSize);
        // finish all tasks
        spawn_and_wait_for_all(P4Task);

        for (int i = 0; i < newSize; i++) {
            for (int j = 0; j < newSize; j++) {
                c[i][j] = P4[i][j] - P2[i][j];
                c[i][j + newSize] = P1[i][j] + P2[i][j];
                c[i + newSize][j] = P3[i][j] + P4[i][j];
                c[i + newSize][j + newSize] = P1[i][j] - P3[i][j];
            }
        }
        free2dArrayScalable<int>(P4);

        set_ref_count(4);

        // don't allocate new memory, just point to old unused arrays
        int **P5 = P1;
        int **P6 = P2;
        int **P7 = P3;

        // repoint
        int **S5 = allocate2dArrayScalable<int>(newSize, newSize);
        int **S6 = allocate2dArrayScalable<int>(newSize, newSize);
        int **S7 = S1;
        int **S8 = S2;
        int **S9 = S3;
        int **S10 = S4;

        // S5 = A11 + A22
        addMatrices(S5, a, rowA, colA, a, rowA + newSize, colA + newSize, newSize);
        // S6 = B11 + B22
        addMatrices(S6, b, rowB, colB, b, rowB + newSize, colB + newSize, newSize);
        // P5 = S5 * S6
        tbb::task &P5Task = *new(allocate_child()) StrassenParallel(P5, S5, 0, 0, S6, 0, 0, newSize);
        spawn(P5Task);

        // S7 = A12 - A22
        subMatrices(S7, a, rowA, colA + newSize, a, rowA + newSize, colA + newSize, newSize);
        // S8 = B21 + B22
        addMatrices(S8, b, rowB + newSize, colB, b, rowB + newSize, colB + newSize, newSize);
        // P6 = S7 * S8
        tbb::task &P6Task = *new(allocate_child()) StrassenParallel(P6, S7, 0, 0, S8, 0, 0, newSize);
        spawn(P6Task);

        // S9 = A11 - A21
        subMatrices(S9, a, rowA, colA, a, rowA + newSize, colA, newSize);
        // S10 = B11 + B12
        addMatrices(S10, b, rowB, colB, b, rowB, colB + newSize, newSize);
        // P7 = S9 * S10
        tbb::task &P7Task = *new(allocate_child()) StrassenParallel(P7, S9, 0, 0, S10, 0, 0, newSize);
        spawn_and_wait_for_all(P7Task);
        
        // Free memory as soon as possible
        free2dArrayScalable<int>(S1);
        free2dArrayScalable<int>(S2);
        free2dArrayScalable<int>(S3);
        free2dArrayScalable<int>(S4);
        free2dArrayScalable<int>(S5);
        free2dArrayScalable<int>(S6);

        for (int i = 0; i < newSize; i++) {
            for (int j = 0; j < newSize; j++) {
                c[i][j] = P6[i][j] + P5[i][j];
                c[i + newSize][j + newSize] = P5[i][j] - P7[i][j];
            }
        }
       
        // free memory
        free2dArrayScalable<int>(P1);
        free2dArrayScalable<int>(P2);
        free2dArrayScalable<int>(P3);

    }
    return nullptr;
}



void strassenParallel(int **a, int **b, int **c, int size) {
    StrassenParallel& root = *new(tbb::task::allocate_root()) StrassenParallel(c, a, 0, 0, b, 0, 0, size); // create task
    tbb::task::spawn_root_and_wait(root);
}
