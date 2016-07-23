//============================================================================
// File Name   : CmdLineArgsParser.h 
// Authors     : Nikola Losic
// Version     : 1.0
// Description : Parser used for parsing passed command line arguments
//============================================================================

#pragma once

#include <map>
#include <iostream>


/**
All possible parameters
*/
typedef enum Arguments_ {
    MATRIX_LEFT = 0, // left matrix in a * b expression
    MATRIX_RIGHT,    // right matrix in a*b expression 
    OUTPUT,          // outpu file for the result matrix
    MATRIX_SIZE,            // size of the matrices
    RANDOM,          // random generated matrices flag
    ALGORITHM        // serial or parallel algorithm
} Arguments;

// Command line arguments map
typedef std::map<Arguments, std::string> Args;

/**
Abstract class used for parsing command line arguments
*/
class CmdLineArgsParser {
protected:
    Args args; // command line arguments
public:

    /**
    Parses arguments and puts them in a map

        @param argc
            Number of parameters
        @param argv
            Array of parameters
    */
    virtual void parse(int argc, char *argv[]) = 0;

    /**
    Shows usage help

        @param name
            Name of the program file
    */
    virtual void showUsage(std::string name) = 0;

    /**
    Checks if argument is present
        
        @param arg
            Argument
    */
    virtual bool argExists(Arguments arg);

    /**
    Gets argument
        
        @param arg
            Argument
    */
    virtual std::string getArg(Arguments arg);
};


/**
Concrete implemenation of the parser used for Matrix Multiplication program
*/
class MatrixMulArgsParser : public CmdLineArgsParser {
public:
    void showUsage(std::string name) override;
    void parse(int argc, char *argv[]) override;
};



/**
Checks if number is power of 2
    
    @param n
        Number that is checked
    @return
        True if number is power of 2, false otherwise
*/
bool isPowerOf2(int n);

/**
Checks if array of characters is a integer

    @param s
        Pointer to char array
    @param positiveOnly
        Indicates if only positive integers are acceptable
    @return
        True if number is integer, false otherwise
*/
bool isInt(char const *s, bool positiveOnly = true);

/**
Returns basename of the file

    @param fullPath
        Full path to the file
    @return 
        Basename of the file's full path
*/
std::string getBasename(std::string fullPath);