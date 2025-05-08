#include "pch.h"
#include <gtest/gtest.h>
#include <set>
#include "../BracketChecker2/BracketChecker2.h"  
#include "../BracketChecker2/BracketChecker2.cpp"  // --- replace function headers from BracketChecker2.cpp to BracketChecker2.h


using namespace std;

/**
 * @test Tests detection of '(' as an unmatched opening bracket.
 */
TEST(testBracketChecker2, DetectUnmatchedOpeningParenthesis) {
    vector<string> code = { "(", "" };
    set<BracketError> expected = {
        {'(', 1, 1, UNMATCHED_BRACKET}
    };
    EXPECT_EQ(parse_brackets(code), expected);
}

/**
 * @test Tests detection of '{' as an unmatched opening bracket.
 */
TEST(testBracketChecker2, DetectUnmatchedOpeningBrace) {
    vector<string> code = { "{", "" };
    set<BracketError> expected = {
        {'{', 1, 1, UNMATCHED_BRACKET}
    };
    EXPECT_EQ(parse_brackets(code), expected);
}

/**
 * @test Tests detection of '[' as an unmatched opening bracket.
 */
TEST(testBracketChecker2, DetectUnmatchedOpeningSquareBracket) {
    vector<string> code = { "[", "" };
    set<BracketError> expected = {
        {'[', 1, 1, UNMATCHED_BRACKET}
    };
    EXPECT_EQ(parse_brackets(code), expected);
}

/**
 * @test Tests that non-bracket characters like 'x' and ')' are ignored or identified as unmatched closing brackets.
 */


TEST(testBracketChecker2, IgnoreNonOpeningBrackets) {
    vector<string> code = { "x)" };
    set<BracketError> expected = {
        {')', 1, 2, WRONG_BRACKET}
    };
    EXPECT_EQ(parse_brackets(code), expected);
}

/**
 * @test Tests detection of ')' as an unmatched closing bracket.
 */
TEST(testBracketChecker2, DetectUnmatchedClosingParenthesis) {
    vector<string> code = { ")" };
    set<BracketError> expected = {
        {')', 1, 1, WRONG_BRACKET}
    };
    EXPECT_EQ(parse_brackets(code), expected);
}

/**
 * @test Tests detection of '}' as an unmatched closing bracket.
 */
TEST(testBracketChecker2, DetectUnmatchedClosingBrace) {
    vector<string> code = { "}" };
    set<BracketError> expected = {
        {'}', 1, 1, WRONG_BRACKET}
    };
    EXPECT_EQ(parse_brackets(code), expected);
}

/**
 * @test Tests detection of ']' as an unmatched closing bracket.
 */
TEST(testBracketChecker2, DetectUnmatchedClosingSquareBracket) {
    vector<string> code = { "]" };
    set<BracketError> expected = {
        {']', 1, 1, WRONG_BRACKET}
    };
    EXPECT_EQ(parse_brackets(code), expected);
}

/**
 * @test Tests that non-closing brackets like '(' and 'a' are ignored.
 */
TEST(testBracketChecker2, IgnoreNonClosingBrackets) {
    vector<string> code = { "(a" };
    set<BracketError> expected = {
        {'(', 1, 1, UNMATCHED_BRACKET}
    };
    EXPECT_EQ(parse_brackets(code), expected);
}


/**
 * @test Tests detection of a valid '()' bracket pair.
 */
TEST(testBracketChecker2, DetectMatchingParentheses) {
    vector<string> code = { "()" };
    set<BracketError> expected = {};
    EXPECT_EQ(parse_brackets(code), expected);
}

/**
 * @test Tests detection of a valid '[]' bracket pair.
 */
TEST(testBracketChecker2, DetectMatchingSquareBrackets) {
    vector<string> code = { "[]" };
    set<BracketError> expected = {};
    EXPECT_EQ(parse_brackets(code), expected);
}

/**
 * @test Tests detection of a valid '{}' bracket pair.
 */
TEST(testBracketChecker2, DetectMatchingBraces) {
    vector<string> code = { "{}" };
    set<BracketError> expected = {};
    EXPECT_EQ(parse_brackets(code), expected);
}

/**
 * @test Tests detection of incorrect bracket pair '(['.
 */
TEST(testBracketChecker2, DetectMismatchedParenthesesAndSquare) {
    vector<string> code = { "([" };
    set<BracketError> expected = {
        {'[', 1, 2, UNMATCHED_BRACKET},
        {'(', 1, 1, UNMATCHED_BRACKET}
    };
    EXPECT_EQ(parse_brackets(code), expected);
}

/**
 * @test Tests detection of incorrect bracket pair '{)'.
 */
TEST(testBracketChecker2, DetectMismatchedBraceAndParenthesis) {
    vector<string> code = { "{)" };
    set<BracketError> expected = {
        {')', 1, 2, WRONG_BRACKET},
        {'{', 1, 1, UNMATCHED_BRACKET}
    };
    EXPECT_EQ(parse_brackets(code), expected);
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
    set<BracketError> errors = parse_brackets(code);
    EXPECT_TRUE(errors.empty()) << "Expected no unmatched brackets.";
}

TEST(testBracketChecker2, UnbalancedBrackets) {
    vector<string> code = {
        "int main() {",
        "    if (true) {",
        "        cout << \"Hello\";",
        "}" // Missing closing '}'
    };
    set<BracketError> errors = parse_brackets(code);
    // set<BracketError> expected_errors
    // BracketError expected_err = {0, 9, ...}
    // expected_errors.add()
    // We should compare two sets 
    EXPECT_FALSE(errors.empty()) << "Expected unmatched brackets.";
}

TEST(testBracketChecker2, IgnoresCommentsAndStrings) {
    vector<string> code = {
        "int main() {",
        "    string s = \"{ not a bracket }\";",
        "    char c = '{'; // Character constant",
        "    /* block comment with [ brackets ] */",
        "    // single-line comment with { bracket",
        "    return 0;",
        "}"
    };
    set<BracketError> errors = parse_brackets(code);
    EXPECT_TRUE(errors.empty()) << "Expected no unmatched brackets.";
}

TEST(testBracketChecker2, EmptyFile) {
    vector<string> code = {};
    set<BracketError> errors = parse_brackets(code);
    EXPECT_TRUE(errors.empty()) << "Expected no errors for an empty file.";
}

TEST(testBracketChecker2, OnlyComments) {
    vector<string> code = {
        "// This is a comment with { brackets }",
        "/* multi-line comment with [ brackets ] inside */"
    };
    set<BracketError> errors = parse_brackets(code);
    EXPECT_TRUE(errors.empty()) << "Expected no errors for a file with only comments.";
}

TEST(testBracketChecker2, onlyWhitespace) {
    vector<string> code = {
        "   ",
        "\t\t"
    };
    set<BracketError> errors = parse_brackets(code);
    EXPECT_TRUE(errors.empty()) << "Expected no errors for a file with only white spaces.";
}

TEST(testBracketChecker2, IgnoresBracketsInsideStringLiterals) {
    vector<string> code = {
        "int main() {",
        "    string str = \"This is a string with brackets ( inside  here\";",
        "    return 0;",
        "}"
    };
    set<BracketError> errors = parse_brackets(code);
    EXPECT_TRUE(errors.empty()) << "Expected no unmatched brackets in string literals.";
}

TEST(BracketChecker2Test, MinimalNestedMismatch_Set) {
    vector<string> input = {
        "({) }"
    };

    set<BracketError> expected = {
        {')', 1, 3, WRONG_BRACKET},
        {'(', 1, 1, UNMATCHED_BRACKET}
    };

    auto actual = parse_brackets(input);
    EXPECT_EQ(expected, actual);
}


TEST(BracketChecker2Test, UnexpectedOpeningBracketLine) {
    vector<string> input = {
        "Int main(",
        "{"  // Unexpected opening bracket without closure
    };

    set<BracketError> expected = {
        {'(', 1, 9, UNMATCHED_BRACKET},
        {'{', 2, 1, UNMATCHED_BRACKET}
    };

    auto actual = parse_brackets(input);
    EXPECT_EQ(expected, actual);
}


TEST(testBracketChecker2, CurlyDoubleQuotesShouldNotAffectBracketParsing) {
    vector<string> code = {
        "{string str = “}”"
    };

    set<BracketError> errors = parse_brackets(code);

    // Only the opening brace '{' is unmatched, the '}' is inside curly double quotes and should be ignored
    set<BracketError> expected = {
        { '{', 1, 1, UNMATCHED_BRACKET }
    };

    EXPECT_EQ(errors, expected);
}

TEST(testBracketChecker2, ExceedsMaximumLinesAllowed) {
    vector<string> longCode(1001, "int a = 0;");  // 1001 lines
    set<BracketError> errors = code_validation(longCode);

    set<BracketError> expected = {
        {'\0', 1001, 1, TOO_LONG_PROGRAM}
    };

    EXPECT_EQ(errors, expected);
}

TEST(testBracketChecker2, ExceedsMaximumLineLength) {
    vector<string> code = {
        string(1001, 'a')  // One line with 1001 characters
    };
    set<BracketError> errors = code_validation(code);

    set<BracketError> expected = {
        {'\0', 1, 1001, TOO_LONG_LINE}
    };

    EXPECT_EQ(errors, expected);
}


TEST(testBracketChecker2, DetectsMacroUsage) {
    vector<string> code = {
        "#define MAX 100"
    };
    set<BracketError> errors = code_validation(code);

    set<BracketError> expected = {
        {'#', 1, 1, MACRO_USAGE}
    };

    EXPECT_EQ(errors, expected);
}


// Needed for comparing BracketError in EXPECT_EQ
bool operator==(const BracketError& lhs, const BracketError& rhs) {
    return lhs.bracket == rhs.bracket &&
        lhs.line == rhs.line &&
        lhs.column == rhs.column &&
        lhs.type == rhs.type;
}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
