//////////////////////////////////////////////////////////////////////////// Header Files

#include <iostream>

#include "Courses.hpp"

////////////////////////////////////////////////////////////////////////////// Namespaces 

using namespace std;

//////////////////////////////////////////////////////////////////////////// Constructors

Courses::Courses() {
	department = "default";
	courseNumber = "default";
	courseName = "default";
	
} 

///////////////////////////////////////////////////////////////////////////////// Getters

string Courses::getDepartment() const {
	return department;
}

string Courses::getCourseNumber() const {
	return courseNumber;
}

string Courses::getCourseName() const {
	return courseName;
}	

vector<Section> Courses::getSectionList() const {
	return listOfSections;
}

///////////////////////////////////////////////////////////////////////////////// Setters

void Courses::setCourseNumber(string newCourseNumber) {
	courseNumber = newCourseNumber;
}

void Courses::setDepartment(string newDepartmentNumber) {
	department = newDepartmentNumber;
}

void Courses::setCourseName(string newCourseName) {
	courseName = newCourseName;
}

///////////////////////////////////////////////////////////// Non-Setter/Getter Functions

void Courses::pushToSectionList(Section newSection) {
	listOfSections.push_back(newSection);
}

//////////////////////////////////////////////////////////////////// Overloaded Functions

std::ostream& operator<<(std::ostream& out, const Courses course) {
	out << "(Department: " << course.getDepartment() << ") ";
	out << "(Course Number: " << course.getCourseNumber() << ") ";
	out << "(Course Name: " << course.getCourseName() << ") ";
	return out;
}
