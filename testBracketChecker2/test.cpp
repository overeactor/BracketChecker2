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


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}