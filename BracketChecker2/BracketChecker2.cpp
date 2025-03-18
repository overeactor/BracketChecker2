

#include "BracketChecker2.h"


BracketChecker2::BracketChecker2() {}


bool BracketChecker2::isOpeningBracket(char ch) {
    return ch == '(' || ch == '[' || ch == '{';
}


bool BracketChecker2::isClosingBracket(char ch) {
    return ch == ')' || ch == ']' || ch == '}';
}


bool BracketChecker2::isMatchingPair(char open, char close) {
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

            if (i < line.size() - 1) {
                if (!inBlockComment && line[i] == '/' && line[i + 1] == '/') {
                    inLineComment = true;
                }
                else if (!inLineComment && line[i] == '/' && line[i + 1] == '*') {
                    inBlockComment = true;
                    i++;
                    continue;
                }
                else if (inBlockComment && line[i] == '*' && line[i + 1] == '/') {
                    inBlockComment = false;
                    i++;
                    continue;
                }
            }