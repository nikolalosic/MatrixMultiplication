//============================================================================
// File Name   : CmdLineArgsParser.cpp 
// Authors     : Nikola Losic
// Version     : 1.0
// Description : CmdLinArgsParser class implementatio
//============================================================================

#include "CmdLineArgsParser.h"
#include "InvalidArgsException.h"
#include <vector>
#include <sstream>


bool isPowerOf2(int n) {
    return n > 0 && !(n & (n - 1));
}

bool isInt(char const *s, bool positiveOnly) {
    int result;
    try {
        result = std::stoi(s);
    }
    catch(std::invalid_argument &ex){
        return false;
    }
    catch (std::out_of_range &ex) {
        return false;
    }
    return  positiveOnly && result < 0 ? false : true; //-result is positive!
}

std::string getBasename(std::string fullPath) {
    std::stringstream ss(fullPath);
    std::string segment;
    std::vector<std::string> seglist;

    while (std::getline(ss, segment, '\\')) {
        seglist.push_back(segment);
    }
    return seglist[seglist.size() - 1];
}


bool CmdLineArgsParser::argExists(Arguments arg) {
    return args.find(arg) != args.end() ? true : false;
}

std::string CmdLineArgsParser::getArg(Arguments arg) {
    return args.find(arg)->second;
}



void MatrixMulArgsParser::parse(int argc, char *argv[]) {
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if ((arg == "-h") || (arg == "--help")) {
            showUsage(argv[0]);
            return;
        }
        else if ((arg == "-l") || (arg == "--left")) {
            if (i + 1 < argc) { // Make sure we aren't at the end of argv!
                args[MATRIX_LEFT] = argv[++i]; // Increment 'i' so we don't get the argument as the next argv[i].
            }
            else { // Uh-oh, there was no argument to the destination option.
                std::cerr << "--left option requires one argument. See --help for more info." << std::endl;
                throw InvalidArgsException();
            }
        }
        else if ((arg == "-r") || (arg == "--right")) {
            if (i + 1 < argc) { // Make sure we aren't at the end of argv!
                args[MATRIX_RIGHT] = argv[++i]; // Increment 'i' so we don't get the argument as the next argv[i].
            }
            else { // Uh-oh, there was no argument to the destination option.
                std::cerr << "--right option requires one argument. See --help for more info." << std::endl;
                throw InvalidArgsException();
            }
        }

        else if ((arg == "-o") || (arg == "--output")) {
            if (i + 1 < argc) { // Make sure we aren't at the end of argv!
                args[OUTPUT] = argv[++i]; // Increment 'i' so we don't get the argument as the next argv[i].
            }
            else { // Uh-oh, there was no argument to the destination option.
                std::cerr << "--output option requires one argument. See --help for more info." << std::endl;
                throw InvalidArgsException();
            }
        }
        else if ((arg == "-s") || (arg == "--size")) {
            if (i + 1 < argc) { // Make sure we aren't at the end of argv!
                if (!isInt(argv[i + 1])) {
                    std::cerr << "--size must be a positive number. See --help for more info." << std::endl;
                    throw InvalidArgsException();
                }
                if (!isPowerOf2(std::stoi(argv[i + 1]))) {
                    std::cerr << "--size must be a power of 2. See --help for more info." << std::endl;
                    throw InvalidArgsException();
                }
                args[MATRIX_SIZE] = argv[++i]; // Increment 'i' so we don't get the argument as the next argv[i].
            }
            else { // Uh-oh, there was no argument to the destination option.
                std::cerr << "--size option requires one argument. See --help for more info." << std::endl;
                throw InvalidArgsException();
            }
        }
        else if ((arg == "-a") || (arg == "--algorithm")) {
            if (i + 1 < argc) { // Make sure we aren't at the end of argv!
                if (!isInt(argv[i + 1])) {
                    std::cerr << "--algorithm option can contain only specific values. See --help for more info." << std::endl;
                    throw InvalidArgsException();
                }
                if (std::stoi(argv[i + 1]) < 1 || std::stoi(argv[i + 1]) > 2) {
                    std::cerr << "--algorithm option can contain only specific values. See --help for more info." << std::endl;
                    throw InvalidArgsException();
                }
                args[ALGORITHM] = argv[++i]; // Increment 'i' so we don't get the argument as the next argv[i].
            }
            else { // Uh-oh, there was no argument to the destination option.
                std::cerr << "--size option requires one argument. See --help for more info. " << std::endl;
                throw InvalidArgsException();
            }
        }

        else if ((arg == "-rn") || (arg == "--random")) {
            args[RANDOM] = "true";
        }

        else {
            std::cerr << "Invalid arguments. See --help for more info." << std::endl;
            throw InvalidArgsException();
        }
    }

    if (args.find(MATRIX_SIZE) == args.end()) {
        std::cerr << "--size option is [REQUIRED]. See --help for more info." << std::endl;
        throw InvalidArgsException();
    }
    if (args.find(RANDOM) == args.end() &&
        (args.find(MATRIX_LEFT) == args.end() || args.find(MATRIX_RIGHT) == args.end())) {
        std::cerr << "If --random option is not specified --left and --right options are [REQUIRED]. See --help for more info." << std::endl;
        throw InvalidArgsException();
    }

}


void MatrixMulArgsParser::showUsage(std::string name) {
    std::cerr << "Usage: " << getBasename(name) << " <option(s)>\n"
        << "Options:\n"
        << "\t-h, --help\t\tShow this help message" << std::endl
        << "\t-l, --left INPUT\tLeft matrix file path" << std::endl
        << "\t-r, --right INPUT\tRight matrix file path" << std::endl
        << "\t-o, --output OUTPUT\tOutput matrix destination file" << std::endl
        << "\t-s, --size INTEGER\tSize of the input matrices [REQUIRED]" << std::endl
        << "\t-rn, --random\t\tGenerate random matrices." << std::endl
        << "\t-a, --algorithm TYPE\tType can have following values: " << std::endl
        << "\t\t\t\t\t 1 - Serial algorithm" << std::endl
        << "\t\t\t\t\t 2 - Parallel algorithm" << std::endl
        << "\nUsage notes:" << std::endl
        << "1. If --random is not present --left and --right options are [REQUIRED] " << std::endl
        << "2. --left and --right options will be ignored if --random option is present" << std::endl
        << "3. Matrix in the input file must have following format: " << std::endl
        << "\t [1, 2, 3, 4;" << std::endl
        << "\t  5, 6, 7, 8;" << std::endl
        << "\t  9, 10, 11, 12;" << std::endl
        << "\t  13, 14, 15, 16]" << std::endl
        << "   All whitespace characters are ignored." << std::endl
        << "   After the right bracket no content is allowed."<<std::endl
        << "   There is no ; at the end of the last row." << std::endl
        << "4. Size of the matrices must be a power of 2" << std::endl
        << "5. Make sure size of the matrices in the files corespond the parameter specified with --size option." << std::endl
        << "6. If --algorithm option is missing both serial and parallel algorithms will be done. Please note that serial version for big matrices can be really slow" << std::endl
        << "7. This version of program supports only integer numbers. Overflow is not handled so make sure numbers are not big!" << std::endl
        << std::endl;
}