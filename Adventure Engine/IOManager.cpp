#include "IOManager.h"

#include <fstream>

bool IOManager::readFileToBuffer(string filePath, vector<unsigned char>& buffer)
{
	ifstream file(filePath, ios::binary);
	if (file.fail())
	{
		perror(filePath.c_str());
		return false;
	}

	//seek to end
	file.seekg(0, ios::end);

	//get the file size
	int fileSize = file.tellg();
	file.seekg(0, ios::beg);

	//reduce file size by any header precent
	fileSize -= file.tellg();

	//set buffer size
	buffer.resize(fileSize);
	file.read((char* )&(buffer[0]), fileSize);
	file.close();

	return true;
}
