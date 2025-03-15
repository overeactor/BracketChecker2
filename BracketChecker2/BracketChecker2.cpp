#include "BracketChecker2.h"

BracketChecker2::BracketChecker2() {}

bool BracketChecker2::isOpeningBracket(char ch) {
    return ch == '(' || ch == '[' || ch == '{';
}
