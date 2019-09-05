#include "stdafx.h"
#include "Database.h"
#include <iostream>

using namespace std;

int main()
{

	Database schools_database;

	// Implementing texas_schools table 
	string * texas_schools_att = new string[2];
	texas_schools_att[0] = "School";
	texas_schools_att[1] = "City";
	Table texas_schools(texas_schools_att, 2);

	Record texas_schools_rec1(texas_schools_att, 2);
	texas_schools.insertRecord(&texas_schools_rec1);
	texas_schools_rec1.set("School", "Texas_A&M");
	texas_schools_rec1.set("City", "College_Station");

	Record texas_schools_rec2(texas_schools_att, 2);
	texas_schools.insertRecord(&texas_schools_rec2);
	texas_schools_rec2.set("School", "University_of_Houston");
	texas_schools_rec2.set("City", "Houston");

	Record texas_schools_rec3(texas_schools_att, 2);
	texas_schools.insertRecord(&texas_schools_rec3);
	texas_schools_rec3.set("School", "University_of_Texas");
	texas_schools_rec3.set("City", "Austin");

	Record texas_schools_rec4(texas_schools_att, 2);
	texas_schools.insertRecord(&texas_schools_rec4);
	texas_schools_rec4.set("School", "Rice");
	texas_schools_rec4.set("City", "Houston");

	Record texas_schools_rec5(texas_schools_att, 2);
	texas_schools.insertRecord(&texas_schools_rec5);
	texas_schools_rec5.set("School", "University_of_North_Texas");
	texas_schools_rec5.set("City", "Denton");

	
	// Implementing TAMU_department table 
	string * TAMU_department_att = new string[3];
	TAMU_department_att[0] = "Department";
	TAMU_department_att[1] = "Building";
	TAMU_department_att[2] = "Head";
	Table TAMU_departments(TAMU_department_att, 3);

	Record TAMU_department_rec1(TAMU_department_att, 3);
	TAMU_departments.insertRecord(&TAMU_department_rec1);
	TAMU_department_rec1.set("Department","CSCE");
	TAMU_department_rec1.set("Building", "HRBB");
	TAMU_department_rec1.set("Head", "Dilma_Da_Silva");

	Record TAMU_department_rec2(TAMU_department_att, 3);
	TAMU_departments.insertRecord(&TAMU_department_rec2);
	TAMU_department_rec2.set("Department", "CHEN");
	TAMU_department_rec2.set("Building", "JEB");
	TAMU_department_rec2.set("Head", "M._Nazmul_Karim");

	Record TAMU_department_rec3(TAMU_department_att, 3);
	TAMU_departments.insertRecord(&TAMU_department_rec3);
	TAMU_department_rec3.set("Department", "AERO");
	TAMU_department_rec3.set("Building", "HRBB");
	TAMU_department_rec3.set("Head", ""); // Rodney Bowersox
	
	// Implementing students table 
	string * students_att = new string[5];
	students_att[0] = "First";
	students_att[1] = "Last";
	students_att[2] = "School";
	students_att[3] = "Department";
	students_att[4] = "Graduating_Year";
	Table students(students_att, 5);
	/*
	Record students_rec1(students_att, 5);
	students.insertRecord(&students_rec1);
	students_rec1.set("First", "Julian");
	students_rec1.set("Last", "Tiu");
	students_rec1.set("School", "Texas_A&M");
	students_rec1.set("Department", "CSCE");
	students_rec1.set("Graduating_Year", "2019");
	
	Record students_rec2(students_att, 5);
	students.insertRecord(&students_rec2);
	students_rec2.set("First", "Will");
	students_rec2.set("Last", "Yu");
	students_rec2.set("School", "Texas_A&M");
	students_rec2.set("Department", "CSCE");
	students_rec2.set("Graduating_Year", "2018");

	Record students_rec3(students_att, 5);
	students.insertRecord(&students_rec3);
	students_rec3.set("First", "Andrew");
	students_rec3.set("Last", "Hue");
	students_rec3.set("School", "Texas_A&M");
	students_rec3.set("Department", "CHEN");
	students_rec3.set("Graduating_Year", "2019");

	Record students_rec4(students_att, 5);
	students.insertRecord(&students_rec4);
	students_rec4.set("First", "Yessi");
	students_rec4.set("Last", "Alti");
	students_rec4.set("School", "University_of_Texas");
	students_rec4.set("Department", "STAT");
	students_rec4.set("Graduating_Year", "2017");

	Record students_rec5(students_att, 5);
	students.insertRecord(&students_rec5);
	students_rec5.set("First", "Marco");
	students_rec5.set("Last", "Tag");
	students_rec5.set("School", "University_of_Houston");
	students_rec5.set("Department", "NURS");
	students_rec5.set("Graduating_Year", "2020");

	Record students_rec6(students_att, 5);
	students.insertRecord(&students_rec6);
	students_rec6.set("First", "Jeff");
	students_rec6.set("Last", "Tame");
	students_rec6.set("School", "Texas_A&M");
	students_rec6.set("Department", "AERO");
	students_rec6.set("Graduating_Year", "2017");*/
	
	// Populating database object schools_database 
	schools_database.addTable(texas_schools, "Texas Schools");
	schools_database.addTable(TAMU_departments, "TAMU Departments");
	schools_database.addTable(students, "Students");
	
	// Listing all tables in the database 
	string tablesList = schools_database.listTables();
	cout << tablesList << endl;
	
	// Dropping TAMU_departments, getting list of tables, then adding TAMU_departments back
	schools_database.dropTable("TAMU Departments");
	string tablesList2 = schools_database.listTables();
	cout << tablesList2 << endl;
	schools_database.addTable(TAMU_departments, "TAMU Departments");
	string tablesList3 = schools_database.listTables();
	cout << tablesList3 << endl;
	
	// Getting size of the database object with inserted tables 
	cout << schools_database.getSize() << endl;

	// Adding attribute to students table, then deleting the attribute 
	students.addAttribute("hello");
	// You guys do not have a function that returns the attributes of the table
	students.dropAttribute("hello");

	// Getting sizes of all the tables 
	cout << students.getSize() << endl;
	cout << TAMU_departments.getSize() << endl;
	cout << texas_schools.getSize() << endl;

	// Iterating to find an attribute for TAMU_departments
	//int itt = TAMU_departments.getKey("Building");
	//cout << "Iterator spot fot 'Building' attribute: " << itt << endl;

	// Setting attribute keys for all tables 
	students.makeKey("Last");
	TAMU_departments.makeKey("Department");
	texas_schools.makeKey("School");
	
	// Cross-joining students and texas_schools 
	Table * crossJoin_texas_schools_and_TAMU_departments;
	crossJoin_texas_schools_and_TAMU_departments = texas_schools.crossJoin(&texas_schools, &TAMU_departments);

	// Natural-joining students and texas_schools 
	Table * naturalJoin_texas_schools_and_students;
	naturalJoin_texas_schools_and_students = texas_schools.naturalJoin(&texas_schools, &students);

	// Natural-join TAMU_departments and students
	Table * naturalJoin_TAMU_departments_and_students;
	naturalJoin_TAMU_departments_and_students = TAMU_departments.naturalJoin(&TAMU_departments, &students);

	// Counting non-null entries for TAMU_department's 'Head' attribute 
	//cout << "# of department heads in TAMU_department: " << TAMU_departments.count("Head") << endl;

	// Counting non-null entries for student's 'First' attribute 
	//cout << "# of students with first names: " << students.count("First") << endl;

	// Finding min in texas_schools's 'City' attribute: checks to see if return value is lexicographically min
	//texas_schools.min("City");

	// Finding min in students's 'Graduating Year' attribute 
	//students.min("Graduating Year");

	// Finding max in students's 'Graduating Year' attribute 
	//students.max("Graduating Year");
	
	// Query test1 
	string * somethingToPutForQueryTable1 = new string();
	somethingToPutForQueryTable1[0] = "N/A";
	Table queryTest1(somethingToPutForQueryTable1, 1);
	string * SELECT1 = new string();
	SELECT1[0] = "Graduating Year";
	queryTest1 = *schools_database.query(SELECT1, 1, "Students", "Graduating_Year > 2017");
	// You guys don't have a function that displays the attributes of the table
	queryTest1.getSize();
	
	// Query test2 
	string * somethingToPutForQueryTable2 = new string();
	somethingToPutForQueryTable2[0] = "N/A";
	Table queryTest2(somethingToPutForQueryTable2, 1);
	string * SELECT2 = new string[4];
	SELECT2[0] = "First";
	SELECT2[1] = "Last";
	SELECT2[2] = "Graduating Year";
	SELECT2[3] = "School";
	queryTest2 = *schools_database.query(SELECT2, 4, "Students", "Graduating_Year >= 2019 AND (School = Texas_A&M OR School = University_Of_Houston)");
	// You guys don't have a function that displays the attributes of the table
	queryTest2.getSize();
	return 0;
}