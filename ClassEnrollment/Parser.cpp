#include "Parser.h"

Parser::Parser() {
	// null constructor
}

Parser::InputStruct *Parser::parseInput(string userString) {
	InputStruct *parsedInput = new InputStruct;

	/*
	 * structure of commands
	 *   Configure student: 1   <integer student id>
	 *   configure class:   2   <integer class id>
	 *   Enroll student in class:  3  <integer class id>  <integer student id>
	 *   Print class roster:       4  <integer class id>
	 *   Quit:              5
	 *   Parser error:      6
	 *
	 * Parser
	 *   Ignore leading white space
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

	return (parsedInput);
}