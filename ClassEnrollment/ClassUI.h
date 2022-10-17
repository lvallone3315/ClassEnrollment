#pragma once

#include <string>
using namespace std;  // fair programming practice, as could create scope issues, but don't feel like qualifying all reads & writes

class ClassUI
{
public:
	ClassUI();
	int writeOutput(string output);
	string getUserInput(string prompt);
};

