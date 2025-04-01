/**
 * @file BracketChecker2.cpp
 * @brief Implementation file for bracket validation functions.
 */
#include "BracketChecker2.h"


bool isOpeningBracket(char ch) {
    return ch == '(' || ch == '[' || ch == '{';
}



bool isClosingBracket(char ch) {
    return ch == ')' || ch == ']' || ch == '}';
}


bool isMatchingPair(char open, char close) {
    return (open == '(' && close == ')') ||
        (open == '[' && close == ']') ||
        (open == '{' && close == '}');
}




vector<pair<char, pair<int, int>>> read_input_file(const string& filename) 

           

    while (!bracketStack.empty()) {
        errorPositions.push_back({ bracketStack.top().first, bracketStack.top().second });
        bracketStack.pop();
    }

    file.close();
    return errorPositions;
}

void print_result(const string& outputFilename, const vector<pair<char, pair<int, int>>>& errors) {
    ofstream outputFile(outputFilename);
    if (!outputFile) {
        cerr << "Error: Cannot open output file " << outputFilename << endl;
        return;
    }

    if (errors.empty()) {
        outputFile << "All brackets are correctly closed." << endl;
    }
    else {
        outputFile << "Unmatched brackets found: " << endl;
        for (const auto& error : errors) {
            outputFile << "Bracket '" << error.first << "' at Line " << error.second.first
                << ", Position " << error.second.second << " is unmatched." << endl;
        }
    }

    outputFile.close();
}