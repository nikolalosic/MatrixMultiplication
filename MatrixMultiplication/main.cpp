//============================================================================
// File Name   : main.cpp 
// Authors     : Nikola Losic
// Version     : 1.0
// Description : Start point for the Matrix Multiplication program
//============================================================================

#include "StrassenSerial.h"
#include "StrassenParallel.h"
#include "Matrix.h"
#include "2dArray.h"
#include "CmdLineArgsParser.h"
#include "InvalidArgsException.h"
#include <iostream>
#include <time.h>
#include <tbb\tick_count.h>

#include <iostream>
#include <istream>
#include <fstream>

using namespace std;

void rmFile(int **a, int rows, int cols, std::string fileName) {
    std::ifstream ist(fileName);
    ist.exceptions(ist.exceptions() | std::ios_base::badbit);
    int currentNum;
    char token;
    ist >> token;

    int row = 0;
    for (int i = 0;i < cols;++i) {
        print2dArray(a, rows, cols);
        if (!(ist >> currentNum) || !(ist >> token)) {
            ist.close();
            throw std::runtime_error("Matrix format error");
        }
        if (i == cols - 1) {
            if (row == rows - 1) {
                if (token != ']') {
                    ist.close();
                    throw std::runtime_error("Matrix format error");
                }
                a[row][i] = currentNum;
                break;
            }
            else if (token != ';') {
                ist.close();
                throw std::runtime_error("Matrix format error");
            }
            row++;
            i = -1; /*reset counter, we are loading new row*/
            a[row][i] = currentNum;
            continue;
        }
        else if (token != ',') {
            ist.close();
            throw std::runtime_error("Matrix format error");
        }
        a[row][i] = currentNum;
    }




    while (ist >> token) {
        if (!isspace(token)) {
            ist.close();
            throw std::runtime_error("Matrix format error");
        }
    }
    ist.close();
}


double doSerial(int **a, int **b, int **c, int size) {
    tbb::tick_count start, end;
    cout << "Serial algorithm for " << size << " * " << size << " matrices started. Please wait.." << endl;
    start = tbb::tick_count::now();
    strassenSerial(a, b, c, size);
    end = tbb::tick_count::now();
    cout << "Strassen serial algorithm done in: " << (end - start).seconds() << " seconds!" << endl << endl;
    return (end - start).seconds();
}

double doParallel(int **a, int **b, int **c, int size) {
    tbb::tick_count start, end;
    cout << "Parallel algorithm for " << size << " * " << size << " matrices started. Please wait.." << endl;
    start = tbb::tick_count::now();
    strassenParallel(a, b, c, size);
    end = tbb::tick_count::now();
    cout << "Strassen parallel algorithm done in: " << (end - start).seconds() << " seconds!" << endl;
    return (end - start).seconds();
}


int main(int argc, char *argv[]) {
    srand(time(NULL));
    MatrixMulArgsParser parser;
    try {
        parser.parse(argc, argv);
    }
    catch (InvalidArgsException &e) {
        exit(1);
    }

    int size = std::stoi(parser.getArg(MATRIX_SIZE));

    cout << "Allocating space for left matrix." << endl;
    int **a = allocate2dArrayScalable<int>(size, size);
    cout << "Space for left matrix alocated!" << endl << endl;

    cout << "Allocating space for right matrix." << endl;
    int **b = allocate2dArrayScalable<int>(size, size);
    cout << "Space for left matrix alocated!" << endl << endl;


    cout << "Allocating space for result matrix." << endl;
    int** c = allocate2dArrayScalable<int>(size, size);
    init2dArrayToValue(c, size, size, 0);
    cout << "Space for result matrix alocated!" << endl << endl;


    if (parser.argExists(RANDOM)) {
        cout << "Initializing random matrix A.." << endl;
        initRandomInteger2dArray(a, size, size);
        cout << "Matrix A initialized!" << endl << endl;

        cout << "Initializing random matrix B.." << endl;
        initRandomInteger2dArray(b, size, size);
        cout << "Matrix B initialized!" << endl << endl;
    }
    else {
        cout << "Initializing matrix A from file.." << endl;
        try {
            readMatrixFromFile(a, size, size, parser.getArg(MATRIX_LEFT));
        }
        catch (std::runtime_error &ex) {
            cerr << ex.what() << endl;
            exit(1);
        }
        cout << "Matrix A initialized!" << endl << endl;

        cout << "Initializing matrix B from file.." << endl;
        try {
            readMatrixFromFile(b, size, size, parser.getArg(MATRIX_RIGHT));
        }
        catch (std::runtime_error &ex) {
            cerr << ex.what() << endl;
            exit(1);
        }
        cout << "Matrix B initialized!" << endl << endl;
    }

    if (parser.argExists(ALGORITHM)) {
        int alg = std::stoi(parser.getArg(ALGORITHM));
        if (alg == 1) {
            doSerial(a, b, c, size);
        }
        else {
            doParallel(a, b, c, size);
        }
    }
    else {
        double serial = doSerial(a, b, c, size);
        init2dArrayToValue(c, size, size, 0);
        cout << "Initializing matrix C back to 0.." << endl;
        double parallel = doParallel(a, b, c, size);
        cout << "Parallel version is faster " << serial/parallel << " times than serial version"<<endl;
    }
 
    free2dArrayScalable(a);
    free2dArrayScalable(b);
    

    if (parser.argExists(OUTPUT)) {
        try {
            writeMatrixToFile(c, size, size, parser.getArg(OUTPUT));
        }
        catch (std::runtime_error &ex) {
            cerr << ex.what() << endl;
            exit(1);
            
        }
    }
    free2dArrayScalable(c);

  
    return 0;
}