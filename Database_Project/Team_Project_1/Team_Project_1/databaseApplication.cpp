#include "stdafx.h"
#include "Database.h"
#include "json.hpp"
#include <iostream>
#include <fstream>
#include <typeinfo>
#include <string>

#ifdef _WIN32
#define CLEAR "cls"
#else //In any other OS
#define CLEAR "clear"
#endif

using namespace std;

void print_database_table(Table* in_table) {
	Table real_table;
	real_table = *in_table;
	for (int i = 0; i < real_table.listAttributes().size(); i++) {
		cout << real_table.listAttributes()[i] << '\t';
	}
	cout << endl;
	//Iterate through records to print data
	vector<Record*> rec_list_ptr = real_table.getRecordList();
	for (int i = 0; i < rec_list_ptr.size();i++) {
		Record real_rec;
		real_rec = *rec_list_ptr[i];
		for (int j = 0; j < real_rec.listAttr().size();j++) {
			cout << real_rec.listAttr()[i] << "\t";
		}
		cout << endl;
	}
}

void display_user_name_ID(Database yelpDatabase) {
	/*
	*	- DO A QUERY HERE!
	*	- SELECT:	userID, userName
	*	- FROM:		userTable
	*	- WHERE:	BLANK
	*
	*	- PRINT THE RESULTING TABLE FOR USER TO SEE
	*/
	Table* user_name_table; 
	string real_str = "userID userName";
	string* ptr_str = &real_str;
	user_name_table = yelpDatabase.query(ptr_str, 2, "userTable", "");
	print_database_table(user_name_table);
	system(CLEAR);
}

void display_business_name_ID(Database yelpDatabase) {
	/*
	*	- DO A QUERY HERE!
	*	- SELECT:	Business ID, Business Name
	*	- FROM:		businessTable
	*	- WHERE:	BLANK
	*
	*	- PRINT THE RESULTING TABLE FOR USER TO SEE
	*/
	Table* buisness_name_table;
	string real_str = "buisnessID buisnessName";
	string* ptr_str = &real_str;
	buisness_name_table = yelpDatabase.query(ptr_str,2, "buisnessTable", "");
	print_database_table(buisness_name_table);
	system(CLEAR);
}

void userInformation(Database yelpDatabase) {
		
	/*
	*	- DO A QUERY HERE!
	*	- SELECT:	User ID, User Name, Review Count, Yelping Since, Friends
	*	- FROM:		userTable
	*	- WHERE:	User ID = user_ID
	*/
	
	Table* name_table;
	string real_str = "userID userName reviewCount yelpingSince";
	string* ptr_str = &real_str;
	cout << "Please enter user ID:" << endl;
	string USERNAME;
	cin >> USERNAME;
	name_table = yelpDatabase.query(ptr_str, 4, "userTable", USERNAME + " == userName");
	//print_database_table(name_table);
	Table* b_table;
	real_str = "buisnessName reviews";
	ptr_str = &real_str;
	b_table = yelpDatabase.query(ptr_str, 2, "buisnessTable", "buisnessName == reviewedBuisnesses");
	Table dummytable;
	Table* joined_table = dummytable.naturalJoin(name_table, b_table);

	int user_information_options;
	
	do {
		system(CLEAR);
		// DO NOT MODIFY. IT LOOKS LIKE THIS DUE TO DOUBLE \\ CHARACTERS
		cout << endl;
		cout << " _______________________________________________________________________ \n";
		cout << "| --------------------------------------------------------------------- |\n";
		cout << "||                    ___     ___ _____ __     _____                   ||\n";
		cout << "||                    \\  \\  /  / |   _||  |   |     \\                  ||\n";
		cout << "||                     \\  \\/  /  |  |_ |  |   |  O  |                  ||\n";
		cout << "||                      \\    /   |   _||  |   |   __/                  ||\n";
		cout << "||                       |  |    |  |_ |  |__ |  |                     ||\n";
		cout << "||                       |__|    |____||_____||__|                     ||\n";
		cout << "||  ___      __     ________   __      ___       __      ______  _____ ||\n";
		cout << "|| |   \\    /  \\   |___   __| /  \\    |   \\     /  \\    |  ____||  __| ||\n";
		cout << "|| |    \\  /    \\     |  |   /    \\   | O /    /    \\   | |____ |  |_  ||\n";
		cout << "|| |    | /  __  \\    |  |  /  __  \\  |   \\   /  __  \\  |____  ||   _| ||\n";
		cout << "|| |    //  /  \\  \\   |  | /  /  \\  \\ | O  \\ /  /  \\  \\  ____| ||  |_  ||\n";
		cout << "|| |___//__/    \\__\\  |__|/__/    \\__\\|____//__/    \\__\\|______||____| ||\n";
		cout << "||_____________________________________________________________________||\n";
		cout << "||---------------------------------------------------------------------||\n";
		cout << "||               WHICH INFORMATION WOULD YOU LIKE TO VIEW?             ||\n";
		cout << "||---------------------------------------------------------------------||\n";
		cout << "||                                                                     ||\n";
		cout << "|| 1: NAME                                                             ||\n";
		cout << "|| 2: REVIEW COUNT                                                     ||\n";
		cout << "|| 3: YELPING SINCE                                                    ||\n";
		cout << "|| 4: REVIEWED BUSINESSES                                              ||\n";
		cout << "|| 5: READ ALL REVIEWS                                                 ||\n";
		cout << "|| 6: BACK                                                             ||\n";
		cout << "||_____________________________________________________________________||\n";
		cout << " ----------------------------------------------------------------------- \n";
		cin >> user_information_options;
		
		Table readtable;
		readtable = *joined_table;

		switch(user_information_options) {
			case 1:
				for (int i = 0; i < readtable.getSize();i++) {
					Record* ptrrec = readtable.getRecordList()[i];
					Record datarec = *ptrrec;
					//Output Name
					cout << datarec.listAttr()[2] << endl;
				}
				break;
			case 2:
				for (int i = 0; i < readtable.getSize();i++) {
					Record* ptrrec = readtable.getRecordList()[i];
					Record datarec = *ptrrec;
					//Output Review Count 
					cout << datarec.listAttr()[3] << endl;
				}
				break;
			case 3:
				for (int i = 0; i < readtable.getSize();i++) {
					Record* ptrrec = readtable.getRecordList()[i];
					Record datarec = *ptrrec;
					//Output Yelping Since
					cout << datarec.listAttr()[4] << endl;
				}
				break;
			case 4:
				for (int i = 0; i < readtable.getSize();i++) {
					Record* ptrrec = readtable.getRecordList()[i];
					Record datarec = *ptrrec;
					//Output Reviewed Buisnesses
					cout << datarec.listAttr()[5] << endl;
				}
				break;
			case 5:
				for (int i = 0; i < readtable.getSize();i++) {
					Record* ptrrec = readtable.getRecordList()[i];
					Record datarec = *ptrrec;
					//Output all reviews
					cout << datarec.listAttr()[6] << endl;
				}
				break;
			case 6:
				break;
			default:
				break;
		}
		
	} while(user_information_options != 6);
	
}

void businessInformation(Database yelpDatabase) {
	
	
	/*
	*	- DO A QUERY HERE!
	*	- SELECT:	Business ID, Business Name, Address, City, State, Zip, Stars, Review Count, Status (open or closed)
	*	- FROM:		businessTable
	*	- WHERE:	Business ID = business_ID
	*/
	
	Table* buisness_q_table;
	string real_str = "buisnessID buisnessName address city state zip stars reviewCount status";
	string* ptr_str = &real_str;
	cout << "Please enter buisness ID:" << endl;
	string BISID;
	cin >> BISID;
	buisness_q_table = yelpDatabase.query(ptr_str, 9, "buisnessTable", BISID  + "== buisnessName");
	Table* u_table;
	real_str = "reviews userName";
	ptr_str = &real_str;
	u_table = yelpDatabase.query(ptr_str, 2, "userTable", "buisnessName == reviewedBuisnesses");
	Table dummytable;
	Table* joined_table = dummytable.naturalJoin(buisness_q_table, u_table);

	//print_database_table(buisness_q_table);

	int business_information_options;
	
	do {
		system(CLEAR);
		// DO NOT MODIFY. IT LOOKS LIKE THIS DUE TO DOUBLE \\ CHARACTERS
		cout << endl;
		cout << " _______________________________________________________________________ \n";
		cout << "| --------------------------------------------------------------------- |\n";
		cout << "||                    ___     ___ _____ __     _____                   ||\n";
		cout << "||                    \\  \\  /  / |   _||  |   |     \\                  ||\n";
		cout << "||                     \\  \\/  /  |  |_ |  |   |  O  |                  ||\n";
		cout << "||                      \\    /   |   _||  |   |   __/                  ||\n";
		cout << "||                       |  |    |  |_ |  |__ |  |                     ||\n";
		cout << "||                       |__|    |____||_____||__|                     ||\n";
		cout << "||  ___      __     ________   __      ___       __      ______  _____ ||\n";
		cout << "|| |   \\    /  \\   |___   __| /  \\    |   \\     /  \\    |  ____||  __| ||\n";
		cout << "|| |    \\  /    \\     |  |   /    \\   | O /    /    \\   | |____ |  |_  ||\n";
		cout << "|| |    | /  __  \\    |  |  /  __  \\  |   \\   /  __  \\  |____  ||   _| ||\n";
		cout << "|| |    //  /  \\  \\   |  | /  /  \\  \\ | O  \\ /  /  \\  \\  ____| ||  |_  ||\n";
		cout << "|| |___//__/    \\__\\  |__|/__/    \\__\\|____//__/    \\__\\|______||____| ||\n";
		cout << "||_____________________________________________________________________||\n";
		cout << "||---------------------------------------------------------------------||\n";
		cout << "||               WHICH INFORMATION WOULD YOU LIKE TO VIEW?             ||\n";
		cout << "||---------------------------------------------------------------------||\n";
		cout << "||                                                                     ||\n";
		cout << "|| 1: NAME                                                             ||\n";
		cout << "|| 2: ADDRESS                                                          ||\n";
		cout << "|| 3: CITY                                                             ||\n";
		cout << "|| 4: STATE                                                            ||\n";
		cout << "|| 5: ZIP                                                              ||\n";
		cout << "|| 6: STARS                                                            ||\n";
		cout << "|| 7: REVIEW COUNT                                                     ||\n";
		cout << "|| 8: STATUS                                                           ||\n";
		cout << "|| 9: REVIEWS                                                          ||\n";
		cout << "|| 10: USERS THAT HAVE REVIEWED US                                     ||\n";
		cout << "|| 11: BACK                                                            ||\n";
		cout << "||_____________________________________________________________________||\n";
		cout << " ----------------------------------------------------------------------- \n";

		cin >> business_information_options;
		
		Table readtable;
		readtable = *joined_table;

		switch(business_information_options) {
			case 1:
				for (int i = 0; i < readtable.getSize();i++) {
					Record* ptrrec = readtable.getRecordList()[i];
					Record datarec = *ptrrec;
					//Output Name
					cout << datarec.listAttr()[2] << endl;
				}
				break;
			case 2:
				for (int i = 0; i < readtable.getSize();i++) {
					Record* ptrrec = readtable.getRecordList()[i];
					Record datarec = *ptrrec;
					//Output Address
					cout << datarec.listAttr()[3] << endl;
				}
				break;
			case 3:
				for (int i = 0; i < readtable.getSize();i++) {
					Record* ptrrec = readtable.getRecordList()[i];
					Record datarec = *ptrrec;
					//Output City
					cout << datarec.listAttr()[4] << endl;
				}
				break;
			case 4:
				for (int i = 0; i < readtable.getSize();i++) {
					Record* ptrrec = readtable.getRecordList()[i];
					Record datarec = *ptrrec;
					//Output State
					cout << datarec.listAttr()[5] << endl;
				}
				break;
			case 5:
				for (int i = 0; i < readtable.getSize();i++) {
					Record* ptrrec = readtable.getRecordList()[i];
					Record datarec = *ptrrec;
					//Output Zip
					cout << datarec.listAttr()[6] << endl;
				}
				break;
			case 6:
				for (int i = 0; i < readtable.getSize();i++) {
					Record* ptrrec = readtable.getRecordList()[i];
					Record datarec = *ptrrec;
					//Output Stars
					cout << datarec.listAttr()[7] << endl;
				}
				break;
			case 7:
				for (int i = 0; i < readtable.getSize();i++) {
					Record* ptrrec = readtable.getRecordList()[i];
					Record datarec = *ptrrec;
					//Output ReviewCount
					cout << datarec.listAttr()[8] << endl;
				}
				break;
			case 8:
				for (int i = 0; i < readtable.getSize();i++) {
					Record* ptrrec = readtable.getRecordList()[i];
					Record datarec = *ptrrec;
					//Output Status
					cout << datarec.listAttr()[9] << endl;
				}
				break;
			case 9:
				for (int i = 0; i < readtable.getSize();i++) {
					Record* ptrrec = readtable.getRecordList()[i];
					Record datarec = *ptrrec;
					//Output Reviews
					cout << datarec.listAttr()[10] << endl;
				}
				break;
			case 10:
				for (int i = 0; i < readtable.getSize();i++) {
					Record* ptrrec = readtable.getRecordList()[i];
					Record datarec = *ptrrec;
					//Output Users who reviewed
					cout << datarec.listAttr()[11] << endl;
				}
			case 11:
				break;
			default:
				break;
		}
		
	} while(business_information_options !=11);
}

int main() {
	
	int userLines;
	int businessLines;
	int tipLines;
	int options;
	
	cout << "\nBefore we get started... \n";
	cout << "Insert number of lines to read from user.json: ";
	cin >> userLines;
	cout << "Insert number of lines to read from business.json: ";
	cin >> businessLines;
	cout << "Insert number of lines to read from tip.json: ";
	cin >> tipLines;
	
	/* 	
	*	- WILL, DO JSON PARSING HERE!
	*	- ONCE THE OTHER TEAM SENDS US INSTRUCTIONS ON HOW TO CREATE A DATABASE,
	*	  THEN LETS CREAT THE DATABASE HERE! 
	*		- CALL THE DATABASE 'yelpDatabse' OR SOMETHING LIKE THAT... 
	*/
	/////////////////////////////////////////////////////
	//												/////
	//Code to extract data from business.json		/////
	//has businessID, name, neighborhood, addr, city, postal, stars,
	//review count, longitude, latitude, and if it is open
	/////////////////////////////////////////////////////
	string line;
	ifstream myFile("business.json");
	using json = nlohmann::json;
	vector<json> jsonList;
	json temp;
	vector<string> attributes;
	vector<string> data;
	int count = 0;
	//read json objects from business.json
	if (myFile.is_open()) {
		while (count < businessLines) {
			myFile >> temp;
			//cout << temp.at("name").get<string>() << endl; //for debugging, used to see which business have been read
			jsonList.push_back(temp);
			count++;
		}
		myFile.close();
	}
	//every attribute of a business listed at index i for each vector
	vector<string> businessIDs;
	vector<string> businessNames;
	vector<string> businessNeighborhoods;
	vector<string> businessAddresses;
	vector<string> businessCities;
	vector<string> businessStates;
	vector<string> businessPostals;
	vector<string> businessStars;
	vector<string> businessRevCount;
	vector<string> longitude;
	vector<string> latitude;
	vector<string> isOpen;
	//extract business data
	for (int i = 0; i < jsonList.size(); i++) {
		string businessID = jsonList.at(i).at("business_id").get<string>();
		for (int spaces = 0; spaces < businessID.size(); spaces++) {
			if (businessID.at(spaces) == ' ' || businessID.at(spaces) == '=' || businessID.at(spaces) == '<' || businessID.at(spaces) == '>'
				|| businessID.at(spaces) == '(' || businessID.at(spaces) == ')' || businessID.at(spaces) == '=')
				businessID.at(spaces) = '_';
		}
		if (businessID.at(0) == '~')
			businessID.at(0) = '-';
		businessIDs.push_back(businessID);
		string name = jsonList.at(i).at("name").get<string>();
		for (int spaces = 0; spaces < name.size(); spaces++) {
			if (name.at(spaces) == ' ' || name.at(spaces) == '=' || name.at(spaces) == '<' || name.at(spaces) == '>'
				|| name.at(spaces) == '(' || name.at(spaces) == ')' || name.at(spaces) == '=')
				name.at(spaces) = '_';
		}
		if (name.size() > 0 && name.at(0) == '~')
			name.at(0) = '-';
		businessNames.push_back(name);
		string neighborhood = jsonList.at(i).at("neighborhood").get<string>();
		for (int spaces = 0; spaces < neighborhood.size(); spaces++) {
			if (neighborhood.at(spaces) == ' ' || neighborhood.at(spaces) == '=' || neighborhood.at(spaces) == '<' || neighborhood.at(spaces) == '>'
				|| neighborhood.at(spaces) == '(' || neighborhood.at(spaces) == ')' || neighborhood.at(spaces) == '=')
				neighborhood.at(spaces) = '_';
		}
		if (neighborhood.size() > 0 && neighborhood.at(0) == '~')
			neighborhood.at(0) = '-';
		businessNeighborhoods.push_back(neighborhood);
		string address = jsonList.at(i).at("address").get<string>();
		for (int spaces = 0; spaces < address.size(); spaces++) {
			if (address.at(spaces) == ' ' || address.at(spaces) == '=' || address.at(spaces) == '<' || address.at(spaces) == '>'
				|| address.at(spaces) == '(' || address.at(spaces) == ')' || address.at(spaces) == '=')
				address.at(spaces) = '_';
		}
		if (address.size() > 0 && address.at(0) == '~')
			address.at(0) = '-';
		businessAddresses.push_back(address);
		string city = jsonList.at(i).at("city").get<string>();
		for (int spaces = 0; spaces < city.size(); spaces++) {
			if (city.at(spaces) == ' ' || city.at(spaces) == '=' || city.at(spaces) == '<' || city.at(spaces) == '>'
				|| city.at(spaces) == '(' || city.at(spaces) == ')' || city.at(spaces) == '=')
				city.at(spaces) = '_';
		}
		if (city.size() > 0 && city.at(0) == '~')
			city.at(0) = '-';
		businessCities.push_back(city);
		string _state = jsonList.at(i).at("state").get<string>();
		for (int spaces = 0; spaces < _state.size(); spaces++) {
			if (_state.at(spaces) == ' ' || _state.at(spaces) == '=' || _state.at(spaces) == '<' || _state.at(spaces) == '>'
				|| _state.at(spaces) == '(' || _state.at(spaces) == ')' || _state.at(spaces) == '=')
				_state.at(spaces) = '_';
		}
		if (_state.size() > 0 && _state.at(0) == '~')
			_state.at(0) = '-';
		businessStates.push_back(_state);
		string _postal = jsonList.at(i).at("postal_code").get<string>();
		for (int spaces = 0; spaces < _postal.size(); spaces++) {
			if (_postal.at(spaces) == ' ' || _postal.at(spaces) == '=' || _postal.at(spaces) == '<' || _postal.at(spaces) == '>'
				|| _postal.at(spaces) == '(' || _postal.at(spaces) == ')' || _postal.at(spaces) == '=')
				_postal.at(spaces) = '_';
		}
		if (_postal.size() > 0 && _postal.at(0) == '~')
			_postal.at(0) = '-';
		businessPostals.push_back(_postal);
		string _stars = to_string(jsonList.at(i).at("stars").get<int>());
		for (int spaces = 0; spaces < _stars.size(); spaces++) {
			if (_stars.at(spaces) == ' ' || _stars.at(spaces) == '=' || _stars.at(spaces) == '<' || _stars.at(spaces) == '>'
				|| _stars.at(spaces) == '(' || _stars.at(spaces) == ')' || _stars.at(spaces) == '=')
				_stars.at(spaces) = '_';
		}
		if (_stars.size() > 0 && _stars.at(0) == '~')
			_stars.at(0) = '-';
		businessStars.push_back(_stars);
		string _reviewCount = to_string(jsonList.at(i).at("review_count").get<int>());
		for (int spaces = 0; spaces < _reviewCount.size(); spaces++) {
			if (_reviewCount.at(spaces) == ' ' || _reviewCount.at(spaces) == '=' || _reviewCount.at(spaces) == '<' || _reviewCount.at(spaces) == '>'
				|| _reviewCount.at(spaces) == '(' || _reviewCount.at(spaces) == ')' || _reviewCount.at(spaces) == '=')
				_reviewCount.at(spaces) = '_';
		}
		if (_reviewCount.size() > 0 && _reviewCount.at(0) == '~')
			_reviewCount.at(0) = '-';
		businessRevCount.push_back(_reviewCount);
		latitude.push_back(to_string(jsonList.at(i).at("latitude").get<double>()));
		longitude.push_back(to_string(jsonList.at(i).at("longitude").get<double>()));
		isOpen.push_back(to_string(jsonList.at(i).at("is_open").get<int>()));
	}
	cout << endl;
	//output business data for debug
	for (int i = 0; i < jsonList.size(); i++) {
		cout << businessIDs.at(i) << " | ";
		cout << businessNames.at(i) << " | ";
		cout << businessNeighborhoods.at(i) << " | ";
		cout << businessCities.at(i) << " | ";
		cout << businessStates.at(i) << " | ";
		cout << businessPostals.at(i) << " | ";
		cout << businessStars.at(i) << " | ";
		cout << latitude.at(i) << ", " << longitude.at(i) << " | ";
		cout << isOpen.at(i) << " | ";
		cout << businessRevCount.at(i) << endl;
	}
	cout << endl;
	/////////////////////////////////////////////////////////////////
	//															
	//Code to extract data from user.json						
	//has userID, name, review count, date yelping since, and a list of userIDs of friends
	/////////////////////////////////////////////////////////////////
	vector<string> userIDs;
	vector<string> userNames;
	vector<string> userRevCount;
	vector<string> yelpingSince;
	vector<vector<string>> friendList;
	ifstream myFile1("user.json");
	vector<json> jsonList1;
	count = 0;
	//read json objects from user.json
	if (myFile1.is_open()) {
		while (count < userLines) {
			myFile1 >> temp;
			jsonList1.push_back(temp);
			count++;
		}
		myFile1.close();
	}
	//extract data
	for (int i = 0; i < jsonList1.size(); i++) {
		string user_id = jsonList1.at(i).at("user_id").get<string>();
		for (int spaces = 0; spaces < user_id.size(); spaces++) {
			if (user_id.at(spaces) == ' ' || user_id.at(spaces) == '=' || user_id.at(spaces) == '<' || user_id.at(spaces) == '>'
				|| user_id.at(spaces) == '(' || user_id.at(spaces) == ')' || user_id.at(spaces) == '=')
				user_id.at(spaces) = '_';
		}
		if (user_id.at(0) == '~')
			user_id.at(0) = '-';
		userIDs.push_back(user_id);
		string _name = jsonList1.at(i).at("name").get<string>();
		for (int spaces = 0; spaces < _name.size(); spaces++) {
			if (_name.at(spaces) == ' ' || _name.at(spaces) == '=' || _name.at(spaces) == '<' || _name.at(spaces) == '>'
				|| _name.at(spaces) == '(' || _name.at(spaces) == ')' || _name.at(spaces) == '=')
				_name.at(spaces) = '_';
		}
		if (_name.at(0) == '~')
			_name.at(0) = '-';
		userNames.push_back(_name);
		userRevCount.push_back(to_string(jsonList1.at(i).at("review_count").get<int>()));
		yelpingSince.push_back(jsonList1.at(i).at("yelping_since").get<string>());
		friendList.push_back(jsonList1.at(i).at("friends").get<vector<string>>());
	}
	//output data for debug
	for (int i = 0; i < jsonList1.size(); i++) {
		cout << userIDs.at(i) << " | ";
		cout << userNames.at(i) << " | ";
		cout << userRevCount.at(i) << " | ";
		//optional to print list of friends for each user
		/*for (int j = 0; j < friendList[i].size(); j++) {
		cout << friendList[i][j] << ", ";
		}
		cout << " | ";*/
		cout << yelpingSince.at(i) << endl;
	}
	//cout << jsonList1.at(0).at("friends").type_name() << endl;
	cout << endl;
	/////////////////////////////////////////////////////////////////
	//															
	//Code to extract data from tip.json						
	//has review tip(named "text"), date posted, likes, businessID, and userID who posted the tip
	/////////////////////////////////////////////////////////////////
	vector<json> jsonList2;
	vector<string> tips;
	vector<string> dates;
	vector<string> likes;
	vector<string> bizIDs;
	vector<string> users;
	ifstream myFile2("tip.json");
	count = 0;
	//read json objects from tip.json
	if (myFile2.is_open()) {
		while (count < tipLines) {
			myFile2 >> temp;
			jsonList2.push_back(temp);
			count++;
		}
		myFile2.close();
	}
	//extract data
	for (int i = 0; i < jsonList2.size(); i++) {
		string text = jsonList2.at(i).at("text").get<string>();
		for (int spaces = 0; spaces < text.size(); spaces++) {
			if (text.at(spaces) == ' ' || text.at(spaces) == '=' || text.at(spaces) == '<' || text.at(spaces) == '>'
				|| text.at(spaces) == '(' || text.at(spaces) == ')' || text.at(spaces) == '=')
				text.at(spaces) = '_';
		}
		if (text.size() > 0 && text.at(0) == '~')
			text.at(0) = '-';
		tips.push_back(text);
		dates.push_back(jsonList2.at(i).at("date").get<string>());
		likes.push_back(to_string(jsonList2.at(i).at("likes").get<int>()));
		string biz_ID = jsonList2.at(i).at("business_id").get<string>();
		for (int spaces = 0; spaces < biz_ID.size(); spaces++) {
			if (biz_ID.at(spaces) == ' ' || biz_ID.at(spaces) == '=' || biz_ID.at(spaces) == '<' || biz_ID.at(spaces) == '>'
				|| biz_ID.at(spaces) == '(' || biz_ID.at(spaces) == ')' || biz_ID.at(spaces) == '=')
				biz_ID.at(spaces) = '_';
		}
		if (biz_ID.at(0) == '~')
			biz_ID.at(0) = '-';
		bizIDs.push_back(biz_ID);
		string user_id = jsonList2.at(i).at("user_id").get<string>();
		for (int spaces = 0; spaces < user_id.size(); spaces++) {
			if (user_id.at(spaces) == ' ' || user_id.at(spaces) == '=' || user_id.at(spaces) == '<' || user_id.at(spaces) == '>'
				|| user_id.at(spaces) == '(' || user_id.at(spaces) == ')' || user_id.at(spaces) == '=')
				user_id.at(spaces) = '_';
		}
		if (user_id.at(0) == '~')
			user_id.at(0) = '-';
		users.push_back(user_id);
	}
	//output data for debug
	for (int i = 0; i < jsonList2.size(); i++) {
		cout << users.at(i) << " | ";
		cout << bizIDs.at(i) << " | ";
		cout << dates.at(i) << " | ";
		cout << tips.at(i) << " | ";
		cout << likes.at(i) << endl;
	}
	cout << endl;
	/*Creating yelpDatabase and its tables*/
	////////////////////////////////////////
	/*business table*/
	Database yelpDatabase;
	string* businessAttributes = new string[12];
	businessAttributes[0] = "ID";
	businessAttributes[1] = "Name";
	businessAttributes[2] = "Neighborhood";
	businessAttributes[3] = "Address";
	businessAttributes[4] = "City";
	businessAttributes[5] = "State";
	businessAttributes[6] = "Postal";
	businessAttributes[7] = "Stars";
	businessAttributes[8] = "Review_Count";
	businessAttributes[9] = "longitude";
	businessAttributes[10] = "latitude";
	businessAttributes[11] = "is_Open";
	Table businesses(businessAttributes, 12);
	for (int i = 0; i < jsonList.size(); i++) {
		Record business(businessAttributes, 12);
		businesses.insertRecord(&business);
		business.set("ID", businessIDs.at(i));
		business.set("Name", businessNames.at(i));
		business.set("Neighborhood", businessNeighborhoods.at(i));
		business.set("Address", businessAddresses.at(i));
		business.set("City", businessCities.at(i));
		business.set("State", businessStates.at(i));
		business.set("Postal", businessPostals.at(i));
		business.set("Stars", businessStars.at(i));
		business.set("Review_Count", businessRevCount.at(i));
		business.set("longitude", longitude.at(i));
		business.set("latitude", latitude.at(i));
		business.set("is_Open", isOpen.at(i));
	}
	//////////////////////////////////////
	/*users table*/
	//////////////////////////////////////
	string* userAttributes = new string[4];
	userAttributes[0] = "ID";
	userAttributes[1] = "Name";
	userAttributes[2] = "Review_Count";
	userAttributes[3] = "Yelping_Since";
	Table userTable(userAttributes, 4);
	for (int i = 0; i < jsonList1.size(); i++) {
		Record user(userAttributes, 4);
		userTable.insertRecord(&user);
		user.set("ID", userIDs.at(i));
		user.set("Name", userNames.at(i));
		user.set("Review_Count", userRevCount.at(i));
		user.set("Yelping_Since", yelpingSince.at(i));
	}
	///////////////////////////////////////
	/*tips table*/
	///////////////////////////////////////
	string* tipAttributes = new string[5];
	tipAttributes[0] = "Tip";
	tipAttributes[1] = "Date";
	tipAttributes[2] = "Likes";
	tipAttributes[3] = "BusinessID";
	tipAttributes[4] = "User";
	Table tipsTable(tipAttributes, 5);
	for (int i = 0; i < jsonList2.size(); i++) {
		Record tip(tipAttributes, 5);
		tipsTable.insertRecord(&tip);
		tip.set("Tip", tips.at(i));
		tip.set("Date", dates.at(i));
		tip.set("Likes", likes.at(i));
		tip.set("BusinessID", bizIDs.at(i));
		tip.set("User", users.at(i));
	}
	yelpDatabase.addTable(businesses, "Businesses");
	yelpDatabase.addTable(userTable, "Users");
	yelpDatabase.addTable(tipsTable, "Tips");
	string tableList = yelpDatabase.listTables();
	cout << tableList << endl;

	cout << "\n************************* WELCOME INTERFACE *****************************\n";
	// WE CAN EDIT THIS WELCOME INTERFACE IN THE FUTURE
	
	do {
		cout << "\nWHAT WOULD YOU LIKE TO DO? \n";
		cout << "\n1: DISPLAY NAMES AND ID NUMBER OF USERS";
		cout << "\n2: DISPLAY NAMES AND ID NUMBER OF BUSINESSES";
		cout << "\n3: LOOK UP USER INFORMATION";
		cout << "\n4: LOOK UP BUSINESS INFORMATION";
		cout << "\n5: QUIT\n";
		// WE CAN ADD MORE OPTIONS FOR THE EXTRA STUFF
		cin >> options;
		
		switch(options) {
			case 1:
				display_user_name_ID(yelpDatabase);
				break;
			case 2:
				display_business_name_ID(yelpDatabase);
				break;
			case 3:
				userInformation(yelpDatabase);
				break;
			case 4:
				businessInformation(yelpDatabase);
				break;
			case 5:
				break;
			default:
				break;
		}
		
	} while(options != 5);
	
	return 0;
}
