//============================================================================
// File Name   : StrassenParallelTestSuite.h
// Authors     : Nikola Losic
// Version     : 1.0
// Copyright   : Nikola Losic. All rights reserved
// Description : Contains definitions of tests for a StrassenParallel.h functions
//============================================================================

#pragma once

#include "StrassenParallel.h"
#include "HelpFunctions.h"
#include <cxxtest/TestSuite.h>
#include <armadillo>
#include <iostream>
#include <random>


using namespace arma;

using namespace std;

class StrassenParallelTestSuite : public CxxTest::TestSuite {

public:
    void testStrassenParallel() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distr(0, 10);
        for (int i = 1;i < 257;i *= 2) {

            Mat<int> armadilloMatA(i, i);
            armadilloMatA.imbue([&]() { return distr(gen); });
            Mat<int> armadilloMatB(i, i);
            armadilloMatB.imbue([&]() { return distr(gen); });
            Mat<int> armadilloMatC = armadilloMatA * armadilloMatB;

            int **matA = allocateMatrix(i);
            int **matB = allocateMatrix(i);
            int **matC = allocateMatrix(i);

            copyMatrix(matA, armadilloMatA, i);
            copyMatrix(matB, armadilloMatB, i);


            strassenParallel(matC, matA, matB, i);

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
