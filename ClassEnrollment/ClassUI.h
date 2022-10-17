#pragma once

#include <string>
using namespace std;  // fair programming practice, as could create scope issues, but don't feel like qualifying all reads & writes

/*
 * Header file for Class program UI
 *    getUserInput() prompts user with specified string and returns user input
 *    writeOutput() writes output to console and returns success (0)
 */

class ClassUI
{
public:
	ClassUI();
	int writeOutput(string output);
	string getUserInput(string prompt);
};

