#pragma once

#include <string>

using namespace std;


class Parser
{
private:  // nothing here

public:
	enum CmdMenu { STUDENT_ID = 1, CLASS_ID = 2, ENROLL_STUDENT = 3, DISPLAY_CLASS_ROSTER = 4, QUIT = 5 }; 
	struct InputStruct {
		CmdMenu command;
		int studentId;
		int ClassId;
	};

	Parser();
	InputStruct *parseInput(string userString);
};

