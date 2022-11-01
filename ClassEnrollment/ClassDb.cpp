#include "ClassDb.h"

#include <list>
#include <iostream>

// ClassDb
//   manage a database of course instances (aka classes)
//   database created as a list, allowing easy addition & deletion of instances
//     (Note: course deletion not implemented yet)
//   cout are for student debugging purposes & could be deleted

ClassDb::ClassDb() {
    // Initialize ClassList - if needed
}

//      storeClassId()
// Create a class object with the classID
// push it onto the class list
//     Returns true if class record creation is successful, false if failed 
//       (ToDo - currently always true, check for failure when adding to db

bool ClassDb::storeClassId(int classId) {
    std::cout << "ClassDb::Creating course instance " << classId << "\n\n";
    Class classObject(classId);
    classList.push_back(classObject);
    return true;

}

//      enrollStudentInClass()
// search the class list to find the class object corresponding
// loop through all of the class objects in the class list
//   if the class is found, call the <object>.enrollStudent(student id) & return true
//   if the class is not found, return false

bool ClassDb::enrollStudentInClass(int studentId, int classId) {
    std::cout << "ClassDb::Trying to enroll student " << studentId << " in Class " << classId << "\n\n";
    list <Class> ::iterator itr;
    for (itr = classList.begin(); itr != classList.end(); itr++) {
        if (itr->getClassId() == classId) {
            itr->enrollStudent(studentId);
            return true;
        }
    }
    return false;
}
    
//      displayClassId()
// search the class list to find the class object correspoding to the classId
// loops through all of the class objects in the class list
//    if the class is found, output the <object>.displayStudentsInClassString() & return true
//    if the class is not found, return false
bool ClassDb::displayClassId(int classId, ClassUI console) {
    std::cout << "ClassDb:displaying class Id\n";
    list <Class> ::iterator itr;
    for (itr = classList.begin(); itr != classList.end(); itr++) {
        if (itr->getClassId() == classId) {
            std::cout << itr->getStudentsInClassString();
            return true;
        }
    }
    return false;
};
