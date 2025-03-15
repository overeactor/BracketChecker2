/**
 * @file BracketChecker2.h
 * @brief Header file for the BracketChecker2 class.
 *
 * This class provides functionality to check for balanced brackets in a given file.
 */
#pragma once
#ifndef BRACKETCHECKER2_H  
#define BRACKETCHECKER2_H

#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

/**
 * @class BracketChecker2
 * @brief A class to check for balanced brackets in a file.
 */
class BracketChecker2 {
public:
	/**
	 * @brief Constructor for BracketChecker2.
	 */
	BracketChecker2();
	
	/**
	 * @brief Checks the brackets in the given file.
	 * @param filename The name of the file to check.
	 */
	void checkBrackets(const string& filename);

private:
	/**
	* @brief Checks if a character is an opening bracket.
	* @param ch Character to check.
	* @return True if opening bracket, false otherwise.
	*/
	bool isOpeningBracket(char ch);
	/**
	 * @brief Checks if a character is a closing bracket.
	 * @param ch Character to check.
	 * @return True if closing bracket, false otherwise.
	 */
	bool isClosingBracket(char ch);
	/**
	 * @brief Checks if two characters are matching bracket pairs.
	 * @param open Opening bracket character.
	 * @param close Closing bracket character.
	 * @return True if they match, false otherwise.
	 */
	bool isMatchingPair(char open, char close);

};




#endif // BRACKETCHECKER2_H