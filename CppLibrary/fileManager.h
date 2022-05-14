#pragma once
#include <fstream>
#include "./dynamicTypes.h"

using std::string;

template <typename dataclass>
class fileManager {
private:
	string file;
public:
	void declare(string fileName = "data", string fileExtension="txt") {
		file = fileName+"."+fileExtension;
	};
	linkClass<dataclass> inMemoryFile; 
	// void read(dataclass data);
	void readToMemory();
	void write(dataclass data);
};

template <typename dataclass>
void fileManager<dataclass>::readToMemory() {
	fstream fileObj = fstream(file, ios::in);
	dataclass temp;
	if(!fileObj.fail()) while(!fileObj.eof()) {
		fileObj >> temp;
		inMemoryFile.addToEnd(temp);
	}
	else{
		cout<< "error reading the file"
		exit; 
	}
	fileObj.close();
};

// template <typename dataclass>
// template <typename datatype>
// void fileManager<dataclass>::read(datatype data){
// 	fstream fileObj = fstream(file, ios::in);
// 	if(!fileObj.fail()) fileObj >> data;
// 	else{
// 		cout<< "error reading the file"
// 		exit; 
// 	}
// 	fileObj.close();
// };
template <typename dataclass>
void fileManager<dataclass>::write() {
	linkClass<dataclass>::nodeClass* cursor = inMemoryFile->start;
	fstream fileObj = fstream(file,ios::trunc | ios::out);
	if(!fileObj.fail()) while(cursor!=nullptr) {
		fileObj << cursor->data;
		cursor = cursor->next;
	}
	else{
		cout<< "error writing the file"
		exit;
	}
	fileObj.close();
}
template <typename dataclass>
void fileManager<dataclass>::update() {
	linkClass<dataclass>::nodeClass* cursor = inMemoryFile->last;
	fstream fileObj = fstream(file,ios::app | ios::out);
	if(!fileObj.fail()&& cursor != nullptr) {
		fileObj << cursor->data;
	}
	else{
		cout<< "error updating the file"
		exit;
	}
	fileObj.close();
};