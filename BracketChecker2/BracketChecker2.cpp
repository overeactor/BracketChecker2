/**
 * @file BracketChecker2.cpp
 * @brief Implementation file for bracket validation functions.
 */
#include "BracketChecker2.h"


inline bool isOpeningBracket(char ch) {
    return ch == '(' || ch == '[' || ch == '{';
}

inline bool isClosingBracket(char ch) {
    return ch == ')' || ch == ']' || ch == '}';
}

inline bool isMatchingPair(char open, char close) {
    return (open == '(' && close == ')') ||
        (open == '[' && close == ']') ||
        (open == '{' && close == '}');
}



vector<string> read_input_file(const string& filename) {


    // 1) Read code from file
    // 2) Validate code bool validate_code(vector<string> code, set<code_error> & errors);

    ifstream file(filename);
    vector<string> lines;

    string line;
    int lineCount = 0;

    while (getline(file, line)) {
        lineCount++;

        if (lineCount > MAX_LINE_COUNT) {
            cerr << "Error: File exceeds maximum allowed lines (" << MAX_LINE_COUNT << ")." << endl;
            return {};
        }

        if (line.length() > MAX_LINE_LENGTH) {
            cerr << "Error: Line " << lineCount << " exceeds max allowed length (" << MAX_LINE_LENGTH << ")." << endl;
            return {};
        }

        lines.push_back(line);
    }

    file.close();
    return lines;
}


set<pair<char, pair<int, int>>> parse_brackets(const vector<string>& lines) {
    stack<pair<char, pair<int, int>>> bracketStack;
    set<pair<char, pair<int, int>>> errorPositions;
    bool inBlockComment = false;

    for (size_t lineNum = 0; lineNum < lines.size(); lineNum++) {
        string line = lines[lineNum];
        bool inLineComment = false;
        bool inString = false;
        char stringDelimiter = '\0';

        for (size_t i = 0; i < line.size(); i++) {
            char ch = line[i];

            // Handle comments
            if (i < line.size() - 1) {
                if (!inBlockComment && line[i] == '/' && line[i + 1] == '/') {
                    inLineComment = true;
                }
                else if (!inLineComment && !inBlockComment && line[i] == '/' && line[i + 1] == '*') {
                    inBlockComment = true;
                    i++; continue;
                }
                else if (inBlockComment && line[i] == '*' && line[i + 1] == '/') {
                    inBlockComment = false;
                    i++; continue;
                }
            }

            // Ignore characters inside comments
            if (inBlockComment || inLineComment) {
                continue;
            }

            // Handle string literals
            if (!inString && (ch == '"' || ch == '\'')) {
                inString = true;
                stringDelimiter = ch;
                continue;
            }
            else if (inString && ch == stringDelimiter) {
                inString = false;
                continue;
            }

            // Ignore brackets inside strings
            if (inString) {
                continue;
            }

            // Process brackets only when NOT inside a string or comment
            if (isOpeningBracket(ch)) {
                bracketStack.push({ ch, {static_cast<int>(lineNum + 1), static_cast<int>(i + 1)} });
            }
            else if (isClosingBracket(ch)) {
                if (!bracketStack.empty() && isMatchingPair(bracketStack.top().first, ch)) {
                    bracketStack.pop();
                }
                else {
                    errorPositions.insert({ ch, {static_cast<int>(lineNum + 1), static_cast<int>(i + 1)} });
                }
            }
        }
    }

    while (!bracketStack.empty()) {
        errorPositions.insert(bracketStack.top());
        bracketStack.pop();
    }

    return errorPositions;
}


void print_result(const string& outputFilename, const set<pair<char, pair<int, int>>>& errors) {
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
