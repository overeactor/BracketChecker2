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

    cout << filename << endl;
    
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


// Parses brackets in the code lines and identifies unmatched or wrong ones
set<BracketError> parse_brackets(const vector<string>& lines) {
    stack<pair<char, pair<int, int>>> bracketStack;
    set<BracketError> errorPositions;
    bool inBlockComment = false;

    for (size_t lineNum = 0; lineNum < lines.size(); lineNum++) {
        string line = lines[lineNum];
        bool inLineComment = false;
        bool inString = false;
        char stringDelimiter = '\0';

        for (size_t i = 0; i < line.size(); i++) {
            char ch = line[i];

            // Handle comment blocks and line comments
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

            if (inBlockComment || inLineComment) continue;

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

            if (inString) continue;

            // Bracket validation logic
            if (isOpeningBracket(ch)) {
                bracketStack.push({ ch, {static_cast<int>(lineNum + 1), static_cast<int>(i + 1)} });
            }
            else if (isClosingBracket(ch)) {
                if (!bracketStack.empty() && isMatchingPair(bracketStack.top().first, ch)) {
                    bracketStack.pop();
                }
                else {
                    errorPositions.insert({ ch, static_cast<int>(lineNum + 1), static_cast<int>(i + 1), WRONG_BRACKET });
                }
            }
        }
    }

    // Remaining opening brackets are unmatched
    while (!bracketStack.empty()) {
        auto top = bracketStack.top();
        errorPositions.insert({ top.first, top.second.first, top.second.second, UNMATCHED_BRACKET });
        bracketStack.pop();
    }

    return errorPositions;
}


void print_result(const string& outputFilename, const set<BracketError>& errors) {
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
            outputFile << "Bracket '" << error.bracket << "' at Line " << error.line
                << ", Column " << error.column << " — ";

            switch (error.type) {
            case WRONG_BRACKET:
                outputFile << "Wrong closing bracket.";
                break;
            case UNMATCHED_BRACKET:
                outputFile << "Unmatched opening bracket.";
                break;
            case TOO_LONG_PROGRAM:
                outputFile << "File exceeds maximum line count.";
                break;
            case TOO_LONG_LINE:
                outputFile << "Line exceeds maximum allowed length.";
                break;
            }

            outputFile << endl;
        }
    }

    outputFile.close();
}
