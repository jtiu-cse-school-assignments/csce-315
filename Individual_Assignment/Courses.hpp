#ifndef COURSES_H
#define COURSES_H

//////////////////////////////////////////////////////////////////////////// Header Files

#include <iostream>
#include <vector>

#include "Books.hpp"
#include "Section.hpp"

//////////////////////////////////////////////////////////////////////// Class Definition

class Courses {

private:

	std::string department;
	std::string courseNumber;
	std::string courseName;
	std::vector<Section> listOfSections;
	
public:

	Courses();
	
	std::string getDepartment() const;
	std::string getCourseNumber() const;
	std::string getCourseName() const;
	std::vector<Section> getSectionList() const;
	
	void setCourseNumber(std::string newCourseNumber);
	void setDepartment(std::string newDepartmentNumber);
	void setCourseName(std::string newCourseName);
	void pushToSectionList(Section newSection);
	
};

std::ostream& operator<<(std::ostream& out, const Courses course);

#endif