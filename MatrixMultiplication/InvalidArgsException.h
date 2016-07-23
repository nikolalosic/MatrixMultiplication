//============================================================================
// File Name   : InvalidArgsException.h 
// Authors     : Nikola Losic
// Version     : 1.0
// Description : Custom exception thrown when command line arguments are invalid
//============================================================================

#pragma once

#include <exception>
#include <stdexcept>
#include <sstream>

class InvalidArgsException : public std::runtime_error {
private:
    static std::ostringstream cnvt;
public:
    InvalidArgsException();
    virtual const char* what() const throw() {
        cnvt.str("");
        cnvt << std::runtime_error::what() << std::endl;
        return cnvt.str().c_str();
    }
};

