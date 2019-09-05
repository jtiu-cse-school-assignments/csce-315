#pragma once
#include "Table.h"
#include <list>

/*	This database utilizes multiple tables consisting of records,
of which is hashed based on the table names -> record -> attribute.
*/

class Database {
private:
	/* parser returns an array of pointers to records
	in the query based on the conditional operations*/
	struct parser {
		void parse(std::list<Record*> parse, std::vector<std::string> _operation);
		std::list<Record*> render();
		std::list<Record*> result;
		int depth;
		std::string* _select;

	} PARSER;
	std::vector<std::string> tableNames;
	std::unordered_map<std::string, Table*> hashTable;
	int size;
public:
	Database();
	~Database();
	void addTable(Table T, std::string name);
	void dropTable(std::string name);
	std::string listTables();
	Table* getTables();
	/* Query calls the parser struct to impliment search function */
	Table* query(std::string* select, int size, std::string from, std::string operation);
	int getSize();
};
