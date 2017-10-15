#include "IOManager.h"
#include <fstream>

namespace Xenro {
bool IOManager::readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer) {
	//read in exact contents of file as binary
	std::ifstream file(filePath, std::ios::binary);

	if (file.fail()) {
		perror(filePath.c_str());
		return false;
	}

	//seek to the end.
	file.seekg(0, std::ios::end);

	//Get the file size.
	int fileSize = file.tellg();

	//seek to beginning.
	file.seekg(0, std::ios::beg);

	//reduce file size by any header bytes that might be present.
	fileSize -= file.tellg();

	buffer.resize(fileSize);
	file.read((char*)&(buffer[0]), fileSize); //needs a char* so cast it as one.

	file.close();
	return true;
	}

bool IOManager::readFileToBuffer(std::string filePath, std::string& buffer) {

	//read in exact contents of file as binary
	std::ifstream file(filePath, std::ios::binary);

	if (file.fail()) {
		perror(filePath.c_str());
		return false;
	}

	//seek to the end.
	file.seekg(0, std::ios::end);

	//Get the file size.
	unsigned int fileSize = (unsigned int)file.tellg();

	//seek to beginning.
	file.seekg(0, std::ios::beg);

	//reduce file size by any header bytes that might be present.
	fileSize -= (unsigned int)file.tellg();

	buffer.resize(fileSize);
	file.read((char*)&(buffer[0]), fileSize); //needs a char* so cast it as one.

	file.close();
	return true;
}
}