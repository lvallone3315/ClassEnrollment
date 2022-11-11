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
#include <stdexcept>  // required for stoi - throws exception for invalid input (e.g. string starting with alphas
#include <string>
#include <vector>    // Vector support for tracking student objects
#include <list>      // list support for tracking student objects
#include <iterator>  // list related - needed to traverse list of student objects

using namespace std;

#define IGNORE_ORIGINAL_CODE

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
    ClassUI console;    // UI encapsulation - rather than directly writing to console - ToDo fix issues in parser class
    Parser parser;      // command parser - pass it a string - parser knows command format & returns struct
    Parser::InputStruct* parserOutput;
    StudentDb studentDb;  // aggregation of all students
    ClassDb classDb;      // aggregation of all classes

    string userInputString;   // raw user input - retrived from UI & redirected to parser for processing


    // local helper functions
    void displayStudents(ClassUI, string);
    int getStudentId(ClassUI console);
    void storeStudentId(unsigned int studentId);

    // ToDo - add versioning
    console.writeOutput("Hello Class Enrollment application!\n");

#ifndef IGNORE_ORIGINAL_CODE
    console.writeOutput("\n\n Enter 5 integers (student IDs - store in different vector & list structures & then display\n");
    system("pause");

    // original approach to data entry - before parser implemented
    // prompt user 5 times for a student ID, push onto the end of the storage array(s)
    unsigned int studentId;
    for (int i = 0; i < 5; i++) {
        if ((studentId = getStudentId(console)) != 0) {
            storeStudentId(studentId);
        }
        // else invalid entry - continue to get next student
    }
    displayStudents(console, "Displaying students entered using stoi() & stored in data structures in main\n\n");


    //   Playing with some of the vector & list capabilities - use local versions

    console.writeOutput("\nNext section - demonstrate different options for manipulating vectors & lists\n");
    system("pause");

    extern void sandboxStudentDb(ClassUI);   // declare just before use
    sandboxStudentDb(console);
#endif

    // Parser approach to data entry
    //    prompt user for a command and while that command isn't quit, grab student IDs
    //    Generally - methods return true (action completed successfully) or false - action not completed
    //       ToDo - track type of failures & store in the parser output structure
    //       ToDo - store actual user string in the parser output structure (this ToDo is also captured elsewhere)

    console.writeOutput("\nNext section - parser (separate class) to support user command entry\n");
    system("pause");

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
            if (!classDb.displayClassId(parserOutput->classId, console))
                console.writeOutput("Error! could not display class - likely class ID does not exist\n\n");
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


// The following code is part of the original approach which used a simple way to parse the input (stoi)
//   and kept the vectors & list storage in main()
//   Updated version moved all of this functionality to other classes & uses a real regex parser

    //     Store the student Id at the end of the arrays (ie vectors & list)
    //       three different storage approaches
    //          vector array storing classes, vector array storing pointers to classes
    //          list storing class
void storeStudentId(unsigned int studentId) {

    // push the object onto the vector array
    //   why does this work?  wouldn't the object get destroyed when storeStudentId exits?
    //   turns out the student object does get destroyed, but vector.push_back() is special :)
    Student student(studentId);
    studentVector.push_back(student);

    // allocate memory from the heap
    Student* studentP = new Student(studentId);
    studentPointerVector.push_back(studentP);

    // add the object created above to a list
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

//   Playing with some of the vector & list capabilities - use local storage (ie defined in main)
void sandboxStudentDb(ClassUI console) {
    // pushing an element at the beginning of the list
    Student student(99);
    studentList.push_front(student);
    studentVector.insert(studentVector.begin(), student);
    displayStudents(console, "Vector & List: adding student ID 99 to front\t\tNote: does not change pointer to object vector version");

    // erasing element at beginning, end & at a given position
    // vector
    studentVector.erase(studentVector.begin());
    studentVector.pop_back();
    studentVector.erase(studentVector.begin() + 2);  // erases element in 3rd position
    displayStudents(console, "Vector: after deleting front, back & 3rd element");

    // list
    studentList.pop_front();
    studentList.pop_back();
    for (list <Student> ::iterator itr = studentList.begin(); itr != studentList.end(); itr++) {
        if (itr->getStudentId() == 3) {
            studentList.erase(itr);
            break;
        }
    }
    displayStudents(console, "List: After deleting front, back & student ID 3");
}
