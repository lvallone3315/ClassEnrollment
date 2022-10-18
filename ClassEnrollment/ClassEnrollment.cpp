// ClassEnrollment.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "ClassUI.h"
#include "Student.h"
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

int main()
{
    ClassUI console;
    console.writeOutput("Hello World\n");

    string studentIdInput;
    unsigned int studentId;
    std::vector<Student> allStudents;
    std::vector<Student*> sPtr;

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
         allStudents.push_back(student);

         // allocate memory from the heap
         Student *studentP = new Student(studentId);
         sPtr.push_back(studentP);
    }

    //for (Student studentIndex : allStudents) {
    for (int i = 0; i < allStudents.size(); i++) {
        console.writeOutput(to_string(allStudents[i].getStudentId()) + "\n");
    }
    for (Student j : allStudents) {
        cout << j.getStudentId();
    }
    cout << "\n";
    for (Student* p : sPtr) {
        cout << p->getStudentId();
    }
}
