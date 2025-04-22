



/**
 * @file main.cpp
 * @brief Entry point for the BracketChecker2 program.
 *
 * This file contains the main function that handles user input for a C++ source file,
 * validates the file extension, checks for unmatched brackets using the BracketChecker2 module,
 * and writes the results to an output file.
 */

#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <fstream>


#include "BracketChecker2.h"

using namespace std;

/**
 * @brief Checks whether a file has a .cpp extension.
 *
 * This helper function is used to ensure the input file is a valid C++ source file
 * by checking its extension.
 *
 * @param filename The name of the file to check.
 * @return true if the file ends with ".cpp", false otherwise.
 */
bool has_cpp_extension(const string& filename) {
	size_t dotPos = filename.rfind('.');
	return dotPos != string::npos && filename.substr(dotPos) == ".cpp";
}

/**
 * @brief Main entry point of the program.
 *
 * Accepts input/output file names, performs validation and parsing,
 * and writes results to the specified output file.
 *
 * @param argc [in] Number of command-line arguments.
 * @param argv [in] Array of command-line argument strings.
 * @return int Exit status: 0 on success, 1 on error.
 */
int main(int argc, char* argv[]) {
    if (argc < 3) {
        cerr << "Usage: BracketChecker2 <validation.cpp> <result.txt>" << endl;
        return 1;
    }

    string inputFile = argv[1];
    string outputFile = argv[2];

    if (!has_cpp_extension(inputFile)) {
        cerr << "Error: Invalid file extension. Please provide a .cpp file." << endl;
        return 1;
    }

    vector<string> lines = read_input_file(inputFile);
    set<BracketError> validationErrors = code_validation(lines);

    if (!validationErrors.empty()) {
        print_result(outputFile, validationErrors);
        cerr << "Validation failed. See result.txt for details." << endl;
        return 1;
    }

    set<BracketError> parseErrors = parse_brackets(lines);
    print_result(outputFile, parseErrors);

    cout << "Bracket checking complete. Results saved to " << outputFile << endl;
    return 0;
}

