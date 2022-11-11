#pragma once

#include <string>

// removed "using namespace std" per sonarlint recommendation as part of code cleanup
//   using namespace should be avoided in header files since the class creator cannot control the environment it will be included in

/*
 * Header file for Class program UI
 *    getUserInput() prompts user with specified string and returns user input
 *    writeOutput() writes output to console and returns success (0)
 */

class ClassUI
{
public:
	int writeOutput(std::string const &output);
	std::string getUserInput(std::string const &prompt);
};

