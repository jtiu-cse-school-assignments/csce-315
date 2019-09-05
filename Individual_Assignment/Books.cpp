//////////////////////////////////////////////////////////////////////////// Header Files

#include <iostream>
#include <string>

#include "Books.hpp"

////////////////////////////////////////////////////////////////////////////// Namespaces 

using namespace std;

//////////////////////////////////////////////////////////////////////////// Constructors

Books::Books() {
	isbn = "N/A";
	title = "N/A";
	author = "N/A";
	date = "N/A";
	edition = "N/A";
	cost = "N/A";
	version = "N/A";
	bookStatus = "N/A";
}

///////////////////////////////////////////////////////////////////////////////// Getters

string Books::getIsbn() const {
	return isbn;
}

string Books::getTitle() const {
    return title;
}

string Books::getAuthor() const {
	return author;
}

string Books::getDate() const {
	return date;
} 

string Books::getEdition() const {
	return edition;
}

string Books::getCost() const {
	return cost;
}

string Books::getVersion() const {
	return version;
}

string Books::getBookStatus() const {
	return bookStatus;
}

///////////////////////////////////////////////////////////////////////////////// Setters

void Books::setIsbn(std::string newIsbnNumber) {
	isbn = newIsbnNumber;
}

void Books::setTitle(std::string newTitle) {
	title = newTitle;
}

void Books::setAuthor(std::string newAuthor) {
	author = newAuthor;
}

void Books::setDate(std::string newDate) {
	date = newDate;
}

void Books::setEdition(string newEdition) {
	edition = newEdition;
}

void Books::setCost(string newCost) {
	cost = newCost;
}

void Books::setVersion(string newVersion) {
	version = newVersion;
}

void Books::setBookStatus(string newBookStatus) {
	bookStatus = newBookStatus;
}

//////////////////////////////////////////////////////////////////// Overloaded Functions

ostream& operator<<(ostream& out, const Books book) {
	out << "(ISBN: " << book.getIsbn() << ")" << endl;
	out << "(Title: " << book.getTitle() << ")" << endl;
	out << "(Author: " << book.getAuthor() << ")" << endl;
	out << "(Publish Date: " << book.getDate() << ")" << endl;
	out << "(Edition: " << book.getEdition() << ")" << endl;
	out << "(Cost: " << book.getCost() << ")" << endl;
	out << "(Version: " << book.getVersion() << ")" << endl;
	return out;
}