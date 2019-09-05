#pragma once
#include "Record.h"

/*	Table contains a map returning a vector of Records as opposed to just
records because a given key can have multiple records.
*/

class Table {
private:
	std::vector<std::string> attributeList;
	std::unordered_map<std::string, Record*> recordList;
	std::vector<Record*> fullRecordList;
	int size;
public:
	Table();
	Table(std::string* attributes, int sizeAttributes);
	~Table();
	void addAttribute(std::string attribute);
	void dropAttribute(std::string attribute);
	void insertRecord(Record* R);
	void makeKey(std::string attribute);
	Table* crossJoin(Table* t1, Table* t2);
	Table* naturalJoin(Table* t1, Table* t2);
	int count(std::string attribute);
	std::string max(std::string attribute);
	std::string min(std::string attribute);
	int getSize();
	std::vector<Record*> getRecordList();
	Record* getRecord(int rank);
	std::string getKey();
	std::vector<std::string> listAttributes();
};
