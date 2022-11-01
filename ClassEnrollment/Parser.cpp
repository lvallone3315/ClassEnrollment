#include "Parser.h"
#include <regex>
#include <string>
#include <iostream>

using namespace std;  // for debugging - delete after debugging

/*
 * Parser
 *   Ignore leading & trailing white space
 *   Parse first integer - if no integer found, or not in 1-5, return Parser Error
 *   if quit - return QUIT
 *   Parse second integer - if no integer found, return Parser Error
 *     if integer found, switch on command & place in appropriate field class (2,3,4 = class id, 1 = student id)
 *   if command is enroll student, parse for 3rd integer, if none found return Error
 *     otherwise place in student id field
 *   return structure
 *
 * Note:
 *   Error returns - some fields may be filled in, but should be ignored
 *   Structure is allocated from heap in this class, but never freed here (ie free space after using by caller)
 */

 /*
  * structure of commands
  *    Note - reducing reduncdancy, comment & help text all in one :)
  */
string helpText =
"Configure student :       1   <integer student id>\n"
"Configure class :         2   <integer class id> \n"
"Enroll student in class : 3  <integer class id>  <integer student id>\n"
"Print class roster :      4  <integer class id>\n"
"Quit:                     5  \n\n";
//   Parser error:             6 -- note this last ID is internal only & not available touser

Parser::Parser() {
	// null constructor
}

Parser::InputStruct *Parser::parseInput(string userString) {
	InputStruct *parsedInput = new InputStruct;

	/* Approach:
	 *   Define a few regular expression comparisons to:
	 *     1) validate the format is one of the defined formats (regex)
	 *     2) if valid, parse into the appropriate fields (sscanf_s)
	 * 
	 * ToDo - cleanup by using helper funtions to parse
	 * ToDo - update parser to save the string the user entered
	 */

	       //             Regular expressions for comamnds
	    // command only (e.g. 5 = quit), single digit in range 1-5
	    // For more information - try https://regex101.com/

	std::regex cmdRegex("^\\s?[1-5]\\s?$");
	    // command + one integer (either student id or class id), 1 or more digits
	std::regex oneArgRegex("^\\s?[1-5]\\s[0-9]+\\s?$");
	    // command + two integers (e.g. enroll student to class), each 1 or more digits
	std::regex twoArgRegex("^\\s?[1-5]\\s[0-9]+\\s[0-9]+\\s?$"); 

	//   command with no arguments - only quit command has this format
	if (regex_match(userString, cmdRegex)) {
		int command;   // define temporary variables locally to avoid scope issues & improve readability
		sscanf_s(userString.c_str(), "%d", &command);
		if (command == QUIT)    // note: enum values are defined in parser.h - no need to hard code here
			parsedInput->command = QUIT;
		else
			parsedInput->command = ERROR;
	}

	// comamnd with one argument - could be class ID or Student ID
	else if (regex_match(userString, oneArgRegex)) {
		int command;
		int id;  // could be either class ID or student ID
		sscanf_s(userString.c_str(), "%d %d", &command, &id);
		if (command == STUDENT_ID) {
			parsedInput->command = STUDENT_ID;
			parsedInput->studentId = id;
		}
		else if (command == CLASS_ID) {
			parsedInput->command = CLASS_ID;
			parsedInput->classId = id;
		}
		// could be a request to display the enrolled students
		// check for this command & configure the parsedInput structure
		else if (command == DISPLAY_CLASS_ROSTER) {
			parsedInput->command = DISPLAY_CLASS_ROSTER;
			parsedInput->classId = id;
		}

		else // invalid one argument command
			parsedInput->command = ERROR;
	}

	// command with two arguments - only enrollment command allows this
	else if (regex_match(userString, twoArgRegex)) {
		int command;
		int classId;
		int studentId;
		sscanf_s(userString.c_str(), "%d %d %d", &command, &classId, &studentId);
		if (command == ENROLL_STUDENT) {
			parsedInput->command = ENROLL_STUDENT;
			parsedInput->studentId = studentId;
			parsedInput->classId = classId;
		}
		else // invalid two argument command
			parsedInput->command = ERROR;
	}
	else {
		parsedInput->command = ERROR;
	}
	return (parsedInput);
}

/**
 * displayParserOutput() - knows how to print all elements of parser output structure
 * args:
 *   parsedOutput - pointer to structure returned by parser
 *   console - UI to print  --- note major problems with this approach, need to debug further
 *      resorting to cout for now
*/

void Parser::displayParsedOutput(InputStruct* parsedOutput, ClassUI console ) {
	//
	switch (parsedOutput->command) {
	case QUIT:
		cout << "Quit\n";
		// console.writeOutput("Quit");
		break;
	case STUDENT_ID:
		cout << "Student ID: " << parsedOutput->studentId << "\n";
		// console.writeOutput("Student ID: " + parsedOutput->studentId);
		break;
	case CLASS_ID:
		cout << "Class ID: " << parsedOutput->classId << "\n";
		// console.writeOutput("Class ID: " + parsedOutput->classId);
		break;
	case ENROLL_STUDENT:
		cout << "Student " << parsedOutput->studentId << " trying to enroll in " << parsedOutput->classId << "\n";
		// console.writeOutput("Class enrolls student" + parsedOutput->classId);  // ToDo - figure out why writeOutput can't use const char[] after int
		// console.writeOutput(" " + parsedOutput->studentId);
		break;
	case DISPLAY_CLASS_ROSTER:
		// output details of display class roster request (e.g. classId)
		cout << "Display roster for class " << parsedOutput->classId << "\n";
		break;

	default:
		cout << "   *** Invalid Command -- Valid commands are ...\n";
		cout << helpText;

		// console.writeOutput("invalid command: " + parsedOutput->command);
		// console.writeOutput("\n");
		// console.writeOutput(helpText);
		break;
	}
	// console.writeOutput("\n");
}