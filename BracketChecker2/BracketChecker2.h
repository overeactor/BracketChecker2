#pragma once
#ifndef BRACKETCHECKER2_H  
#define BRACKETCHECKER2_H

#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include <vector>

using namespace std;


bool isOpeningBracket(char ch);
bool isClosingBracket(char ch);
bool isMatchingPair(char open, char close);


vector<pair<char, pair<int, int>>> read_input_file(const string& filename);
void print_result(const string& outputFilename, const vector<pair<char, pair<int, int>>>& errors);


#endif // BRACKETCHECKER2_H