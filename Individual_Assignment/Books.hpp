#ifndef BOOKS_H
#define BOOKS_H

//////////////////////////////////////////////////////////////////////////// Header Files

#include <string>
#include <iostream>

//////////////////////////////////////////////////////////////////////// Class Definition

class Books {

private:

	std::string isbn;
	std::string title;
	std::string author;
	std::string date;
	std::string edition;
	std::string version;
	std::string cost;
	std::string bookStatus;
	
public:

	Books();
	
	std::string getIsbn() const;
	std::string getTitle() const;
	std::string getAuthor() const;
	std::string getDate() const;
	std::string getEdition() const;
	std::string getVersion() const;
	std::string getCost() const;
	std::string getBookStatus() const;
	
	void setIsbn(std::string newIsbnNumber);
	void setTitle(std::string newTitle);
	void setAuthor(std::string newAuthor);
	void setDate(std::string newDate);
	void setEdition(std::string newEdition);
	void setCost(std::string newCost);
	void setVersion(std::string newVersion);
	void setBookStatus(std::string newBookStatus);
	
};

std::ostream& operator<<(std::ostream& out, const Books book);

#endif