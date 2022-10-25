#pragma once

/**
* Student class - each object maintains information for a given student
*   for now - only the student ID is captured
* Student(student id) - creates student object with ID
*    note: no other method available for inutting (or changing) the student ID
* unsigned int getStudentId() - returns id
*/

class Student
{
public: 
	Student(unsigned int studentId);
	unsigned int getStudentId();

protected:
	unsigned int studentId;
};

