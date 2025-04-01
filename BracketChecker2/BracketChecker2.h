/**
 * @file BracketChecker2.h
 * @brief Header file for bracket validation functions.
 *
 * This file contains function declarations for checking matching brackets
 * in a given input file. It includes utility functions to determine bracket types
 * and handle file input/output operations.
 */


#pragma once
#ifndef BRACKETCHECKER2_H  
#define BRACKETCHECKER2_H

#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include <vector>


 /**
  * @brief Checks if the given character is an opening bracket.
  *
  * @param ch The character to check.
  * @return True if it is an opening bracket, otherwise false.
  */
using namespace std;


/**
 * @brief Checks if the given character is an opening bracket.
 *
 * @param ch The character to check.
 * @return True if it is an opening bracket, otherwise false.
 */
bool isOpeningBracket(char ch);


/**
 * @brief Checks if the given character is a closing bracket.
 *
 * @param ch The character to check.
 * @return True if it is a closing bracket, otherwise false.
 */
bool isClosingBracket(char ch);

/**
 * @brief Checks if the given pair of brackets match.
 *
 * @param open The opening bracket character.
 * @param close The closing bracket character.
 * @return True if they form a valid pair, otherwise false.
 */
bool isMatchingPair(char open, char close);


vector<string> read_input_file(const string& filename);

/**
 * @brief Outputs the result of bracket matching to a file.
 *
 * @param outputFilename The name of the output file.
 * @param errors A vector containing unmatched brackets with their positions.
 */
void print_result(const string& outputFilename, const vector<pair<char, pair<int, int>>>& errors);


#endif // BRACKETCHECKER2_H