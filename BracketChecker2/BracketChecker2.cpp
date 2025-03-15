#include "BracketChecker2.h"

BracketChecker2::BracketChecker2() {}

bool BracketChecker2::isOpeningBracket(char ch) {
    return ch == '(' || ch == '[' || ch == '{';
}

bool BracketChecker2::isClosingBracket(char ch) {
    return ch == ')' || ch == ']' || ch == '}';
}

bool BracketChecker2::isMatchingPair(char open, char close) {
    return (open == '(' && close == ')') ||
        (open == '[' && close == ']') ||
        (open == '{' && close == '}');
}