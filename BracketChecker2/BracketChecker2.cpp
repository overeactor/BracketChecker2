/**
 * @file BracketChecker2.cpp
 * @brief Implementation file for bracket validation functions.
 */
#include "BracketChecker2.h"



vector<string> read_input_file(const string& filename) {
    ifstream file(filename);
    vector<string> lines;

    if (!file.is_open()) {
        cerr << "Error: Cannot open file " << filename << endl;
        return {};
    }

    string line;
    while (getline(file, line)) {
        lines.push_back(line);
    }

    file.close();
    return lines;
}



set<BracketError> code_validation(const vector<string>& lines) {
    set<BracketError> errors;

    if (lines.size() >= 1000) {
        errors.insert({ '\0', static_cast<int>(lines.size()), 1, TOO_LONG_PROGRAM });
        return errors;
    }

    for (size_t i = 0; i < lines.size(); i++) {
        const string& line = lines[i];

        if (line.length() >= 1000) {
            errors.insert({ '\0', static_cast<int>(i + 1), 1001, TOO_LONG_LINE });
        }

        size_t pos = line.find("#define");
        if (pos != string::npos) {
            errors.insert({ '#', static_cast<int>(i + 1), static_cast<int>(pos + 1), MACRO_USAGE });
        }
    }

    return errors;
}


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
        outputFile << "Unmatched or invalid constructs found: " << endl;
        for (const auto& error : errors) {
            outputFile << "At Line " << error.line << ", Column " << error.column << ": ";

            switch (error.type) {
            case WRONG_BRACKET:
                outputFile << "Wrong closing bracket '" << error.bracket << "'.";
                break;
            case UNMATCHED_BRACKET:
                outputFile << "Unmatched opening bracket '" << error.bracket << "'.";
                break;
            case TOO_LONG_PROGRAM:
                outputFile << "Too many lines in the program.";
                break;
            case TOO_LONG_LINE:
                outputFile << "Line exceeds maximum length.";
                break;
            case MACRO_USAGE:
                outputFile << "Usage of #define is not allowed.";
                break;
            }

            outputFile << endl;
        }
    }

    outputFile.close();
}

