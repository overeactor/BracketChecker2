/**
 * @file Main.cpp
 * @brief Main entry point for the Bracket Checker program.
 */

#include "BracketChecker2.h"

 
 /**
  * @brief The main function of the program.
  *
  * this function Reads an input file, parses it for unmatched brackets, and writes the results to an output file.
  *
  * @return 0 on successful execution.
  */
int main() {
	string inputFile = "code.txt";
	string outputFile = "result.txt";

	vector<string> lines = read_input_file(inputFile);
	vector<pair<char, pair<int, int>>> errors = parse_brackets(lines);


	cout << "Bracket checking complete. Results saved to " << outputFile << endl;

	return 0;

	
}


/**
 * @mainpage Bracket Checker Documentation
 *
 * @section intro Introduction
 * This project is a simple bracket validation tool that scans a text file
 * and verifies that all brackets (parentheses, square brackets, and curly braces) are correctly matched.
 *
 * @section usage Usage
 * - The program reads an input file containing code or text.
 * - It detects any unmatched opening or closing brackets.
 * - The results are written to an output file.
 *
 * @section author Author
 * Created by [Bebahani asl A]
 *
 */