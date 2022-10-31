#pragma once

#include <vector>
#include <string>

class Class
{
private:
	int classId;
	std::vector <int> enrolledStudents;

public:
	Class(int id);    // constructor - class object can only exist with a class #, ToDo - refactor to validate class identifier
	int getClassId(); // returns class identifier
	bool enrollStudent(int StudentId);   // enrolls a student in the class, ToDo - add validation of student id
	std::string getStudentsInClassString();   // returns a string listing all students in the class
	std::vector <int> getStudentsInClass();   // returns all of the students enrolled in the class, consider using list instead of vector
};

