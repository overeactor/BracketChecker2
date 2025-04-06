#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <fstream>


#include "BracketChecker2.h"

using namespace std;


bool has_cpp_extension(const string& filename) {
	size_t dotPos = filename.rfind('.');
	return dotPos != string::npos && filename.substr(dotPos) == ".cpp";
}


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
    vector<pair<char, pair<int, int>>> errors = parse_brackets(lines);

    print_result(outputFile, errors);

    cout << "Bracket checking complete. Results saved to " << outputFile << endl;

    return 0;
}

