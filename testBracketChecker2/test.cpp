#include "pch.h"
#include <gtest/gtest.h>
#include <set>
#include "../BracketChecker2/BracketChecker2.h"  
#include "../BracketChecker2/BracketChecker2.cpp"  

using namespace std;

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
    EXPECT_FALSE(lines.empty()) << "File should be read successfully.";
}

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
    set<pair<char, pair<int, int>>> errors = parse_brackets(code);
    EXPECT_TRUE(errors.empty()) << "Expected no unmatched brackets.";
}

TEST(testBracketChecker2, UnbalancedBrackets) {
    vector<string> code = {
        "int main() {",
        "    if (true) {",
        "        cout << \"Hello\";",
        "}" // Missing closing '}'
    };
    set<pair<char, pair<int, int>>> errors = parse_brackets(code);
    EXPECT_FALSE(errors.empty()) << "Expected unmatched brackets.";
}

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
    set<pair<char, pair<int, int>>> errors = parse_brackets(code);
    EXPECT_TRUE(errors.empty()) << "Expected no unmatched brackets, but some were found.";
}

TEST(testBracketChecker2, EmptyFile) {
    vector<string> code = {};
    set<pair<char, pair<int, int>>> errors = parse_brackets(code);
    EXPECT_TRUE(errors.empty()) << "Expected no errors for an empty file.";
}

TEST(testBracketChecker2, OnlyComments) {
    vector<string> code = {
        "// This is a comment with { brackets }",
        "/* multi-line comment with [ brackets ] inside */"
    };
    set<pair<char, pair<int, int>>> errors = parse_brackets(code);
    EXPECT_TRUE(errors.empty()) << "Expected no errors for a file with only comments.";
}

TEST(testBracketChecker2, onlyWhitespace) {
    vector<string> code = {
        "   ",
        "\t\t"
    };
    set<pair<char, pair<int, int>>> errors = parse_brackets(code);
    EXPECT_TRUE(errors.empty()) << "Expected no errors for a file with only white spaces";
}

TEST(testBracketChecker2, IgnoresBracketsInsideStringLiterals) {
    vector<string> code = {
        "int main() {",
        "    string str = \"This is a string with brackets ( inside  here\";", // Inside string
        "    return 0;",
        "}"
    };
    set<pair<char, pair<int, int>>> errors = parse_brackets(code);
    EXPECT_TRUE(errors.empty()) << "The program incorrectly detected unmatched brackets inside string literals.";
}

TEST(BracketChecker2Test, MinimalNestedMismatch_Set) {
    vector<string> input = {
        "({) }"
    };

    set<pair<char, pair<int, int>>> expected = {
        {')', {1, 3}},
        {'(', {1, 1}}
    };

    auto actual = parse_brackets(input);
    EXPECT_EQ(expected, actual);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
