/**
 * @mainpage BracketChecker2 Documentation
 *
 * @section intro Introduction
 * BracketChecker2 is a C++ command-line utility that reads source files,
 * validates code formatting constraints, and parses bracket usage.
 * It detects unmatched or misplaced brackets such as (), {}, and [].
 *
 * @section features Features
 * - Checks for correct bracket pairing and nesting.
 * - Validates line limits (max 1000 lines) and line length (max 1000 characters).
 * - Disallows usage of `#define` macros.
 * - Outputs structured error reports.
 *
 * @section usage Usage
 * @code
 * BracketChecker2 input.cpp result.txt
 * @endcode
 *
 * @section author Author
 * Developed by Bebahani A.
 */

 /**
  * @file BracketChecker2.h
  * @brief Header definitions for BracketChecker2 program.
  *
  * Declares the core types and functions used in reading, validating,
  * parsing, and printing bracket and formatting errors.
  *
  * @author
  * Bebahani A.
  */


#pragma once
#ifndef BRACKETCHECKER2_H  
#define BRACKETCHECKER2_H

#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include <vector>
#include <set>
#include <tuple>





 
using namespace std;





/**
 * @enum BracketErrorType
 * @brief Represents various types of bracket or formatting errors.
 */
enum BracketErrorType { 
    WRONG_BRACKET,    ///< Mismatched closing bracket
    UNMATCHED_BRACKET, ///< Unmatched opening bracket
    TOO_LONG_PROGRAM,  ///< File has more than 1000 lines
    TOO_LONG_LINE, ///< A single line exceeds 1000 characters
    MACRO_USAGE   ///< `#define` macro used in code

};


/**
 * @struct BracketError
 * @brief Struct to hold details about a bracket or formatting error.
 */

struct BracketError
{
    char bracket;
    int line;
    int column;
    BracketErrorType type;
    // Needed for using BracketError in a set (sorted container)
    bool operator<(const BracketError& other) const {
        return tie(line, column, bracket, type) < tie(other.line, other.column, other.bracket, other.type);
    }

};



/**
 * @brief Checks whether a character is an opening bracket.
 * @param ch [in] The character to evaluate.
 * @return True if the character is one of '(', '[', or '{'.
 */
inline bool isOpeningBracket(char ch);


/**
 * @brief Checks whether a character is a closing bracket.
 * @param ch [in] The character to evaluate.
 * @return True if the character is one of ')', ']', or '}'.
 */
inline bool isClosingBracket(char ch);

/**
 * @brief Checks whether two characters form a valid matching bracket pair.
 * @param open [in] The opening bracket character.
 * @param close [in] The closing bracket character.
 * @return True if the pair is valid (i.e., (), {}, []).
 */
inline bool isMatchingPair(char open, char close);


/**
 * @brief Reads all lines from a file.
 * @param filename [in] Path to the input file.
 * @return Vector containing each line as a string.
 */
vector<string> read_input_file(const string& filename);


/**
 * @brief Validates program constraints.
 *
 * Checks line count, line length, and macro usage.
 * @param lines [in] Source code lines to validate.
 * @return Set of bracket errors related to formatting.
 */
set<BracketError> code_validation(const vector<string>& lines);


/**
 * @brief Parses brackets in the source code.
 * @param lines [in] Validated source code lines.
 * @return Set of bracket errors (wrong or unmatched).
 */
set<BracketError> parse_brackets(const vector<string>& lines);


/**
 * @brief Prints errors to an output file.
 * @param outputFilename [in] Path to output result file.
 * @param errors [in] Set of errors to write.
 */
void print_result(const string& outputFilename, const set<BracketError>& errors);



#endif // BRACKETCHECKER2_H