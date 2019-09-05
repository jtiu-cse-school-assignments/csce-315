#ifndef SECTION_H
#define SECTION_H

//////////////////////////////////////////////////////////////////////////// Header Files

#include <iostream>
#include <vector>

#include "Books.hpp"

//////////////////////////////////////////////////////////////////////// Class Definition

class Section {
	
	private:
		
		std::string sectionNumber;
		std::vector<Books> listOfBooks;
		
	public:
		
		Section();
		
		std::string getSectionNumber() const;
		std::vector<Books> getBooksList() const;
		
		void pushToBooksList(Books newBook);
		
		void setSectionNumber(std::string newSectionNumber);
};

std::ostream& operator<<(std::ostream& out, const Section section);

#endif