//============================================================================
// File Name   : MatrixTestSuite.h
// Authors     : Nikola Losic
// Version     : 1.0
// Copyright   : Nikola Losic. All rights reserved
// Description : Contains definitions of tests for a Matrix.h functions
//============================================================================

#pragma once

#include <cxxtest/TestSuite.h>
#include "Matrix.h"
#include "2dArray.h"
#include <armadillo>
#include <iostream>
#include <random>
#include "HelpFunctions.h"
#include <windows.h>


using namespace arma;

using namespace std;

class MatrixTestSuite : public CxxTest::TestSuite {

public:
    void testMultiplyMatricesStandard() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distr(0, 10);
        for (int i = 1;i < 257;i *= 2) {
            Mat<int> armadilloMatA(i, i);
            armadilloMatA.imbue([&]() { return distr(gen); });
            Mat<int> armadilloMatB(i, i);
            armadilloMatB.imbue([&]() { return distr(gen); });
            Mat<int> armadilloMatC = armadilloMatA*armadilloMatB;

            int **matA = allocateMatrix(i);
            int **matB = allocateMatrix(i);
            int **matC = allocateMatrix(i);

            copyMatrix(matA, armadilloMatA, i);
            copyMatrix(matB, armadilloMatB, i);

            multiplyMatricesStandard(matC, matA, 0, 0, matB, 0, 0, i);
            TS_ASSERT_EQUALS(compareMatrix(matC, armadilloMatC, i, i), true);

            freeMatrix(matA, i);
            freeMatrix(matB, i);
            freeMatrix(matC, i);

        }

    }

    void testAddMatrices() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distr(0, 10);
        for (int i = 1;i < 257;i *= 2) {

            Mat<int> armadilloMatA(i, i);
            armadilloMatA.imbue([&]() { return distr(gen); });
            Mat<int> armadilloMatB(i, i);
            armadilloMatB.imbue([&]() { return distr(gen); });
            Mat<int> armadilloMatC = armadilloMatA + armadilloMatB;

            int **matA = allocateMatrix(i);
            int **matB = allocateMatrix(i);
            int **matC = allocateMatrix(i);

            copyMatrix(matA, armadilloMatA, i);
            copyMatrix(matB, armadilloMatB, i);

            addMatrices(matC, matA, 0, 0, matB, 0, 0, i);

            TS_ASSERT_EQUALS(compareMatrix(matC, armadilloMatC, i, i), true);


            freeMatrix(matA, i);
            freeMatrix(matB, i);
            freeMatrix(matC, i);

        }
    }

    void testSubMatrices() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distr(0, 10);

        for (int i = 1;i < 257;i *= 2) {

            Mat<int> armadilloMatA(i, i);
            armadilloMatA.imbue([&]() { return distr(gen); });
            Mat<int> armadilloMatB(i, i);
            armadilloMatB.imbue([&]() { return distr(gen); });
            Mat<int> armadilloMatC = armadilloMatA - armadilloMatB;

            int **matA = allocateMatrix(i);
            int **matB = allocateMatrix(i);
            int **matC = allocateMatrix(i);

            copyMatrix(matA, armadilloMatA, i);
            copyMatrix(matB, armadilloMatB, i);

            subMatrices(matC, matA, 0, 0, matB, 0, 0, i);
            

            TS_ASSERT_EQUALS(compareMatrix(matC, armadilloMatC, i, i), true);


            freeMatrix(matA, i);
            freeMatrix(matB, i);
            freeMatrix(matC, i);

        }
    }

    void setUp() {

    }
    void tearDown() {

    }


};
