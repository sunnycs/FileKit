#pragma once
#pragma execution_character_set("utf-8")

#include <iostream>
#include "fileKit.h"

using namespace std;
char* path = "d:/imgs/";

int main()
{
	int fN = 0;
	char** fileNames = NULL;//store files' names
	bool ret = getFileListAndNum(path, "bmp", fileNames, fN);
	if (!ret)
	{
		cout << "file detection error" << endl;
		return -1;
	}
	for (int i = 0; i < fN; i++)
	{
		cout << fileNames[i] << endl;
	}
	return 0;
}
