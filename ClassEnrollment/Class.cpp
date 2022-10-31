#include "Class.h"

#include <iostream>

// Class (ie school class) class :)
// each Class object contains the information relevant to a single course instance
// including the class # (integer) and the students enrolled in the class (student objects)

// constructor - class object can only exist with a class #,
// ToDo - refactor to validate class identifier
Class::Class(int id) {
	// store id into instance variable classId
	std::cout << "Class::construct class for id " << id << "\n";
}

// getClassId()
//   returns class id associated with this class instance

int Class::getClassId() {
	std::cout << "Class::Returns the integer class Id\n";
	return 0;

}

// enrollStudent(studentId)
//   1st version - add student to the class, even if already in the class
//      always return true (ie enrollment successful)
//   afterwards - validate student not already enrolled in class
//      if already enrolled, return false (ie error)
//
bool Class::enrollStudent(int StudentId) {
	std::cout << "Class::Enrolling the namned student in class " << classId << "\n";
	// add student to class vector enrolledSTudents & return true
	return true;
}

// getStudentsInClassString()
//    returns string containg all students in the class, with new lines inbetween each student id
std::string Class::getStudentsInClassString()
{
	// declare a local string variable
	// iterate through all students in the class, saving them in the string variable
	// return the string
	std::cout << "Class::returning a string listing all students in the class\n";
	return "";
}
