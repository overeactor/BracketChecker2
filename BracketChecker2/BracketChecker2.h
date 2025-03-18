#pragma once
#ifndef BRACKETCHECKER2_H  
#define BRACKETCHECKER2_H

#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include <vector>

using namespace std;


class BracketChecker2 {

public:
	
	BracketChecker2();
	

	void checkBrackets(const string& filename);

private:

	bool isOpeningBracket(char ch);
	
	 
	bool isClosingBracket(char ch);

	bool isMatchingPair(char open, char close);

};




#endif // BRACKETCHECKER2_H