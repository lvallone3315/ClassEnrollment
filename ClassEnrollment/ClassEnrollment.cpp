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
//   Versioning
//   Hardcoding of a loop iteration
//   Hardcoding user output
//   UI class seems to have issues consistently outputing the passed strings
//   Inconsistent formats (e.g. comments)
//   Student storage & display really should be its own class to hide implementation from others
//

#include "ClassUI.h"
#include "Parser.h"
#include "Student.h"
#include "StudentDb.h"

#include <iostream>
#include <stdexcept>  // required for stoi - throws exception for invalid input (e.g. string starting with alphas
#include <string>
#include <vector>    // Vector support for tracking student objects
#include <list>      // list support for tracking student objects
#include <iterator>  // list related - needed to traverse list of student objects

// Global storage for student arrays so can use helper function to display
    // two versions
    //   1st vector of objects
    //   2nd vector of pointers to objects
std::vector<Student> studentVector;
std::vector<Student*> studentPointerVector;

// list approach
//
std::list<Student> studentList; 

int main()
{
    ClassUI console;    // UI encapsulation - rather than directly writing to console
    Parser parser;      // command parser - pass it a string - parser knows command format & returns struct
    Parser::InputStruct* parserOutput;
    StudentDb studentDb;  // aggregation of all students

    string userInputString;   // raw user input - retrived from UI & redirected to parser for processing


    // helper functions
    void displayStudents(ClassUI, string);
    int getStudentId(ClassUI console);
    void storeStudentId(unsigned int studentId);

    // ToDo - add versioning
    console.writeOutput("Hello Class Enrollment application!\n");

    // original approach to data entry - before parser implemented
    // prompt user 5 times for a student ID, push onto the end of the storage array(s)
    unsigned int studentId;
    for (int i = 0; i < 5; i++) {
        if ((studentId = getStudentId(console)) != 0) {
            storeStudentId(studentId);
        }
        // else invalid entry - continue to get next student
    }
    displayStudents(console, "Displaying students entered using stoi() & local to main storage\n\n");

    // Parser approach to data entry
    //    prompt user for a command and while that command isn't quit, grab student IDs

    do {
        userInputString = console.getUserInput("Enter command: ");
        parserOutput = parser.parseInput(userInputString);
        parser.displayParsedOutput(parserOutput, console);

        switch (parserOutput->command) {
        case Parser::STUDENT_ID:
            studentDb.storeStudentId(parserOutput->studentId);
        };
    } while (parserOutput->command != Parser::QUIT);

    // display contents of all three versions
    studentDb.displayStudents(console, "Vector & List: after entering student IDs");


         //   Playing with some of the vector & list capabilities - use local versions
    studentDb.sandboxStudentDb(console);

}


// The following code is part of the original approach which used a simple way to parse the input (stoi)
//   and kept the vectors & list storage in main()
//   Updated version moved all of this functionality to other classes & uses a real regex parser

    //     Store the student Id at the end of the arrays (ie vectors & list)
    //       three different storage approaches
    //          vector array storing classes, vector array storing pointers to classes
    //          list storing class
void storeStudentId(unsigned int studentId) {

    // push the object onto the vector array
    Student student(studentId);
    studentVector.push_back(student);

    // allocate memory from the heap
    Student* studentP = new Student(studentId);
    studentPointerVector.push_back(studentP);

    // add the object to a list
    studentList.push_back(student);
}

/*
 *   Display student arrays (vector & list)
 *   Multiple approaches to iterating through the vectors & lists
 *   e.g. iterating vector by index, or iterating by 'in' ?
 *        iterating list by iterator
 */

void displayStudents(ClassUI console,string heading) {
    cout << "\n*** " << heading << " ***\n";
    cout << "Display all students in studentVector (iterating by index)\n";
    for (int i = 0; i < studentVector.size(); i++) {
        console.writeOutput(to_string(studentVector[i].getStudentId()) + " ");
    }
    cout << "\nDisplay all students in studentVector\n";
    for (Student j : studentVector) {
        cout << j.getStudentId() << " ";
    }
    cout << "\nDisplay all students in vector of pointers to student objects\n";
    for (Student* p : studentPointerVector) {
        cout << p->getStudentId() << " ";
    }
    cout << "\nDisplay all students in list of student objects\n";
    for (list <Student> ::iterator itr = studentList.begin(); itr != studentList.end(); itr++) {
        cout << itr->getStudentId() << " ";
    }
    cout << "\n";
}


//          Original simple approach to entering student Id using stoi()
// returns entered studentId or
//   on failure - returns 0  (ToDo - find another way to indicate failure - e.g. throw an exception
int getStudentId(ClassUI console) {
    string studentIdInput;
    unsigned int studentId;

    studentIdInput = console.getUserInput("Enter student ID: ");

    // try to make it robust, if a non-valid id is entered, e.g. abc#, catch the error & request again
    // stoi() is good & quick, but will quietly discard non-numeric chars or throw an error in some cases
    try {
        studentId = stoi(studentIdInput);
    }
    catch (const std::invalid_argument& ia) {
        console.writeOutput("Invalid student id: " + string(ia.what()) + '\n');
        return 0;
    }
    return studentId;
}
