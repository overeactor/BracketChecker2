/**
 * @file BracketChecker2.cpp
 * @brief Implementation of the BracketChecker2 class.
 *
 * This file contains the implementation of methods to check if brackets in a file are balanced.
 */

#include "BracketChecker2.h"

 /**
  * @brief Default constructor for BracketChecker2.
  */
BracketChecker2::BracketChecker2() {}

/**
 * @brief Checks if a character is an opening bracket.
 *
 * @param ch The character to check.
 * @return true if the character is an opening bracket, false otherwise.
 */
bool BracketChecker2::isOpeningBracket(char ch) {
    return ch == '(' || ch == '[' || ch == '{';
}

/**
 * @brief Checks if a character is a closing bracket.
 *
 * @param ch The character to check.
 * @return true if the character is a closing bracket, false otherwise.
 */
bool BracketChecker2::isClosingBracket(char ch) {
    return ch == ')' || ch == ']' || ch == '}';
}

/**
 * @brief Checks if an opening and closing bracket form a matching pair.
 *
 * @param open The opening bracket character.
 * @param close The closing bracket character.
 * @return true if the characters form a matching pair, false otherwise.
 */
bool BracketChecker2::isMatchingPair(char open, char close) {
    return (open == '(' && close == ')') ||
        (open == '[' && close == ']') ||
        (open == '{' && close == '}');
}

/**
 * @brief Checks if the brackets in the given file are balanced.
 *
 * Reads a file line by line and checks for unmatched brackets,
 * reporting their positions if found.
 *
 * @param filename The name of the file to check.
 */
void BracketChecker2::checkBrackets(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error: Cannot open file " << filename << endl;
        return;
    }

    stack<pair<char, pair<int, int>>> bracketStack;
    vector<pair<char, pair<int, int>>> errorPositions;
    string line;
    int lineNum = 0;

    while (getline(file, line)) {
        lineNum++;
        for (size_t i = 0; i < line.size(); i++) {
            char ch = line[i];

            if (isOpeningBracket(ch)) {
                bracketStack.push({ ch, {lineNum, i + 1} });
            }
            else if (isClosingBracket(ch)) {
                if (!bracketStack.empty() && isMatchingPair(bracketStack.top().first, ch)) {
                    bracketStack.pop();
                }
                else {
                    errorPositions.push_back({ ch, {lineNum, i + 1} });
                }
            }
        }
    }

    while (!bracketStack.empty()) {
        errorPositions.push_back({ bracketStack.top().first, bracketStack.top().second });
        bracketStack.pop();
    }

    if (errorPositions.empty()) {
        cout << "All brackets are correctly closed." << endl;
    } else {
        cout << "Unmatched brackets found: " << endl;
        for (const auto& error : errorPositions) {
            cout << "Bracket '" << error.first << "' at Line " << error.second.first
                << ", Position " << error.second.second << " is unmatched." << endl;
        }
    }

    file.close();
}