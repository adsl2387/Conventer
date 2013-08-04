// ReadC++Code.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <string>


using namespace std;
#define MAX_BUFFER_SIZE  128


string ReadLine(FILE* file, long offset = 0, int fromWhere = SEEK_CUR);

int getIndex(string s)
{
	if (s.find("mile")!= -1)
	{
		return 0;
	}
	else if (s.find("yard")!= -1)
	{
		return 1;
	}
	else if (s.find("inch")!= -1)
	{
		return 2;
	}
	else if (s.find("foot") != -1 || s.find("feet") != -1)
	{
		return 3;
	}
	else if (s.find("fath") != -1)
	{
		return 4;
	}
	else if (s.find("furlong") != -1)
	{
		return 5;
	}
	else
	{
		return -1;
	}
}


void Complete(string filename)
{

	FILE* fIn = NULL;
	FILE* fOut = NULL;
	double conveter[6] = {0};
	fIn = fopen("in.txt", "rb");
	fOut = fopen("out.txt", "wb");
	char* email = "313124800@qq.com\r\n\r\n";
	fwrite(email, sizeof(char), strlen(email), fOut);
	string line = ReadLine(fIn, 0);
	while(line.length() > 2)
	{
		int fir = line.find(' ');
		int sec = line.find(' ', fir + 1);
		if (fir == -1 || sec == -1)
		{
			line = ReadLine(fIn, 0);
			continue;
		}
		string str = line.substr(fir+1, sec - fir - 1);
		double dNum = 1;
		//sscanf(line.substr(0, fir).c_str(), "%f", &dNum);
		dNum = atof(line.substr(0, fir).c_str());
		fir = line.find(' ', sec + 1);
		sec = line.find(' ', fir + 1);
		if (fir == -1 || sec == -1)
		{
			line = ReadLine(fIn, 0);
			continue;
		}
		double dLength = 0;
		dLength = atof(line.substr(fir + 1, sec - fir - 1).c_str());
		//sscanf(tmp.c_str(), "%f", &dLength);
		int index = getIndex(str);
		if (index == -1)
		{
			line = ReadLine(fIn, 0);
			continue;
		}
		conveter[index] = dLength / dNum;
		line = ReadLine(fIn, 0);
	}
	line = ReadLine(fIn, 0);
	while(line.length() > 2)
	{
		double dNume = 0;
		int fir = -1;
		int sec = -1;
		int mid = 0;
		double dSum = 0;
		char cOper = '+';
		while(1)
		{
			fir = line.find(' ', mid);
			sec = line.find(' ', fir + 1);
			if (fir == -1)
			{
				break;
			}
			if (sec == -1)
			{
				sec = line.length();
			}
			int index = getIndex(line.substr(fir + 1, sec - fir - 1));
			//sscanf(line.substr(mid, fir - mid).c_str(), "%f", &dNume);
			dNume = atof(line.substr(mid, fir - mid).c_str());
			if (cOper == '+')
			{
				dSum += dNume * conveter[index];
			}
			else if (cOper == '-')
			{
				dSum -=  dNume * conveter[index];
			}
			else
			{
				break;
			}
			if (sec < line.length() - 2)
			{
				cOper = line[++sec];
				mid = sec + 2;
			}
			else
			{
				break;
			}
		}
		char buffer[50] = {0};
		sprintf(buffer, "%.2f m\r\n",  dSum);
		fwrite(buffer,  sizeof(char), strlen(buffer),fOut);
		line = ReadLine(fIn);
	}

	fclose(fIn);
	fclose(fOut);
}



int _tmain(int argc, _TCHAR* argv[])
{
	Complete("in.txt");

	printf("执行完成\n");

	return 0;
}

string ReadLine(FILE* file, long offset, int fromWhere )
{
	char buffer[MAX_BUFFER_SIZE] = {0};
	size_t bytesRead = 0;
	string value;
	fseek(file, offset, fromWhere);
	bool stop = false;
	while(1)
	{

		memset(buffer, 0, MAX_BUFFER_SIZE);
	
		bytesRead = fread(buffer, sizeof(char), MAX_BUFFER_SIZE, file);
		if (bytesRead == 0)
		{
			break;
		}
		size_t i = 0;
		for (i = 0;i < bytesRead; i++)
		{
			value.push_back(buffer[i]);
			if (buffer[i] == '\n')
			{
				stop = true;
				break;
			}
			
		}
		
		if (stop)
		{
			long offsee = i + 1- bytesRead;
			fseek(file, offsee, SEEK_CUR);
			break;
		}
	}

	return value;
}
