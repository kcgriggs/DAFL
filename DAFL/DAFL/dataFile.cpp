#include "dafl.h"
const int HEADSIZE = 4;
void dataFile::createFile(char* fn, unsigned int n)
{
	finOut.open(fn, ios::out);	
	if (finOut.is_open())
	{
		recCount = 0;
		recSize = n;
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
	finOut.open(fn, ios::in | ios::out);
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
	finOut.seekg(0);
	finOut.write((char*)& recSize, sizeof recSize);
	finOut.write((char*)& recCount, sizeof recCount);
	finOut.close();
}

void dataFile::putRecord(int k, const void* r)
{
	int writePosition = 0;
	if (k >= 1)
	{
		int writePosition = ((k - 1) * recSize) + HEADSIZE;
	}
	if (k >= 0 && k <= recCount)
	{
		finOut.seekg(writePosition);
		finOut.write((char*)r, recSize);
		fs = fsSuccess;
	}
	else
	{
		fs = fsPutFail;
	}
	
}

void dataFile::getRecord(int k, const void* r)
{
	int readPosition = 0;
	if (k >= 1)
	{
		int writePosition = ((k - 1) * recSize) + HEADSIZE;
	}
	if (k >= 0 && k <= recCount)
	{
		finOut.seekg(readPosition);
		finOut.write((char*)r, recSize);
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
	finOut.seekg(sizeof recSize);
	finOut.write((char*)& recCount, sizeof recCount);
}

int dataFile::fileStatus()
{
	return fs;
}