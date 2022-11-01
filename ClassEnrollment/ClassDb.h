#pragma once
#include <list>
#include "ClassUI.h"
#include "Class.h"

class ClassDb
{
private:
    std::list<Class> classList;

public:
    ClassDb();
    bool storeClassId(int classId);
    bool enrollStudentInClass(int studentId, int classId);  // returns true if student enrolled in class, false if class doesn't exist
    bool displayClassId(int classId, ClassUI console);      // outputs all of the students in the specified class
};

