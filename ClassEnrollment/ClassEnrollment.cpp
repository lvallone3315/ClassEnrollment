// ClassEnrollment.cpp : This file contains the 'main' function. Program execution begins and ends there.
//    Author: Lee
//    Created: 22-Oct, 2022 for Fall 2022 CSCI 3315
// 
// Application to capture students & classes (entered from console)
// & then associate (e.g. enroll entered students in specified classes) & display class rosters
// 
// Real objectives are to demonstrate some C++ constructs including:
// * Object oriented design including encapsulation
// * Enums
// * Vector & Lists including heap memory allocation
// * Parsing using regex & sscanf
// 
// Various issues with this code:
//   Versioning missing
//   Hardcoding of a loop iteration
//   Hardcoding user output, string literals littered through the code
//   Inconsistent formats (e.g. comments)
//   Student storage & display really should be its own class to hide implementation from others
//      Note - this one is fixed with StudentDb class, though retaining original implementation for demo
//

#include "ClassUI.h"
#include "Parser.h"
#include "Student.h"
#include "StudentDb.h"
#include "ClassDb.h"

#include <iostream>
#include <string>
 

int main()
{
    ClassUI console;    // UI encapsulation - rather than directly writing to console - ToDo fix issues in parser class
    Parser parser;      // command parser - pass it a string - parser knows command format & returns struct
    Parser::InputStruct* parserOutput;
    StudentDb studentDb;  // aggregation of all students
    ClassDb classDb;      // aggregation of all classes

    string userInputString;   // raw user input - retrived from UI & redirected to parser for processing


    // ToDo - add versioning
    console.writeOutput("Hello Class Enrollment application!\n");

    // Parser approach to data entry
    //    prompt user for a command and while that command isn't quit, grab student IDs
    //    Generally - methods return true (action completed successfully) or false - action not completed
    //       ToDo - track type of failures & store in the parser output structure
    //       ToDo - store actual user string in the parser output structure (this ToDo is also captured elsewhere)

    do {
        userInputString = console.getUserInput("\n\nEnter command: ");
        parserOutput = parser.parseInput(userInputString);   // parserOutput is a pointer to memory created on the heap
        parser.displayParsedOutput(parserOutput, console);   // beware - memory leak!!!!

        switch (parserOutput->command) {
        case Parser::STUDENT_ID:         // create student in student database
            if (!studentDb.storeStudentId(parserOutput->studentId))
                console.writeOutput("Error!  Student record not created\n\n");
            break;
        case Parser::CLASS_ID:          // create course instance in class database
            if (!classDb.storeClassId(parserOutput->classId))
                console.writeOutput("Error!  Class record not created\n\n");
            break;
        case Parser::ENROLL_STUDENT:   // enroll student in specified class
            if (!classDb.enrollStudentInClass(parserOutput->studentId, parserOutput->classId))
                console.writeOutput("Error! Student not added to class - likely class ID does not exist\n\n");
            else
                console.writeOutput("Student successfully enrolled!\n");
            break;
        case Parser::DISPLAY_CLASS_ROSTER: // display roster for specified class
            // class-431 add support to display the students enrolled in a class, don't forget the error case
            break;
        case Parser::QUIT:            // exit application
            console.writeOutput("Bye!!\n\n");
            break;
        case Parser::ERROR:           // error when parsing user input, ignore & try again
        default:                      // should never get to default, unless added command & forgot to update this switch statement
            console.writeOutput("ERROR returned from parser\n\n");
            break;
        };
        // ToDo - free parserOutput memory output - maybe passing command to a local variable 1st so can free it here
    } while (parserOutput->command != Parser::QUIT);

    // display students for all three versions
    studentDb.displayStudents(console, "Vector & List: after entering student IDs");

}
