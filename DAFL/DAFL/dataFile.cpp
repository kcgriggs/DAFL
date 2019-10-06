#include "dafl.h"

void dataFile::createFile(char* fn, unsigned int n)
{
	finOut.clear();
	finOut.open(fn, ios::out);	
	if (finOut.is_open())
	{
		finOut.seekg(0);
		recCount = 0;
		recSize = n;
		headSize = sizeof recCount + sizeof recSize;
		finOut.write((char*)& recSize, sizeof recSize);
		finOut.write((char*)& recCount, sizeof recCount);
		finOut.close();
		fs = fsSuccess;
	}
	else
	{
		fs = fsCreateFail;
	}
}

void dataFile::openFile(char* fn)
{
	finOut.open(fn, ios::in | ios::out | ios::binary | ios::app);
	if (finOut.is_open())
	{
		fs = fsSuccess;
	}
	else
	{
		fs = fsOpenFail;
	}
}

void dataFile::closeFile()
{
	finOut.seekp(0, ios::beg);
	finOut.write((char*)& recSize, sizeof recSize);
	finOut.write((char*)& recCount, sizeof recCount);
	finOut.close();
}

void dataFile::putRecord(int k, const void* r)
{
	finOut.clear();
	int writePosition = headSize + (recSize * k);
	finOut.seekg(writePosition, ios::beg);
	if (finOut.write(reinterpret_cast<const char*>(&r), recSize))
	{
		fs = fsSuccess;
	}
	else
	{
		fs = fsPutFail;
	}
}

void dataFile::getRecord(int k, const void* r)
{
	finOut.clear();
	int readPosition = headSize + (recSize * k);
	finOut.seekg(readPosition);
	if (finOut.write(reinterpret_cast<const char*>(r), recSize))
	{
		fs = fsSuccess;
	}
	else
	{
		fs = fsGetFail;
	}
}

int dataFile::recordCount()
{
	return recCount;
}

void dataFile::updateRecordCount(int n)
{
	recCount += n;
}

int dataFile::fileStatus()
{
	return fs;
}