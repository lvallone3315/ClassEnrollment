#include "ClassDb.h"

#include <list>
#include <iostream>

// std::list<Class> ClassList;

ClassDb::ClassDb() {
    // Initialize ClassList - if needed
}

//      storeClassId()
// Create a class object with the classID
// push it onto the class list

void ClassDb::storeClassId(int classId) {
    std::cout << "ClassDb::Creating class (ie storing ClassId)\n";

}

//      enrollStudentInClass()
// search the class list to find the class object corresponding
// loop through all of the class objects in the class list
//   if the class is found, call the <object>.enrollStudent(student id) & return true
//   if the class is not found, return false

bool ClassDb::enrollStudentInClass(int studentId, int classId) {
    std::cout << "ClassDb::Enrolling student in Class\n";
    return true;


}
    
//      displayClassId()
// search the class list to find the class object correspoding to the classId
// loops through all of the class objects in the class list
//    if the class is found, output the <object>.displayStudentsInClassString() & return true
//    if the class is not found, return false
bool ClassDb::displayClassId(int classId, ClassUI console) {
    std::cout << "ClassDb:displaying class Id\n";
    return true;
};
