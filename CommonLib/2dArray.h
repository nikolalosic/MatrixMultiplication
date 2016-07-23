//============================================================================
// File Name   : 2dArray.h 
// Authors     : Nikola Losic
// Version     : 1.0
// Description : Contains declarations of functions for manipulating 2d arrays
//============================================================================

#pragma once

/**
Template function for printing a 2d array

    @param a
        Array
    @param rows
        Number of rows in the array
    @param cols
        Number of columns in the array
*/
template <typename T>
void print2dArray(T **a, int rows, int cols);

/**
Template function used to initialize array to the specific values
    @param a
        Array
    @param rows
        Number of rows in the array
    @param cols
        Number of columns in the array
    @param value
        Value used for initializing array
*/
template <typename T>
void init2dArrayToValue(T **a, int rows, int cols, T value);

/**
Template function used to allocate 2d array

    @param rows
        Number of rows in the array
    @param cols
        Number of columns in the array
    @return
        Allocated array
*/
template <typename T>
T **allocate2dArray(int rows, int cols);

/**
Template function used to free memory allocated by allocate2DArray function

    @param Array
        Allocated array
*/
template <typename T>
void free2dArray(T** Array);

/**
Template function used to allocate 2d array using scalable malloc
    @param rows
        Number of rows in the array
    @param cols
        Number of columns in the array
    @return
        Allocated array

*/
template <typename T>
T **allocate2dArrayScalable(int rows, int cols);


/**
Template function used to free memory allocated by allocate2DArrayScalable function

    @param Array
        Allocated array
*/
template <typename T>
void free2dArrayScalable(T** Array);


/**
Initializes 2d array to random integers

    @param a
        Destination array
    @param rows
        Number of rows in the array
    @param cols
        Number of columns in the array

*/
void initRandomInteger2dArray(int **a, int rows, int cols);


/**
Allocates 2d array and initializes it to random integers

    @param rows
        Number of rows in the array
    @param cols
        Number of columns in the array
    @return
        Allocated and initialized 2d array
*/
int **generateRandomInteger2dArray(int rows, int cols);


/**
Compares two 2d integer arrays

    @param a
        First array
    @param b
        Second array
    @return 
        True if arrays have all the elements same, false otherwise
*/
bool compareInteger2dArray(int **a, int **b, int  rows, int cols);

