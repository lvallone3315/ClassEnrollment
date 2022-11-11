#include "Class.h"

using namespace std;

// Class (ie school class) class :)
// each Class object contains the information relevant to a single course instance
// including the class # (integer) and the students enrolled in the class (student objects)

// constructor - class object can only exist with a class #,
// ToDo - refactor to validate class identifier
Class::Class(int id) {
	// store course id into instance variable classId
	classId = id;
}

// getClassId()
//   returns class id associated for this instance (ie object)

int Class::getClassId() {
	return classId;
}

// enrollStudent(studentId)
//   1st version - add student to the class, even if already in the class
//      always return true (ie enrollment successful)
//   afterwards - validate student not already enrolled in class
//      if already enrolled, return false (ie error)
//
bool Class::enrollStudent(int studentId) {
	// add student to class vector enrolledSTudents & return true
	enrolledStudents.push_back(studentId);
	return true;
}

// getStudentsInClassString()
//    returns string containg all students in the class, with new lines inbetween each student id
std::string Class::getStudentsInClassString()
{
	// declare a local string variable
	// iterate through all students in the class, saving them in the string variable
	// return the string

	std::string returnString = "";
	for (int i = 0; i < enrolledStudents.size(); i++) {
		returnString += std::to_string(enrolledStudents[i]);
		returnString += "\n";
	}
	return returnString;
}
