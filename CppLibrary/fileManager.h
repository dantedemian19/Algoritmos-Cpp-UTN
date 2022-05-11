#pragma once
#include <fstream>

using std::string;

template <typename dataclass>
class fileManager<dataclass> {
private:
	string file;
	
public:
	dataclass read(string fileName);
	void write(dataclass data);
};

template <typename dataclass>
dataclass fileManager<dataclass>::read(string fileName) {
	file = fileName + ".txt";
	fstream fileObj = fstream(file, ios::in);

	
};