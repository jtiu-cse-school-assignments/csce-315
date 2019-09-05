                                      *************
                                      ** READ ME **
                                      *************

************************************ PROJECT DETAILS *************************************

CONTRIBUTERS: Michael Sallean, William Liu, Julian Tiu
SLN: TeamAssignment1.sln
* Requires at least Visual Studio 2017. Any previous versions will not work *

************************************** INSTRUCTIONS **************************************

Compilation is all done using the TeamAssignment1.sln file. To run, simply build and run in
Visual Studio 2017. 

************************************* FUNCTIONALITIES ************************************

DATABASE FUNCTIONALITIES INCLUDE: 

- DISPLAY NAMES AND ID NUMBER OF USERS
	- The user does not have to input a query. When this option is selected, the program
	  will automatically perform a query (SELECT: Name, ID ; FROM: user). After a query
	  is complete, a resulting table would be printed showing all the user names and IDs
	  available for look up
- DISPLAY NAMES AND ID NUMBER OF BUSINESSES
	- The user does not have to input a query. When this option is selected, the program
	  will automatically perform a query (SELECT: Name, ID ; FROM: business). 
	  After a query is complete, a resulting table would be printed showing all the 
	  business names and IDs available for look up
- LOOK UP USER INFORMATION
	- The user will input a user ID code, and the program will automatically perform a
	  query (SELECT: ID, Name, userRevCount, yelpingSince, friendList ; FROM: user).
	  The resulting table will allow the program to acces information that the user
	  specifies (ID, Name, userRevCount, yelpingSince, and friendList). Additionally,
	  natural join is used to combine the user, business and tip tables, and the resulting
	  table can be used to display information of all of the user's review of multiple
	  businesses. A count of how many reviews will also be displayed using the table's
	  count funtion.
- LOOK UP BUSINESS INFORMATION
	- The user will input a business ID code, and the program will automatically perform a
	  query (SELECT: ID, Name, Neighborhood, Address, City, State, Postal, Stars, 
	  Review_Count, longitude, latitude, and isOpen ; FROM: business ; 
	  WHERE: ID = IDInput). The resulting table will allow the program to acces 
	  information that the user specifies (ID, Name, Neighborhood, Address, City, State, 
	  Postal, Stars). Additionally, natural join is used to combine the user, business,
	  and tip tables and the resulting table can be used to display information of 
	  all of the business' review by every user. A count of how many reviews will also be 
	  displayed using the table's count function.
	  
UNUSED FUNCTIONALITIES:

- Table .size() function is unable to be used due to a logical/runtime error. Using this 
  function will display the wrong information, more specifically, when a record is deleted
  from a table, the .size() function will display a number that is less than the actual 
  amount. 
- Table makeKey() is unused, because the use of this function results in an unusable
  natural join function
- Table .min() function is unused, because it is not needed by the user
- Table .max() function is unused, because it is not needed by the user
- Table .crossJoin() function is unused, because it is not needed by the user
- Table .getRecordList() function is unused, because it is not needed by the user
- Database getTables() function is unused, because it is not needed by the user
- Database getSize() function is unused, because it is not needed by the user


*********************************** EXTERNAL LIBRARIES ***********************************

An external json.hpp was used to parse through and extract data from the JSON files to
convert different JSON objects to string inputted in the data-fields and attributes
of various records.

All documentation of the json.hpp can be found at: 
https://github.com/nlohmann/json/tree/develop
https://nlohmann.github.io/json/
	
