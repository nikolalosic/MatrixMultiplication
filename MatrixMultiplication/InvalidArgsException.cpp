//============================================================================
// File Name   : InvalidArgsException.cpp 
// Authors     : Nikola Losic
// Version     : 1.0
// Description :Implementation of the InvalidArgsException class
//============================================================================

#include "InvalidArgsException.h"


std::ostringstream InvalidArgsException::cnvt;

InvalidArgsException::InvalidArgsException()
    : runtime_error("Invalid command line arguments.\n") {
}