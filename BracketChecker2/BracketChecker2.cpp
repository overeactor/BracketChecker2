/**
 * @file BracketChecker2.cpp
 * @brief Implementation file for bracket validation functions.
 */
#include "BracketChecker2.h"


 // Reads lines from a given file and returns them as a vector of strings
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


// Validates code formatting: max number of lines, max line length, and no macro usage
set<BracketError> code_validation(const vector<string>& lines) {
    set<BracketError> errors;
    // Check for too many lines
    if (lines.size() >= 1000) {
        errors.insert({ '\0', static_cast<int>(lines.size()), 1, TOO_LONG_PROGRAM });
        return errors;
    }

    for (size_t i = 0; i < lines.size(); i++) {
        const string& line = lines[i];
        
        // Check for long lines
        if (line.length() >= 1000) {
            errors.insert({ '\0', static_cast<int>(i + 1), 1001, TOO_LONG_LINE });
        }
        // Check for usage of #define macros
        size_t pos = line.find("#define");
        if (pos != string::npos) {
            errors.insert({ '#', static_cast<int>(i + 1), static_cast<int>(pos + 1), MACRO_USAGE });
        }
    }

    return errors;
}

// Helper: Returns true if character is an opening bracket
inline bool isOpeningBracket(char ch) {
    return ch == '(' || ch == '[' || ch == '{';
}
// Helper: Returns true if character is a closing bracket
inline bool isClosingBracket(char ch) {
    return ch == ')' || ch == ']' || ch == '}';
}
// Helper: Checks if the open and close brackets form a matching pair
inline bool isMatchingPair(char open, char close) {
    return (open == '(' && close == ')') ||
        (open == '[' && close == ']') ||
        (open == '{' && close == '}');
}


// Parses brackets in the given lines and detects unmatched or wrong bracket pairs
set<BracketError> parse_brackets(const vector<string>& lines) {
    stack<pair<char, pair<int, int>>> bracketStack; // Stack stores (bracket, (line, column))
    set<BracketError> errorPositions;
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
                    inLineComment = true;// Start of single-line comment
                }
                else if (!inLineComment && !inBlockComment && line[i] == '/' && line[i + 1] == '*') {
                    inBlockComment = true; // Start of block comment
                    i++; continue;
                }
                else if (inBlockComment && line[i] == '*' && line[i + 1] == '/') {
                    inBlockComment = false; // End of block comment
                    i++; continue;
                }
            }

            if (inBlockComment || inLineComment) continue;

            // Normalize fancy quotes: “ ” → " and ‘ ’ → '
            if (!inString && (ch == '"' || ch == '\'' || ch == '“' || ch == '”' || ch == '‘' || ch == '’')) {
                inString = true;

                // Normalize fancy quote to standard quote type
                if (ch == '“' || ch == '”') {
                    stringDelimiter = '"';
                }
                else if (ch == '‘' || ch == '’') {
                    stringDelimiter = '\'';
                }
                else {
                    stringDelimiter = ch;
                }

                continue;
            }
            // If inside string, and we hit a matching closing quote (even a fancy one), exit
            else if (inString && (
                ch == stringDelimiter ||
                (stringDelimiter == '"' && (ch == '“' || ch == '”')) ||
                (stringDelimiter == '\'' && (ch == '‘' || ch == '’'))
                )) {
                inString = false;
                continue;
            }

            if (inString) continue;
            // Handle brackets
            if (isOpeningBracket(ch)) {
                bracketStack.push({ ch, {static_cast<int>(lineNum + 1), static_cast<int>(i + 1)} });
            }
            else if (isClosingBracket(ch)) {
                if (!bracketStack.empty() && isMatchingPair(bracketStack.top().first, ch)) {
                    bracketStack.pop();
                }
                else {  // Wrong closing bracket
                    errorPositions.insert({ ch, static_cast<int>(lineNum + 1), static_cast<int>(i + 1), WRONG_BRACKET });
                }
            }
        }
    }
    // Add remaining unmatched opening brackets
    while (!bracketStack.empty()) {
        auto top = bracketStack.top();
        errorPositions.insert({ top.first, top.second.first, top.second.second, UNMATCHED_BRACKET });
        bracketStack.pop();
    }

    return errorPositions;
}





// Writes the bracket and formatting errors to an output file
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

