// include statements
#include <iostream>
#include <string>
#include <boost/regex.hpp>
#include <algorithm>
#include <vector>
#include "board.h"

// using statements
using namespace std;

// function declarations
string getCurrentGameBoard(bool* gameRunning);
bool regexValidate(string expr, string teststring);
void stringTrim(string* inputStr, vector<char> args);
void removeCharFromString(string* str, char arg);
void getInputLine(string* str);

// global variables
const bool debug = true;
const bool deepDebug = false;
const string boardInputFormat = "^\\([0-9],[0-9],[0-9],[0-9],[0-9],[0-9],[0-9],[0-9],[0-9]\\)$";

int main()
{
	//game mechanic variables
	bool gameRunning = true;


	while (gameRunning)
	{
		string userInput = getCurrentGameBoard(&gameRunning);
		if (!gameRunning)
		{
			break;
		}

		
	}
}

string getCurrentGameBoard(bool* gameRunning)
{
	string possibleBoard;
	while (true)
	{
		cout << "What is the current state of the game board? [enter -1 to exit the program]" << endl;
		getInputLine(&possibleBoard);
		stringTrim(&possibleBoard, { ' ' });

		if (possibleBoard == "-1") 
		{ 
			*gameRunning = false; 
			cout << "Exit Input Detected -> closing the program." << endl;
			if (deepDebug) { cout << endl << (*gameRunning ? "True" : "False") << endl; }
			break;
		}
		else if (regexValidate(boardInputFormat, possibleBoard))
		{
			if (debug) { cout << "The supplied " << possibleBoard << "  board is in the correct format" << endl; }
			stringTrim(&possibleBoard, { '(', ')'});
			if (deepDebug) { cout << possibleBoard << endl; }
		}
		else
		{
			cout << "The supplied " << possibleBoard << "  board is not in the correct format: \n(a,b,c,d,e,f,g,h,i) with 0's for the empty cells." << endl;
		}
	}
	return possibleBoard;
}

bool regexValidate(string expr, string teststring)
{
	boost::regex ex(expr);
	if (boost::regex_match(teststring, ex)) {
		if (deepDebug) { cout << "true" << endl; }
		return true;
	}
	return false;
}

void stringTrim(string* inputStr, vector<char> args) 
{
	string my_str = *inputStr;
	for (char v : args)
	{
		removeCharFromString(&my_str, v); //remove v from string
	}
	*inputStr = my_str;
	if (deepDebug) { cout << *inputStr << endl; }
}

void removeCharFromString(string* str, char arg)
{
	string my_str = "";
	for (int i = 0; i < (*str).length(); i++)
	{
		if ((*str)[i] != arg)
		{
			my_str += (*str)[i];
		}
	}
	*str = my_str;
	if (deepDebug) { cout << *str << endl; }
}

void getInputLine(string* str)
{
	string in;
	getline(cin, in);
	*str = in;
	// cin >> in; 
}