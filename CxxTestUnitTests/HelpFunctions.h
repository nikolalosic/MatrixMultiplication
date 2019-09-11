//============================================================================
// File Name   : HelpFunctions.h
// Authors     : Nikola Losic
// Version     : 1.0
// Copyright   : Nikola Losic ©. All rights reserved
// Description : Contains declarations of functions used by test suites
//============================================================================


#pragma once
#include <armadillo>

using namespace arma;

bool compareMatrix(int **a, Mat<int> &b, int rows, int cols);

int **allocateMatrix(int size);


void freeMatrix(int **a, int size);

void copyMatrix(int **a, Mat<int> &b, int size);