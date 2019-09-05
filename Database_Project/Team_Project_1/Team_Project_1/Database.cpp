#include "Database.h"
#include <iostream>
#include <list>
using namespace std;

class BAD_INPUT {};

extern bool isNumeric(string input);

//The most general checking for operators. If it matches any of the comparators, AND-OR-NOT return true
bool isOp(string str) {
	return str == "=" || str == "<>" || str == ">" || str == "<" || str == ">=" || str == "<=" || str == "NOT" || str == "AND" || str == "OR";
}
//This checks for the specific comparators, not including AND-OR-NOT
bool isOp2(string token) {
	return (token == "=" || token == ">" || token == "<" || token == ">=" || token == "<=" || token == "<>");
}
//This checks for the foundations of the comparators. These 3 symbols are used in all of them
bool isOp3(char str) {
	return (str == '=' || str == '>' || str == '<');
}
//Evaluate the comparison operation between two strings
bool evalOp(string in1, string in2, string op) {

	bool n1 = isNumeric(in1);
	bool n2 = isNumeric(in2);
	//cannot compare Numeric-String, so I used exclusive or
	if (n1 ^ n2) throw BAD_INPUT();
	//already determined both are either numeric or not
	if (n1) {
		//parse strings into floats and perform the comparisons
		double In1 = stof(in1);
		double In2 = stof(in2);

		if (op == "=") return (In1 == In2);
		else if (op == "<") return (In1 < In2);
		else if (op == ">") return (In1 > In2);
		else if (op == "<=") return (In1 <= In2);
		else if (op == ">=") return (In1 >= In2);
		else if (op == "<>") return (In1 != In2);
	}
	else {
		//perform comparisons as regular strings
		if (op == "=") return (in1 == in2);
		else if (op == "<") return (in1 < in2);
		else if (op == ">") return (in1 > in2);
		else if (op == "<=") return (in1 <= in2);
		else if (op == ">=") return (in1 >= in2);
		else if (op == "<>") return (in1 != in2);
	}
}
//Perform AND or OR operation
bool evalAndOr(bool in1, bool in2, string op) {
	if (op == "AND") return (in1 && in2);
	else if (op == "OR") return (in1 || in2);
}
//Perform NOT operation
bool evalNot(bool in, string op) {
	return (!in);
}
/*	Parse is given list of records and the operation in Reverse Polish Notation.
From there it evaluates the boolean expression and eliminates the records that return false from the list
Finally it places that final list into 'result'
*/
void Database::parser::parse(list<Record*> listR, vector<string> output) {

	for (int i = 0; i < listR.size(); ++i) {
		//stack of general strings for comparison
		stack<string> vals;
		//stack of booleans used for AND-OR-NOT
		stack<bool> bools;
		//gets our record to use
		Record* record = listR.front();
		listR.pop_front();

		for (int i = 0; i < output.size(); ++i) {
			//indicates a comparison operator
			if (isOp2(output[i])) {
				//can't compare less than two values
				if (vals.size() < 2) throw BAD_INPUT();
				//pushed in order, popped backwards
				string in2 = vals.top();
				vals.pop();
				string in1 = vals.top();
				vals.pop();
				//evaluate the expressions and push resutant boolean onto stack
				bool result = evalOp(in1, in2, output[i]);
				bools.push(result);
			}
			//Evaluate AND-OR on two top boolean values
			else if (output[i] == "AND" || output[i] == "OR") {
				//Can't evaluate AND-OR with less than one value
				if (bools.size() < 2) throw BAD_INPUT();
				bool in2 = bools.top();
				bools.pop();
				bool in1 = bools.top();
				bools.pop();
				//push new result onto stack
				bool result = evalAndOr(in1, in2, output[i]);
				bools.push(result);
			}
			//Evaluate NOT on top boolean value
			else if (output[i] == "NOT") {
				//must have at least on boolean value to NOT
				if (bools.size() < 1) throw BAD_INPUT();
				bool in = bools.top();
				bools.pop();
				bool result = evalNot(in, output[i]);
				bools.push(result);
			}
			//Not an operator of any kind. Just a value used for comparisons
			else {
				string token = output[i];
				//Indicates that it's from array select, use record value at that attribute
				if (token[0] == '~') {
					string tokenName = token.substr(1, token.size() - 1);
					//overwrite token with value from record
					token = record->getElem(tokenName);
				}
				//only time that values get added to vals stack
				vals.push(token);
			}
		}
		//indicates an incomplete operation passed by user
		if (bools.size() != 1 || vals.size() != 0) {
			throw BAD_INPUT();
		}
		//if true, return the record to the end of the list, otherwise leave it out
		if (bools.top() == 1) {
			listR.emplace_back(record);
		}
	}
	//we now have a result
	result = listR;
	return;
}

//Only returns result, could be an empty list
list<Record*> Database::parser::render() {
	return result;
}
//Initialize size to 0, everything else starts blank
Database::Database() {
	size = 0;
}
//Iterate throgh all tables in database and delete the pointers to them
Database::~Database() {
	for (int i = 0; i < tableNames.size(); ++i) {
		string table = tableNames[i];
		delete hashTable[table];
	}
}
//Add table to Database. Can overwrite existing table of same name
void Database::addTable(Table T, std::string name) {
	bool found = false;
	int index = 0;
	//if the table name doesn't exist yet in the database, add it to the list of names
	while (!found && index < size) {
		if (tableNames[index] == name) found = true;
		else index++;
	}
	if (!found) {
		tableNames.push_back(name);
	}
	//insert a pointer to the table into the database
	Table* addedTable = new Table;
	*(addedTable) = T;
	hashTable[name] = addedTable;
	size++;
	return;
}
//Drop table from database
void Database::dropTable(std::string name) {
	//Erase name from list of names and erase pointer to table from the map
	for (int i = 0; i < size; ++i) {
		if (tableNames[i] == name) {
			tableNames.erase(tableNames.begin() + i);
			size--;
		}
	}
	hashTable.erase(name);
	return;
}
//Output a string of all table names separated by commas
string Database::listTables() {
	string names;
	for (int i = 0; i < tableNames.size(); i++) {
		names += tableNames[i] + ", ";
	}
	names = names.substr(0, names.size() - 3);
	return names;
}
//Output an array of pointers to all tables in the database
Table* Database::getTables() {
	Table* allTables = new Table[size];
	for (int i = 0; i < size; ++i) {
		string name = tableNames[i];
		allTables[i] = *(hashTable[name]);
	}
	return allTables;
}
//Set the precedence of each operator for shunting yard
void initPrec(unordered_map<string, int> &prec) {
	prec["="] = 4;
	prec["<>"] = 4;
	prec[">"] = 4;
	prec["<"] = 4;
	prec[">="] = 4;
	prec["<="] = 4;
	prec["NOT"] = 3;
	prec["AND"] = 2;
	prec["OR"] = 1;
	prec[" "] = -1;
	prec["("] = 0;
	return;
}
//Return a new table with all records that match the operation
Table* Database::query(std::string* select, int size, std::string from, std::string operation) {
	try {
		//Set the operator precedences
		unordered_map<string, int> prec;
		initPrec(prec);
		//used to split up different 'tokens' from 'operation', initial size 1
		vector<string> tokens(1);
		//output of the shunting yard algorithm
		vector<string> output;
		//operators stack used in algorithm, space will serve as base of the stack
		stack<string> operators;
		operators.push(" ");

		//charIndex goes through the 'operation' string
		int charIndex = 0;
		//wordIndex goes through 'tokens' vector
		int wordIndex = 0;

		//Indicates a normal character, for instance 'A', is an acceptable char for current 'word'
		bool l4Char = 1;
		//Indicates an operator character, for instance '<', is an acceptable char for current 'word'
		bool l4Op = 1;

		//ignore all leading whitespace
		while (operation[charIndex] == ' ') {
			charIndex++;
		}
		//iterate through each remaining character of the string
		for (charIndex; charIndex < operation.length(); charIndex++) {
			char chr = operation[charIndex];
			//if its a space, continue until next char is not a space
			if (operation[charIndex] == ' ') {
				while (operation[charIndex] == ' ' && charIndex < operation.length()) {
					charIndex++;
				}
				charIndex--;
				//both types of characters are acceptable now, start a new word
				l4Char = 1;
				l4Op = 1;
				tokens.push_back("");
				wordIndex++;
			}
			else if (operation[charIndex] == ')' || operation[charIndex] == '(') {
				//indicates that current word is not looking for one or the other, start a new word
				if (!l4Char || !l4Op) {
					tokens.push_back("");
					wordIndex++;
				}
				//add parenthesis to new word, not looking for either type in current word now
				tokens[wordIndex] += operation[charIndex];
				l4Char = 0;
				l4Op = 0;
			}
			//it is an operator character
			else if (isOp3(operation[charIndex])) {
				//if not currently looking for operator character, start a new word
				if (!l4Op) {
					tokens.push_back("");
					wordIndex++;
				}
				//now only looking for operator characters
				l4Op = 1;
				l4Char = 0;
				tokens[wordIndex] += operation[charIndex];
			}
			else {
				//start a new word
				if (!l4Char) {
					tokens.push_back("");
					wordIndex++;
				}
				//only want normal characters
				l4Op = 0;
				l4Char = 1;
				tokens[wordIndex] += operation[charIndex];
			}
		}
		//if one of the 'tokens' is in select, add '~' to front to indicate that we want an attribute value, used later
		for (int i = 0; i < tokens.size(); ++i) {
			//token cannot initially start with a '~' in front
			if ((tokens[i])[0] == '~') throw BAD_INPUT();
			for (int j = 0; j < size; ++j) {
				if (tokens[i] == select[j]) {
					tokens[i] = "~" + tokens[i];
				}
			}
		}

		//Looks for closing parenthesis, value indicates how many are left to look for
		int looking4par = 0;
		//The Shunting Yard Algorithm
		for (int i = 0; i < tokens.size(); ++i) {
			//'character' just denotes an index of tokens, it's really a full string, not necessarily a char
			string character = tokens[i];
			//if it's an operator, throw in onto operators stack
			if (isOp(character)) {
				//pop off all operators of higher precedence and push onto output vector
				while (operators.size() > 1 && prec[character] < prec[operators.top()]) {
					output.push_back(operators.top());
					operators.pop();
				}
				operators.push(character);
			}
			//we need another close parenthesis now
			else if (character == "(") {
				operators.push("(");
				looking4par++;
			}
			//found a close
			else if (character == ")") {
				//can't close if not open
				if (!looking4par) {
					throw BAD_INPUT();
				}
				//pop off everything from stack until the open is found
				while (operators.top() != "(") {
					output.push_back(operators.top());
					operators.pop();
				}
				operators.pop();
				looking4par -= 1;
			}
			//not an operator, just push the string onto the output stack
			else {
				output.push_back(character);
			}
		}
		//reached the end of tokens, pop off everything until the end
		while (operators.top() != " ") {
			//mismatched parenthesis, error
			if (operators.top() == ")" || operators.top() == "(") throw BAD_INPUT();
			output.push_back(operators.top());
			operators.pop();
		}

		//Table specified in function argument, get list of tables from it
		Table* table = hashTable[from];
		vector<Record*> vecR = table->getRecordList();
		list<Record*> listR;

		for (int i = 0; i < vecR.size(); ++i) {
			listR.push_back(vecR[i]);
		}

		//evaluate reverse polish notation
		PARSER.parse(listR, output);

		//this is a list of all records that passed to operation expression
		list<Record*> finalList = PARSER.render();
		int sizeFinal = finalList.size();

		//Create a new table with all of the records
		vector<string> attrVec = table->listAttributes();
		string* attrArr = new string[attrVec.size()];
		for (int i = 0; i < attrVec.size(); ++i) {
			attrArr[i] = attrVec[i];
		}

		Table* newTable = new Table(attrArr, attrVec.size());
		for (int i = 0; i < sizeFinal; ++i) {
			//we want a deep copy, pointers to same record independent of each other
			Record* record = new Record;
			*record = *(finalList.front());
			finalList.pop_front();
			newTable->insertRecord(record);
		}

		return newTable;
	}
	catch (BAD_INPUT) {
		cout << "\n\n\n***INVALID EXPRESSION***\n\n\n";
		return NULL;
	}
}
//return size
int Database::getSize() {
	return size;
}