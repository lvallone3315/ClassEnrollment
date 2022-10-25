// ClassEnrollment.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "ClassUI.h"
#include "Parser.h"
#include "Student.h"
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
    ClassUI console;
    Parser parser;
    string userInputString;
    Parser::InputStruct *parserOutput;

    console.writeOutput("Hello World\n");

    // Test loop to verify parser works as expected

    for (int i = 0; i < 5; i++) {
        userInputString = console.getUserInput("Enter command: ");
        parserOutput = parser.parseInput(userInputString);
        parser.displayParsedOutput(parserOutput, console);
    }


    // Play with Vector & List arrays to store students

    string studentIdInput;
    unsigned int studentId;

    // helper functions
    void displayStudents(ClassUI, string);



    for (int i = 0; i < 5; i++) {
         studentIdInput = console.getUserInput("Enter student ID: ");

         // try to make it robust, if a non-valid id is entered, e.g. abc#, catch the error & request again
         // stoi() is good & quick, but will quietly discard non-numeric chars or throw an error in some cases
         try {
             studentId = stoi(studentIdInput);
         }
         catch (const std::invalid_argument& ia) {
             console.writeOutput("Invalid student id: " + string(ia.what()) + '\n');
             continue;
         }

         // push the object onto the vector array
         Student student (studentId);
         studentVector.push_back(student);

         // add the object to a list
         studentList.push_back(student);

         // allocate memory from the heap
         Student *studentP = new Student(studentId);
         studentPointerVector.push_back(studentP);
    }
    displayStudents(console, "Vector & List: after configuring entered student IDs");

    // pushing an element at the beginning of the list
    Student student(99);
    studentList.push_front(student);
    studentVector.insert(studentVector.begin(), student);
    displayStudents(console, "Vector & List: adding student ID 99 to front");

    // erasing element at beginning, end & given position
    // vector
    studentVector.erase(studentVector.begin());
    studentVector.pop_back();
    studentVector.erase(studentVector.begin() + 2);  // erases element in 3rd position
    displayStudents(console, "Vector: after deleting front, back & 3rd element");

    // list
    studentList.pop_front();
    studentList.pop_back();
    for (list <Student> :: iterator itr = studentList.begin(); itr != studentList.end(); itr++) {
        if (itr->getStudentId() == 3) {
            studentList.erase(itr);
            break;
        }
    }
    displayStudents(console, "List: After deleting front, back & student ID 3");

}

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
