//============================================================================
// File Name   : 2dArray-impl.cpp 
// Authors     : Nikola Losic
// Version     : 1.0
// Description : Contains declarations of template functions for manipulating 2d arrays
//               These declarations are needed so compiler could see definitions of
//               template functions in cpp file
//============================================================================

#include "2dArray.cpp"

template void print2dArray<int>(int **a, int rows, int cols);
template void init2dArrayToValue<int>(int **a, int rows, int cols, int value);
template int **allocate2dArray<int>(int rows, int cols);
template void free2dArray<int>(int** Array);
template int **allocate2dArrayScalable<int>(int rows, int cols);
template void free2dArrayScalable<int>(int** Array);