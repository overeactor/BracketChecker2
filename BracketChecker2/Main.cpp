/**
 * @mainpage BracketChecker2
 *
 * @section intro_sec Overview
 * BracketChecker2 is a command-line C++ tool that scans source code files
 * for unmatched or incorrectly paired brackets. It supports detection of:
 * - Parentheses `()`
 * - Curly braces `{}`
 * - Square brackets `[]`
 *
 * @section author_sec Author
 * Developed by [Bebahani A.]
 */



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
 * @brief Main function for the BracketChecker2 program.
 *
 * Prompts the user for an input C++ file name. Validates that the file has a `.cpp` extension.
 * Reads the contents of the file, checks for unmatched brackets using the BracketChecker2 module,
 * and writes the results to a file named `result.txt`.
 *
 * @return int Returns 0 on success, or 1 on failure (e.g., invalid file extension).
 */
int main() {
    string inputFile;
    cout << "Enter the input filename (.cpp): ";
    cin >> inputFile;

    if (!has_cpp_extension(inputFile)) {
        cerr << "Error: Invalid file extension. Please provide a .cpp file." << endl;
        return 1;
    }

    string outputFile = "result.txt";

    vector<string> lines = read_input_file(inputFile);
    if (lines.empty()) {
        cerr << "Parsing aborted due to input errors or constraint violation." << endl;
        return 1;
    }
    
    set<BracketError> errors = parse_brackets(lines);
    print_result(outputFile, errors);


    cout << "Bracket checking complete. Results saved to " << outputFile << endl;

    return 0;
}

