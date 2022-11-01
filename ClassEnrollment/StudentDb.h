#pragma once

#include <vector>    // Vector support for tracking student objects
#include <list>      // list support for tracking student objects
#include <string>
#include "Student.h"
#include "ClassUI.h"


class StudentDb
{
private:
    // Global storage for student arrays so can use helper function to display
        // two versions
        //   1st vector of objects
        //   2nd vector of pointers to objects
    std::vector<Student> studentVector;
    std::vector<Student*> studentPointerVector;
    // list approach
    std::list<Student> studentList;

public:
    void displayStudents(ClassUI console, string heading);
    bool storeStudentId(unsigned int studentId);
};

