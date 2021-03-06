/*************************************************************************/
/*                           IOManager.cpp                               */
/*************************************************************************/
/*                       This file is part of:                           */
/*                           Xenro Engine                                */
/*             https://github.com/Jmiller7023/Xenro-Engine               */
/*************************************************************************/
/*                 Copyright  11-3-2017 Joseph Miller.                   */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/

#include "IOManager.h"
#include <fstream>
#include <filesystem>

// Namespace alias
namespace fs = std::experimental::filesystem;

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
	std::streamoff fileSize = file.tellg();

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

bool IOManager::getDirectoryEntries(const char* path, std::vector<DirEntry>& rvEntries) {

	auto dpath = fs::path(path);
	// Must be directory
	if (!fs::is_directory(dpath)) return false;

	for (auto it = fs::directory_iterator(dpath); it != fs::directory_iterator(); ++it) {
		rvEntries.emplace_back();
		rvEntries.back().path = it->path().string();
		if (is_directory(it->path())) {
			rvEntries.back().isDirectory = true;
		}
		else {
			rvEntries.back().isDirectory = false;
		}
	}
	return true;
}

bool IOManager::makeDirectory(const char* path) {
	return fs::create_directory(fs::path(path));
}
}