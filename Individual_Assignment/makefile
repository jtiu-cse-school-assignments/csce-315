all: Individual_Assignment.o Books.o Courses.o Section.o
	g++ -std=c++11 Individual_assignment.o Books.o Courses.o Section.o -o main

Books.o: Books.cpp Books.hpp
	g++ -std=c++11 -c Books.cpp

Courses.o: Courses.cpp Courses.hpp Books.hpp Section.hpp
	g++ -std=c++11 -c Courses.cpp

Section.o: Section.cpp Section.hpp
	g++ -std=c++11 -c Section.cpp

Individual_Assignment.o: Individual_Assignment.cpp Books.hpp Courses.hpp Section.hpp
	g++ -std=c++11 -c Individual_Assignment.cpp

clean:
	rm *.o main