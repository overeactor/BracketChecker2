/**
 * @file test.cpp
 * @brief Unit tests for BracketChecker2 using Google Test.
 *
 * This file contains test cases to verify the correctness of the
 * BracketChecker2 library. It covers:
 * - Bracket matching and mismatching scenarios.
 * - Detection of formatting violations (long lines, macros).
 * - Ignoring brackets inside strings and comments.
 * - File reading behavior and edge cases (empty input, comments only).
 *
 * Each test checks the output of `parse_brackets` or `code_validation`
 * against expected `BracketError` results.
 */

#include "pch.h"
#include <gtest/gtest.h>
#include <set>
#include "../BracketChecker2/BracketChecker2.h"  
#include "../BracketChecker2/BracketChecker2.cpp"  


/* kuliokin: Add a function to compare set and print message if sets are not equlas...
* difference between two sets
Example: your set does not contain {1,1,CLOSE} but it expected
Example: your set contain {1,1,CLOSE} but it is not expected*/



/**
  * @brief Prints differences between two sets of BracketError.
  * @param expected The expected set of BracketError.
  * @param actual The actual set of BracketError produced by the parser.
  */
void print_set_difference(const std::set<BracketError>& expected, const std::set<BracketError>& actual) {
    if (expected == actual) {
        std::cout << "Sets are identical." << std::endl;
        return;
    }

    std::set<BracketError> missing, extra;

    std::set_difference(expected.begin(), expected.end(), actual.begin(), actual.end(),
        std::inserter(missing, missing.begin()));
    std::set_difference(actual.begin(), actual.end(), expected.begin(), expected.end(),
        std::inserter(extra, extra.begin()));

    if (!missing.empty()) {
        std::cout << "Expected but not found:" << std::endl;
        for (const auto& e : missing) {
            std::cout << "  {" << e.bracket << "," << e.line << "," << e.column << "," << e.type << "}" << std::endl;
        }
    }

    if (!extra.empty()) {
        std::cout << "Found but not expected:" << std::endl;
        for (const auto& e : extra) {
            std::cout << "  {" << e.bracket << "," << e.line << "," << e.column << "," << e.type << "}" << std::endl;
        }
    }
}



using namespace std;



/**
 * @test DetectUnmatchedOpeningParenthesis
 * @brief Tests detection of an unmatched opening parenthesis.
 */
TEST(testBracketChecker2, DetectUnmatchedOpeningParenthesis) {
    vector<string> code = { "(", "" };
    set<BracketError> expected = {
        {'(', 1, 1, UNMATCHED_BRACKET}
    };
    auto actual = parse_brackets(code);
    EXPECT_EQ(actual, expected);
    print_set_difference(expected, actual);
    /*function call print_set_difference(...)*/
}

/**
 * @test DetectUnmatchedOpeningBrace
 * @brief Tests detection of an unmatched opening brace.
 */
TEST(testBracketChecker2, DetectUnmatchedOpeningBrace) {
    vector<string> code = { "{", "" };
    set<BracketError> expected = {
        {'{', 1, 1, UNMATCHED_BRACKET}
    };
    auto actual = parse_brackets(code);
    EXPECT_EQ(actual, expected);
    print_set_difference(expected, actual);
}

/**
 * @test DetectUnmatchedOpeningSquareBracket
 * @brief Tests detection of unmatched opening square bracket.
 */
TEST(testBracketChecker2, DetectUnmatchedOpeningSquareBracket) {
    vector<string> code = { "[", "" };
    set<BracketError> expected = {
        {'[', 1, 1, UNMATCHED_BRACKET}
    };
    auto actual = parse_brackets(code);
    EXPECT_EQ(actual, expected);
    print_set_difference(expected, actual);
}


/**
 * @test IgnoreNonOpeningBrackets
 * @brief Tests ignored non-opening characters and detection of unmatched closing parenthesis.
 */
TEST(testBracketChecker2, IgnoreNonOpeningBrackets) {
    vector<string> code = { "x)" };
    set<BracketError> expected = {
        {')', 1, 2, WRONG_BRACKET}
    };
    auto actual = parse_brackets(code);
    EXPECT_EQ(actual, expected);
    print_set_difference(expected, actual);
}

/**
 * @test DetectUnmatchedClosingParenthesis
 * @brief Tests detection of unmatched closing parenthesis.
 */
TEST(testBracketChecker2, DetectUnmatchedClosingParenthesis) {
    vector<string> code = { ")" };
    set<BracketError> expected = {
        {')', 1, 1, WRONG_BRACKET}
    };
    auto actual = parse_brackets(code);
    EXPECT_EQ(actual, expected);
    print_set_difference(expected, actual);
}

/**
 * @test DetectUnmatchedClosingBrace
 * @brief Tests detection of unmatched closing brace.
 */
TEST(testBracketChecker2, DetectUnmatchedClosingBrace) {
    vector<string> code = { "}" };
    set<BracketError> expected = {
        {'}', 1, 1, WRONG_BRACKET}
    };
    auto actual = parse_brackets(code);
    EXPECT_EQ(actual, expected);
    print_set_difference(expected, actual);
}

/**
 * @test DetectUnmatchedClosingSquareBracket
 * @brief Tests detection of unmatched closing square bracket.
 */
TEST(testBracketChecker2, DetectUnmatchedClosingSquareBracket) {
    vector<string> code = { "]" };
    set<BracketError> expected = {
        {']', 1, 1, WRONG_BRACKET}
    };
    auto actual = parse_brackets(code);
    EXPECT_EQ(actual, expected);
    print_set_difference(expected, actual);
}

/**
 * @test IgnoreNonClosingBrackets
 * @brief Tests ignored characters that aren't brackets.
 */
TEST(testBracketChecker2, IgnoreNonClosingBrackets) {
    vector<string> code = { "(a" };
    set<BracketError> expected = {
        {'(', 1, 1, UNMATCHED_BRACKET}
    };
    auto actual = parse_brackets(code);
    EXPECT_EQ(actual, expected);
    print_set_difference(expected, actual);
}


/**
 * @test DetectMatchingParentheses
 * @brief Tests detection of matched parentheses.
 */
TEST(testBracketChecker2, DetectMatchingParentheses) {
    vector<string> code = { "()" };
    set<BracketError> expected = {};
    auto actual = parse_brackets(code);
    EXPECT_EQ(actual, expected);
    print_set_difference(expected, actual);
}

/**
 * @test DetectMatchingSquareBrackets
 * @brief Tests detection of matched square brackets.
 */
TEST(testBracketChecker2, DetectMatchingSquareBrackets) {
    vector<string> code = { "[]" };
    set<BracketError> expected = {};
    auto actual = parse_brackets(code);
    EXPECT_EQ(actual, expected);
    print_set_difference(expected, actual);
}

/**
 * @test DetectMatchingBraces
 * @brief Tests detection of matched braces.
 */
TEST(testBracketChecker2, DetectMatchingBraces) {
    vector<string> code = { "{}" };
    set<BracketError> expected = {};
    auto actual = parse_brackets(code);
    EXPECT_EQ(actual, expected);
    print_set_difference(expected, actual);
}

/**
 * @test DetectMismatchedParenthesesAndSquare
 * @brief Tests detection of mismatched brackets: parentheses and square bracket.
 */
TEST(testBracketChecker2, DetectMismatchedParenthesesAndSquare) {
    vector<string> code = { "([" };
    set<BracketError> expected = {
        {'[', 1, 2, UNMATCHED_BRACKET},
        {'(', 1, 1, UNMATCHED_BRACKET}
    };
    auto actual = parse_brackets(code);
    EXPECT_EQ(actual, expected);
    print_set_difference(expected, actual);
}

/**
 * @test DetectMismatchedBraceAndParenthesis
 * @brief Tests detection of mismatched brackets: brace and parenthesis.
 */
TEST(testBracketChecker2, DetectMismatchedBraceAndParenthesis) {
    vector<string> code = { "{)" };
    set<BracketError> expected = {
        {')', 1, 2, WRONG_BRACKET},
        {'{', 1, 1, UNMATCHED_BRACKET}
    };
    auto actual = parse_brackets(code);
    EXPECT_EQ(actual, expected);
    print_set_difference(expected, actual);
}

/**
 * @test ReadInputFile
 * @brief Tests reading input file successfully.
 */
TEST(testBracketChecker2, ReadInputFile) {
    vector<string> lines = read_input_file("test_input.txt");
    EXPECT_FALSE(lines.empty()) << "File should be read successfully.";
}

/**
 * @test BalancedBrackets
 * @brief Tests detection of fully balanced bracket nesting.
 */
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

/**
 * @test UnbalancedBrackets
 * @brief Tests detection of unmatched opening bracket in a function with nested scope.
 *
 * The test simulates a case where the main function includes an if-statement with its own scope,
 * but the final closing brace for the main function is missing. The parser should return an
 * unmatched bracket error for the first opening brace.
 */
TEST(testBracketChecker2, UnbalancedBrackets) {
    vector<string> code = {
        "int main() {",
        "    if (true) {",
        "        cout << \"Hello\";",
        "}" // Missing one closing '}'
    };

    set<BracketError> expected = {
        {'{', 1, 12, UNMATCHED_BRACKET}

    };

    set<BracketError> actual = parse_brackets(code);
    EXPECT_EQ(actual, expected);
    print_set_difference(expected, actual);
}

/**
 * @test IgnoresCommentsAndStrings
 * @brief Tests parser ignoring brackets inside strings and comments.
 */
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

/**
 * @test EmptyFile
 * @brief Tests parsing an empty file.
 */
TEST(testBracketChecker2, EmptyFile) {
    vector<string> code = {};
    set<BracketError> errors = parse_brackets(code);
    EXPECT_TRUE(errors.empty()) << "Expected no errors for an empty file.";
}

/**
 * @test OnlyComments
 * @brief Tests parsing comments only (no code).
 */
TEST(testBracketChecker2, OnlyComments) {
    vector<string> code = {
        "// This is a comment with { brackets }",
        "/* multi-line comment with [ brackets ] inside */"
    };
    set<BracketError> errors = parse_brackets(code);
    EXPECT_TRUE(errors.empty()) << "Expected no errors for a file with only comments.";
}

/**
 * @test onlyWhitespace
 * @brief Tests parsing a file with only whitespace.
 */
TEST(testBracketChecker2, onlyWhitespace) {
    vector<string> code = {
        "   ",
        "\t\t"
    };
    set<BracketError> errors = parse_brackets(code);
    EXPECT_TRUE(errors.empty()) << "Expected no errors for a file with only white spaces.";
}


/**
 * @test IgnoresBracketsInsideStringLiterals
 * @brief Tests ignoring brackets in string literals.
 */
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

/**
 * @test MinimalNestedMismatch_Set
 * @brief Tests detection of minimal nested mismatch.
 */
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
    print_set_difference(actual, expected);
}


/**
 * @test UnexpectedOpeningBracketLine
 * @brief Tests detection of unexpected opening brackets across lines.
 */
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
    print_set_difference(actual, expected);
}

/**
 * @test CurlyDoubleQuotesShouldNotAffectBracketParsing
 * @brief Tests parser handling of curly double quotes with brackets.
 */
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
    print_set_difference(expected, errors);
}

/**
 * @test ExceedsMaximumLinesAllowed
 * @brief Tests detection of excessive line count.
 */
TEST(testBracketChecker2, ExceedsMaximumLinesAllowed) {
    vector<string> longCode(1001, "int a = 0;");  // 1001 lines
    set<BracketError> errors = code_validation(longCode);

    set<BracketError> expected = {
        {'\0', 1001, 1, TOO_LONG_PROGRAM}
    };

    EXPECT_EQ(errors, expected);
    print_set_difference(expected, errors);
}

/**
 * @test ExceedsMaximumLineLength
 * @brief Tests detection of excessively long single line.
 */
TEST(testBracketChecker2, ExceedsMaximumLineLength) {
    vector<string> code = {
        string(1001, 'a')  // One line with 1001 characters
    };
    set<BracketError> errors = code_validation(code);

    set<BracketError> expected = {
        {'\0', 1, 1001, TOO_LONG_LINE}
    };

    EXPECT_EQ(errors, expected);
    print_set_difference(expected, errors);
}

/**
 * @test DetectsMacroUsage
 * @brief Tests detection of disallowed macro usage.
 */
TEST(testBracketChecker2, DetectsMacroUsage) {
    vector<string> code = {
        "#define MAX 100"
    };
    set<BracketError> errors = code_validation(code);

    set<BracketError> expected = {
        {'#', 1, 1, MACRO_USAGE}
    };

    EXPECT_EQ(errors, expected);
    print_set_difference(expected, errors);
}


/**
 * @brief Comparison operator for BracketError to support EXPECT_EQ.
 */
bool operator==(const BracketError& lhs, const BracketError& rhs) {
    return lhs.bracket == rhs.bracket &&
        lhs.line == rhs.line &&
        lhs.column == rhs.column &&
        lhs.type == rhs.type;
}

/**
 * @brief Main function to run all Google Test unit tests.
 */
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

