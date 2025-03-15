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

   