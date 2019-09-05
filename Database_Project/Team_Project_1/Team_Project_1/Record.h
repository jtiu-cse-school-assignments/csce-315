#pragma once
#include <stack>
#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>

/*	Record is a vector of attributes, these attributes are stored
in the vector as a hash table for efficient reading and writing
to Record class.
*/



class Record {
private:
	std::vector<std::string> attributes;
	int size;
	std::unordered_map<std::string, std::string> dataHash;
public:
	Record();
	Record(std::string* data, int sizeData);
	~Record();
	int getSize();
	std::string getElem(std::string key);
	/*Invalid Characters:
	Cannot start with '~'
	Cannot include: ' ', '>', '<', '(', ')', '=' */
	void set(std::string column, std::string newData);
	void drop(std::string attr);
	std::vector<std::string> listAttr();
};
