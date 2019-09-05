/* 	
*	INDIVIDUAL ASSIGNMENT
*	Julian Tiu
*	CSCE 315
*/

//////////////////////////////////////////////////////////////////////////// Header Files

#include <stdio.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <iterator>

#include "Books.hpp"
#include "Courses.hpp"
#include "Section.hpp"

////////////////////////////////////////////////////////////////////////////// Namespaces 
using namespace std;

/////////////////////////////////////////////////////////////////////////////// Functions

/****************************************************************************************
*	Given the ISBN number, this function finds the book
*/
multimap<string, Books>::iterator findBooks(string isbn, multimap<string, Books> &booksMap) {
	
	/* find() is defined in the multimap stl */
	multimap<string, Books>::iterator book = booksMap.find(isbn);
	
	return book;
}

/****************************************************************************************
*	
*/
void commandPD(vector<char *> &tokenizedCommand, multimap<string, Courses> &courseReferenceMap) {
	
	vector<Books> courseBooksListRef;
	vector<Books> courseBooksList;
	int matchedBookCounter;
	
	/* pair is defined in the standard library
	 *	equal_range() is defined in the multimap stl
	 */
	pair<map<string,Courses>::iterator, map<string,Courses>::iterator> equalDepartmentRange;
	equalDepartmentRange = courseReferenceMap.equal_range(tokenizedCommand[1]);

	for(auto Itr = equalDepartmentRange.first; Itr != equalDepartmentRange.second; ++Itr) {
		for(int i = 0; i < Itr->second.getSectionList().size(); i++) {
			courseBooksListRef.push_back(Itr->second.getSectionList().at(i).getBooksList().at(0));
		}
	}
	
	/*	Since each section will be put in the courseSectionList multiple times, the nested
	*	loop ensures that there will be no duplicates of any books
	*/
	for(int j = 0; j < courseBooksListRef.size(); j++) {
		
		matchedBookCounter = 0;
		
		for(int k = 0; k < j; k++) {
			if(courseBooksListRef.at(j).getIsbn() == courseBooksListRef.at(k).getIsbn()) {
				matchedBookCounter++;
			}
		}
		if(matchedBookCounter == 0) {
			courseBooksList.push_back(courseBooksListRef.at(j));
		}
	}

	for(int l = 0; l < courseBooksList.size(); l++) {
		cout << endl << courseBooksList.at(l) << endl;
	}
}

/****************************************************************************************
*	String tokenizer is defined in the Standard Template Library and utilizes the strtok
*	function to separate strings with a defined delimiter 
*/
vector<char *> dateTokenization(string date) {
	
	vector<char *> tokenizedDate;
	char *tokens = strtok((char *)date.c_str(), "/");
    
	while(tokens!=NULL) {
		tokenizedDate.push_back(tokens);
		tokens = strtok(NULL, "/");
	}
	
	return tokenizedDate;
}

/****************************************************************************************
*	
*/
void commandPY(vector<char *> &tokenizedCommand, multimap<string, Books> &booksMap) {
	
	vector<char *> tokenizedCommandDate;
	vector<char *> tokenizedBookDate;
	int commandMonth;
	int bookMonth;
	int commandYear;
	int bookYear;
	
	tokenizedCommandDate = dateTokenization(tokenizedCommand[1]);
	
	/*	stoi() is defined in the STL. It converts string to integer value */
	commandMonth = stoi(tokenizedCommandDate[0], nullptr);
	commandYear = stoi(tokenizedCommandDate[1], nullptr);
	
	for(auto book = booksMap.cbegin(); book != booksMap.cend(); ++book) {
		tokenizedBookDate = dateTokenization(book->second.getDate());
		bookMonth = stoi(tokenizedBookDate[0], nullptr);
		bookYear = stoi(tokenizedBookDate[1], nullptr);
		
		if(bookYear > commandYear) {
			cout << endl << book->second << endl;
		}
		else if((bookYear == commandYear) && (bookMonth > commandMonth)) {
			cout << endl << book->second << endl;
		}
		else if((bookYear == commandYear) && (bookMonth == commandMonth)) {
			cout << endl << book->second << endl;
		}
	}
}

/****************************************************************************************
*
*/
void commandPC(multimap<string, Courses> &courseReferenceMap) {
	
	for(auto it = courseReferenceMap.cbegin(); it != courseReferenceMap.cend(); ++it)
	{
		cout << endl << it->second << endl;
	}
}

/****************************************************************************************
*
*/
void commandPB(multimap<string, Books> &booksMap) {
	
	for(auto it = booksMap.cbegin(); it != booksMap.cend(); ++it) {
		cout << endl << it->second << endl;
	}
}

/****************************************************************************************
*
*/
void commandGB(vector<char *> &tokenizedCommand, multimap<string, Books> &booksMap) {
	
	string isbn = tokenizedCommand[1];
	multimap<string, Books>::iterator book;
	
	book = findBooks(isbn, booksMap);
	cout << book->second << endl;
}

/****************************************************************************************
*
*/
void commandGS(vector<char *> &tokenizedCommand, multimap<string, Courses> &courseReferenceMap) {
	
	string department = tokenizedCommand[1];
	string courseNumber = tokenizedCommand[2];
	string sectionNumber = tokenizedCommand[3];
	
	Courses newCourse;
	Section matchedSection;
	vector<Section> courseSectionList;
	vector<Books> booksList;
	
	/* pair is defined in the standard library
	 *	equal_range() is defined in the multimap stl
	 */
	pair<map<string,Courses>::iterator, map<string,Courses>::iterator> equalDepartmentRange;
	equalDepartmentRange = courseReferenceMap.equal_range(department);
	
	for(auto Itr = equalDepartmentRange.first; Itr != equalDepartmentRange.second; ++Itr) {
		if(Itr->second.getCourseNumber() == courseNumber) {
			newCourse = Itr->second;
		}
	}
	
	courseSectionList = newCourse.getSectionList();
	
	for(int i = 0; i < courseSectionList.size(); i++) {
		if(courseSectionList.at(i).getSectionNumber() == sectionNumber) {
			cout << endl << courseSectionList.at(i) << endl;
 			matchedSection = courseSectionList.at(i);
			booksList = matchedSection.getBooksList();
			cout << booksList.at(0) << endl;

		}
	}
}

/****************************************************************************************
*
*/
void commandGC(vector<char *> &tokenizedCommand, multimap<string, Courses> &courseReferenceMap) {
	
	string department = tokenizedCommand[1];
	string courseNumber = tokenizedCommand[2];
	Courses newCourse;
	vector<Section> sectionList;
	vector<Books> booksList;
	
	/* pair is defined in the standard library
	 *	equal_range() is defined in the multimap stl
	 */
	pair<map<string,Courses>::iterator, map<string,Courses>::iterator> equalDepartmentRange;
	equalDepartmentRange = courseReferenceMap.equal_range(department);
	
	for(auto Itr = equalDepartmentRange.first; Itr != equalDepartmentRange.second; ++Itr) {
		if(Itr->second.getCourseNumber() == courseNumber) {
			newCourse = Itr->second;
		}
	}
	
	sectionList = newCourse.getSectionList();
	
	for(int i = 0; i < sectionList.size(); i++) {
		booksList = sectionList.at(i).getBooksList();
		cout << endl << sectionList.at(i) << endl;
		cout << booksList[0] << endl;
	}
}

/****************************************************************************************
*
*/
void commandA(vector<char *> &tokenizedCommand, multimap<string, Books> &booksMap, multimap<string, Courses> &courseReferenceMap) {
	
	string isbn = tokenizedCommand[1];
	string department = tokenizedCommand[2];
	string courseNumber = tokenizedCommand[3];
	string sectionNumber = tokenizedCommand[4];
	string status = tokenizedCommand[5];
	multimap<string, Books>::iterator booksMapIterator;
	Courses newCourse;
	Section newSection;
	Books matchedBook;
	vector<Section> sectionList;
	
	booksMapIterator = findBooks(isbn, booksMap);
	matchedBook = booksMapIterator->second;
	
	newSection.setSectionNumber(sectionNumber);
	matchedBook.setBookStatus(status);
	newSection.pushToBooksList(matchedBook);
	
	/* pair is defined in the standard library
	 *	equal_range() is defined in the multimap stl
	 */
	pair<map<string,Courses>::iterator, map<string,Courses>::iterator> equalDepartmentRange;
	equalDepartmentRange = courseReferenceMap.equal_range(department);
	
	for(auto Itr = equalDepartmentRange.first; Itr != equalDepartmentRange.second; ++Itr) {
		if(Itr->second.getCourseNumber() == courseNumber) {
			newCourse = Itr->second;
			newCourse.pushToSectionList(newSection);
			Itr->second = newCourse;
			
		}
	}
}


/****************************************************************************************
*
*/
void commandC(vector<char *> &tokenizedCommand, multimap<string, Courses> &courseReferenceMap) {
	
	string courseName;
	string department = tokenizedCommand[1];
	string courseNumber = tokenizedCommand[2];
	int noMatchCounter = 0;
	int iteratorCounter = 0;
	Courses newCourse;
	
	newCourse.setDepartment(department);
	newCourse.setCourseNumber(courseNumber);
	
	for(int i = 3; i < tokenizedCommand.size(); i++) {
		courseName.append(tokenizedCommand[i]);
		courseName.append(" ");
	}
	
	newCourse.setCourseName(courseName);
	
	/* 	Duplicate course number or course name is not allowed. Instead, the existing
	*	course's information will be modified. Otherwise, a new course is defined
	*/
	if(courseReferenceMap.count(department) > 0) {
		pair<map<string,Courses>::iterator, map<string,Courses>::iterator> ret;
		ret = courseReferenceMap.equal_range(newCourse.getDepartment());
	
		for(auto Itr = ret.first; Itr != ret.second; ++Itr) {
			if(Itr->second.getCourseNumber() == courseNumber) {
				Itr->second.setCourseName(courseName);
			}
			else if(Itr->second.getCourseName() == courseName) {
				Itr->second.setCourseNumber(courseNumber);
			}
			else if((Itr->second.getCourseNumber() == courseNumber) && (Itr->second.getCourseName() == courseName)) {
				Itr->second.setCourseName(courseName);
				Itr->second.setCourseNumber(courseNumber);
			}
			else {
				noMatchCounter++;
			}
			iteratorCounter++;
		}

		if(iteratorCounter == noMatchCounter) {
			courseReferenceMap.insert (pair<string, Courses>(newCourse.getDepartment(), newCourse));
		}
	} 
	else {
		courseReferenceMap.insert (pair<string, Courses>(newCourse.getDepartment(), newCourse));
	}
}

/****************************************************************************************
*
*/
void commandM(vector<char *> &tokenizedCommand, multimap<string, Books> &booksMap) {
	
	string isbn = tokenizedCommand[1];
	string cost = tokenizedCommand[2];
	string version = tokenizedCommand[3];
	
	multimap<string, Books>::iterator it = booksMap.find(isbn);
	
	it->second.setCost(cost);
	it->second.setVersion(version);
	
}

/****************************************************************************************
*
*/
void commandD(vector<char *> &tokenizedCommand, multimap<string, Books> &booksMap) {
	
	string isbn = tokenizedCommand[1];
	string option = tokenizedCommand[2];
	string value;
	
	multimap<string, Books>::iterator it = booksMap.find(isbn);
	
	if(option == "A") {
		
		/*	The delimiter for the string tokenization are spaces. If the name of the
		 *	author contains spaces, this will append them to one string
		 */
		for(int i = 3; i < tokenizedCommand.size(); i++) {
			value.append(tokenizedCommand[i]);
			value.append(" ");
		}
		
		it->second.setAuthor(value);
	}
	else if(option == "E") {
		value = tokenizedCommand[3];
		it->second.setEdition(value);
	}
	else if(option == "D") {
		value = tokenizedCommand[3];
		it->second.setDate(value);
	} 
	else {
		cout << "error: Invalid Option" << endl;
	}
}

/****************************************************************************************
*
*/
void commandB(vector<char *> &tokenizedCommand, multimap<string, Books> &booksMap) {
	
	string title;
	Books newBook;
	newBook.setIsbn(tokenizedCommand[1]);
	
	/*	The delimiter for the string tokenization are spaces. If the title of the book
	 *	contains spaces, this will append them to one string
	 */
	for(int i = 2; i < tokenizedCommand.size(); i++) {
		title.append(tokenizedCommand[i]);
		title.append(" ");
	}
	
	newBook.setTitle(title);
	
	if(booksMap.count(newBook.getIsbn()) > 0) {
		multimap<string, Books>::iterator it = booksMap.find(newBook.getIsbn());
		it->second.setTitle(title);
	} 
	else {
		booksMap.insert (pair<string, Books>(newBook.getIsbn(), newBook));
	}
}

/****************************************************************************************
*	In order for the command interpreter function to recognize the first one/two letter/s
*	of the command inputted from the user, this function tokenizes the user's inputted
*	string
*
*	String tokenizer is defined in the Standard Template Library and utilizes the strtok
*	function to separate strings with a defined delimiter 
*/
vector<char *> stringTokenization(string commandInput) {
	
	/* 	a vector must be used to store the tokenized string
	*		- stl function strtok() does not store these values anywhere 
	*/
	vector<char *> tokenizedCommand;
	char *tokens = strtok((char *)commandInput.c_str(), " ");
    
	while(tokens!=NULL) {
		tokenizedCommand.push_back(tokens);
		tokens = strtok(NULL, " ");
	}
	
	return tokenizedCommand;
}

/****************************************************************************************
*	
*/
void commandInterpreter(string command, multimap<string, Books> &booksMap, multimap<string, Courses> &courseReferenceMap) {
	
	vector<char *> tokenizedCommand;
	string firstCommandLetter;
	
	tokenizedCommand = stringTokenization(command);
	firstCommandLetter = tokenizedCommand[0];
	
	if(firstCommandLetter == "B") {
		commandB(tokenizedCommand, booksMap);
	} 
	else if(firstCommandLetter == "D") {
		commandD(tokenizedCommand, booksMap);
	}
	else if(firstCommandLetter == "M") {
		commandM(tokenizedCommand, booksMap);
	}
	else if(firstCommandLetter == "C") {
		commandC(tokenizedCommand, courseReferenceMap);
	}
	else if(firstCommandLetter == "A") {
		commandA(tokenizedCommand, booksMap, courseReferenceMap);
	}
	else if(firstCommandLetter == "GC") {
		commandGC(tokenizedCommand, courseReferenceMap);
	}
	else if(firstCommandLetter == "GS") {
		commandGS(tokenizedCommand, courseReferenceMap);
	}
	else if(firstCommandLetter == "GB") {
		commandGB(tokenizedCommand, booksMap);
	}
	else if(firstCommandLetter == "PB") {
		commandPB(booksMap);
	}
	else if(firstCommandLetter == "PC") {
		commandPC(courseReferenceMap);
	}
	else if(firstCommandLetter == "PY") {
		commandPY(tokenizedCommand, booksMap);
	}
	else if(firstCommandLetter == "PD") {
		commandPD(tokenizedCommand, courseReferenceMap);
	}
	else if(firstCommandLetter == "PM") {
	
	}
	else {
		cout << "error: invalid command" << endl;
	}
}

//////////////////////////////////////////////////////////////////////////////////// Main

int main(int argc, char* argv[]) {
	
	string command;
	multimap<string, Books> booksMap;
	multimap<string, Courses> courseReferenceMap;
	
	do{
		cout << "\n******************* ENTER COMMAND ******************* " << endl;
		getline(cin,command);
		cout << command << endl;	
		commandInterpreter(command, booksMap, courseReferenceMap);
	} while (!cin.eof());

  return 0;

}