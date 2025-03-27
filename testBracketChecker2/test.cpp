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


TEST(testBracketChecker2, ReadInputFile_Valid) {
    std::ofstream testFile("test_valid.txt");
    testFile << "{[()]}";  
    testFile.close();

    auto errors = read_input_file("test_valid.txt");
    EXPECT_TRUE(errors.empty());  
}



// Test read_input_file() function with unmatched brackets
TEST(testBracketChecker2, ReadInputFile_Invalid) {
    std::ofstream testFile("test_invalid.txt");
    testFile << "{[(])}";  // Incorrectly matched brackets
    testFile.close();

    auto errors = read_input_file("test_invalid.txt");
    EXPECT_FALSE(errors.empty());  // Expect errors
}


// Test print_result() function
TEST(testBracketChecker2, PrintResult) {
    std::vector<std::pair<char, std::pair<int, int>>> errors = {
        {'(', {1, 5}}, {')', {3, 10}}
    };

    print_result("test_output.txt", errors);

    std::ifstream inFile("test_output.txt");
    std::stringstream buffer;
    buffer << inFile.rdbuf();
    std::string result = buffer.str();

    EXPECT_NE(result.find("Unmatched brackets found"), std::string::npos);
    EXPECT_NE(result.find("Bracket '(' at Line 1, Position 5 is unmatched."), std::string::npos); 
} 

//Test an empty file
TEST(BracketChecker2Test, EmptyFile) {
    std::ofstream testFile("empty_file.txt");
    testFile.close();  // Create an empty file

    auto errors = read_input_file("empty_file.txt");
    EXPECT_TRUE(errors.empty());  // Should pass
}  

//Test file with only comments (should be ignored)
// No errors should be detected.
TEST(BracketChecker2Test, OnlyComments) {
    std::ofstream testFile("only_comments.txt");
    testFile << R"(
        // This is a comment with brackets { [ ( ) ] }
        /* Another comment
           with brackets { [ ( ) ] } */
    )";
    testFile.close();

    auto errors = read_input_file("only_comments.txt");
    EXPECT_TRUE(errors.empty());  // Should ignore all brackets inside comments  
}   


//Test deeply nested brackets and no error should be detected
TEST(BracketChecker2Test, DeeplyNestedBrackets) {
    std::ofstream testFile("nested_brackets.txt");
    testFile << R"(
        int main() {
            if (true) {
                while (x > 0) {
                    for (int i = 0; i < 10; i++) {
                        arr[i] = (i + (x * [y + (z)]));
                    }
                }
            }
        }
    )";
    testFile.close();

    auto errors = read_input_file("nested_brackets.txt");
    EXPECT_TRUE(errors.empty());  // Should pass
}




int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}