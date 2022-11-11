#pragma once

#include <string>
#include "ClassUI.h"


class Parser
{
private:  // nothing here

public:
	enum CmdMenu { STUDENT_ID = 1, CLASS_ID = 2, ENROLL_STUDENT = 3, DISPLAY_CLASS_ROSTER = 4, QUIT = 5, ERROR = 6 }; 
	struct InputStruct {
		CmdMenu command;
		int studentId;
		int classId;
	};

	// Using default constructor - nothing to initialize, InputStruct created by parseInput() from the heap & returned to caller
	InputStruct *parseInput(std::string const &userString);             // passing reference to user string to avoid copy (more efficient, id by Sonarlint)
	void displayParsedOutput(InputStruct* parsedOutput, ClassUI console);   // write an Input structure to the console object
};

