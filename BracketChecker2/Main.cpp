/**
 * @file Main.cpp
 * @brief Entry point for the bracket checking application.
 *
 * This program creates an instance of the BracketChecker2 class
 * and checks the brackets in a specified file.
 */

#include "BracketChecker2.h"

 /**
  * @brief Main function of the program.
  *
  * Creates an instance of BracketChecker2 and checks the brackets
  * in the file "code.txt".
  *
  * @return int Returns 0 upon successful execution.
  */

int main() {
    BracketChecker2 checker;
    checker.checkBrackets("code.txt");
    return 0;
}