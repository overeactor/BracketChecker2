#include "pch.h"
#include <gtest/gtest.h>
#include "../BracketChecker2/BracketChecker2.h"  
#include "../BracketChecker2/BracketChecker2.cpp"  


TEST(testBracketChecker2, IsOpeningBracket) {
    EXPECT_TRUE(isOpeningBracket('('));
    EXPECT_TRUE(isOpeningBracket('{'));
    EXPECT_TRUE(isOpeningBracket('['));
    EXPECT_FALSE(isOpeningBracket('x'));
    EXPECT_FALSE(isOpeningBracket(')'));
}

TEST(testBracketChecker2, IsClosingBracket) {
    EXPECT_TRUE(isClosingBracket(')'));
    EXPECT_TRUE(isClosingBracket('}'));
    EXPECT_TRUE(isClosingBracket(']'));
    EXPECT_FALSE(isClosingBracket('('));
    EXPECT_FALSE(isClosingBracket('a'));
}

TEST(testBracketChecker2, IsMatchingPair) {
    EXPECT_TRUE(isMatchingPair('(', ')'));
    EXPECT_TRUE(isMatchingPair('[', ']'));
    EXPECT_TRUE(isMatchingPair('{', '}'));
    EXPECT_FALSE(isMatchingPair('(', ']'));
    EXPECT_FALSE(isMatchingPair('{', ')'));
}


TEST(testBracketChecker2, ReadInputFile) {
    vector<string> lines = read_input_file("test_input.txt");

    cout << "Number of lines read: " << lines.size() << endl; // Debug print

    EXPECT_FALSE(lines.empty()) << "File should be read successfully.";
}





// Test parsing balanced brackets
TEST(testBracketChecker2, BalancedBrackets) {
    vector<string> code = {
        "int main() {",
        "    if (true) {",
        "        for (int i = 0; i < 10; i++) {",
        "            cout << \"Hello\";",
        "        }",
        "    }",
        "}"
    };
    vector<pair<char, pair<int, int>>> errors = parse_brackets(code);
    EXPECT_TRUE(errors.empty()) << "Expected no unmatched brackets.";
}


// Test detecting unbalanced brackets
TEST(testBracketChecker2, UnbalancedBrackets) {
    vector<string> code = {
        "int main() {",
        "    if (true) {",
        "        cout << \"Hello\";",
        "}" // Missing closing '}'
    };
    vector<pair<char, pair<int, int>>> errors = parse_brackets(code);
    EXPECT_FALSE(errors.empty()) << "Expected unmatched brackets.";
}


// Test ignoring brackets inside comments and strings
TEST(testBracketChecker2, IgnoresCommentsAndStrings) {
    vector<string> code = {
        "int main() {", // Valid opening
        "    string s = \"{ not a bracket }\";", // Inside string
        "    char c = '{'; // Character constant", // Inside char
        "    /* block comment with [ brackets ] */", // Block comment
        "    // single-line comment with { bracket", // Single-line comment
        "    return 0;",
        "}" // Valid closing
    };
    vector<pair<char, pair<int, int>>> errors = parse_brackets(code);
    EXPECT_TRUE(errors.empty()) << "Expected no unmatched brackets, but some were found.";
}

// Test an empty file
TEST(testBracketChecker2, EmptyFile) {
    vector<string> code = {};
    vector<pair<char, pair<int, int>>> errors = parse_brackets(code);
    EXPECT_TRUE(errors.empty()) << "Expected no errors for an empty file.";
}

//test an empty file
TEST(testBrscketChecker2, OnlyComments) {
    vector<string> code = {
        "// This is a comment with { brackets }",
        "/* multi-line comment with [ brackets ] isnside */"
    };
    vector<pair<char, pair<int, int>>> errors = parse_brackets(code);
    EXPECT_TRUE(errors.empty()) << "expected no errors for a file with only comments. ";
}

// test only white space
TEST(testBracketChecker2, onlyWhitespace) {
    vector<string> code = {
        "   ",
        "\t\t"
    };
    vector<pair<char, pair<int, int>>> errors = parse_brackets(code);
    EXPECT_TRUE(errors.empty()) << "Expected no errors for a file with only white spaces";
}


// Test ignoring brackets inside string literals
TEST(testBracketChecker2, IgnoresBracketsInsideStringLiterals) {
    vector<string> code = {
        "int main() {",
        "    string str = \"This is a string with brackets ( inside  here\";", // Inside string
        "    return 0;",
        "}"
    };
    vector<pair<char, pair<int, int>>> errors = parse_brackets(code);

    // Since the brackets inside the string should be ignored, there should be no errors
    EXPECT_TRUE(errors.empty()) << "The program incorrectly detected unmatched brackets inside string literals.";
}




int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}