#include "StudentDb.h"
#include "Student.h"

#include <iostream>


//     Store the student Id at the end of the arrays (ie vectors & list)
//       three different storage approaches
//          vector array storing classes, vector array storing pointers to classes
//          list storing class
void StudentDb::storeStudentId(unsigned int studentId) {

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

void StudentDb::displayStudents(ClassUI console, string heading) {
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

void StudentDb::sandboxStudentDb(ClassUI console) {
    //   Playing with some of the vector & list capabilities - use local versions

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
    for (list <Student> ::iterator itr = studentList.begin(); itr != studentList.end(); itr++) {
        if (itr->getStudentId() == 3) {
            studentList.erase(itr);
            break;
        }
    }
    displayStudents(console, "List: After deleting front, back & student ID 3");
}

