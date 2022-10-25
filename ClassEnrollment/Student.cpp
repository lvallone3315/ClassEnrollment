#include "Student.h"

/**
* Student class - see student.h for details
*/

// constructor - creates object with ID, only method to set the Id
Student::Student(unsigned int id) {
	studentId = id;
}

// returns student Id - stored & returned as unsigned int as Ids will never be negative
unsigned int Student::getStudentId() {
	return(studentId);
}
