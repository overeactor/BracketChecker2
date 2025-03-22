
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




vector<pair<char, pair<int, int>>> read_input_file(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error: Cannot open file " << filename << endl;
        return {};
    }


    
    stack<pair<char, pair<int, int>>> bracketStack;
    vector<pair<char, pair<int, int>>> errorPositions;
    string line;
    int lineNum = 0;
    bool inBlockComment = false;

    
    
    while (getline(file, line)) {
        lineNum++;
        bool inLineComment = false;

        for (size_t i = 0; i < line.size(); i++) {
            char ch = line[i];

            // Handle comments correctly
            if (i < line.size() - 1) {
                if (!inBlockComment && line[i] == '/' && line[i + 1] == '/') {
                    inLineComment = true;
                }
                else if (!inLineComment && !inBlockComment && line[i] == '/' && line[i + 1] == '*') {
                    inBlockComment = true;
                    i++; // Skip next character
                    continue;
                }
                else if (inBlockComment && line[i] == '*' && line[i + 1] == '/') {
                    inBlockComment = false;
                    i++; // Skip next character
                    continue;
                }
            }


            // Ensure brackets inside both block and line comments are ignored completely
            if (inBlockComment || inLineComment) {
                continue;
            }

            // Process brackets only when NOT inside any type of comment
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