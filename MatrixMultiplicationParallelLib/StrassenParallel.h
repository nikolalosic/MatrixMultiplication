//============================================================================
// File Name   : StrassenParallel.h
// Authors     : Nikola Losic
// Version     : 1.0
// Description : Contains declarations of functions and class, needed for 
//               executing a tbb task, for parallel version of Strassen's 
//               algorithm for multiplication of matrices
//============================================================================


#pragma once

#include <tbb\task.h>

/**
Class used as a tbb task for parallel version of Strassen's algorithm for matrix multiplication
*/
class StrassenParallel : public tbb::task {
    int **a, rowA, colA, **b, rowB, colB, **c, size;
public:
    StrassenParallel(int **c_, int **a_, int rowA_, int colA_,
        int **b_, int rowB_, int colB_, int size_) :
        a(a_), rowA(rowA_), colA(colA_), b(b_), rowB(rowB_), colB(colB_), c(c_), size(size_) {
    };

    /**
    Task's method where Strassen's algorithm for matrix multiplication is implemented
    */
    tbb::task* execute();

};

/**
Multiplies square matrices using a parallel version of Strassen's algorithm for matrix multiplication

    @param a
        Left matrix
    @param b
        Right matrix
    @param c
        Result matrix
    @param size
        Size of the matrices

*/
void strassenParallel(int **a, int **b, int **c, int size);