//#include "stdafx.h"
#include <stdio.h>
#include<io.h> //下面查找文件的功能需要用到
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string.h>


#include "fileKit.h"

using namespace std;

int getNewName(char *path, char* type, char* newName64);//64
int getFileNumAndLastName(char *path, char* type, char* lastName64);//64
int checkDB(char *path, char* type, int perUser);

int getFileNames(char* path, char* type, char** &files);

int myitoa5(int i, char *indexname5);
int myatoi(char* input);



int getFileNum(char *path, char* type)
{
    struct _finddata_t fa;
    long fHandle;
	
	char dstStr[64] = {0};
	memcpy(dstStr, path, strlen(path));
	strcat_s(dstStr, "*.");
	strcat_s(dstStr, type);
	//cout<<"Path: "<<dstStr<<endl; 

    int i = 0;
 
    if ((fHandle = _findfirst(dstStr, &fa)) == -1L)//这里可以改成需要的目录 
    {
        printf("当前目录下没有目标文件%s\n",type);
        return 0;
    }
    else
        do
        {
           
          //  cout << "ok.." << ++i << endl;
			i++;
             
    } while (_findnext(fHandle, &fa) == 0);
      
    _findclose(fHandle);
    return i;
}

bool getFileListAndNum(char* path, char* type, char** &fileList, int &fileNum)
{
	struct _finddata_t fa;
	long fHandle;

	char dstStr[64] = { 0 };
	memcpy(dstStr, path, strlen(path));
	strcat_s(dstStr, "*.");
	strcat_s(dstStr, type);
	//cout<<"Path: "<<dstStr<<endl; 
	int n = getFileNum(path, type);
	fileList = (char**)new char*[n];
	for (int i = 0; i < n; i++)
	{
		fileList[i] = new char[128];
		memset(fileList[i], 0, 128);
	}
	int i = 0;

	if ((fHandle = _findfirst(dstStr, &fa)) == -1L)//这里可以改成需要的目录 
	{
		printf("当前目录下没有目标文件%s\n", type);
		//return 0;
		goto nofile;
	}
	else
		do
		{

			memcpy(fileList[i], fa.name, strlen(fa.name));
			i++;

		} while (_findnext(fHandle, &fa) == 0);

	nofile:
		_findclose(fHandle);

		fileNum = i;

		return true;
}


int getFileNames(char* path,char* type, char** &files)
{
	int n = getFileNum(path, type);
	files = (char**)new char*[n];
	for (int i = 0; i < n; i++)
	{
		files[i] = (char*)new char[64];
		memset(files[i], 0, 64);
	}


	struct _finddata_t fa;
	long fHandle;

	char dstStr[64] = { 0 };
	memcpy(dstStr, path, strlen(path));
	strcat_s(dstStr, "*.");
	strcat_s(dstStr, type);
	//cout<<"Path: "<<dstStr<<endl; 

	int i = 0;

	if ((fHandle = _findfirst(dstStr, &fa)) == -1L)//这里可以改成需要的目录 
	{
		printf("当前目录下没有目标文件%s\n", type);
		return 0;
	}
	else
		do
		{
			memcpy(files[i], fa.name, strlen(fa.name));
			//  cout << "ok.." << ++i << endl;
			i++;

		} while (_findnext(fHandle, &fa) == 0);

		_findclose(fHandle);
		return i;
}
int getNewName(char *path, char* type, char* newName64)//64
{
	struct _finddata_t fa;
	long fHandle;

	char dstStr[64] = { 0 };
	memcpy(dstStr, path, strlen(path));
	strcat_s(dstStr, "*.");
	strcat_s(dstStr, type);
	//cout<<"Path: "<<dstStr<<endl; 

	int i = 0;
	char lastName[64] = { 0 };
	char curName[64] = { 0 };
	if ((fHandle = _findfirst(dstStr, &fa)) == -1L)//这里可以改成需要的目录 
	{
		printf("当前目录下没有目标文件%s\n", type);
		//return 0;
		goto nofiles;
	}
	else
		do
		{
			if (i != 0)
			{
				memcpy(curName, fa.name, 4);
				//lastName[4] = 0;
				if (strcmp(lastName, curName))
					memcpy(lastName, fa.name, 4);
			}
			else
			{
				memcpy(lastName, fa.name, 4);
			}
			//  cout << "ok.." << ++i << endl;
			i++;

		} while (_findnext(fHandle, &fa) == 0);
nofiles:
		_findclose(fHandle);
		// I REAL FILEN NUM
		memset(newName64, 0, 64);
		memset(lastName + 4, 0, 60);

		int lastIndex = 0;
		if (i>0)
			lastIndex = atoi(lastName);
		int newIndex =  lastIndex + 1;
		newName64[3] = newIndex % 10 + 48;
		newName64[2] = newIndex / 10 % 10 + 48;
		newName64[1] = newIndex / 100 % 10 + 48;
		newName64[0] = newIndex / 1000 % 10 + 48;
		return i;
}
int myitoa5(int i,char *indexname5)
{
	memset(indexname5, 0, 5);
	indexname5[3] = i % 10 + 48;
	indexname5[2] = i / 10 % 10 + 48;
	indexname5[1] = i / 100 % 10 + 48;
	indexname5[0] = i / 1000 % 10 + 48;
	return 0;
}
int myatoi(char* input)
{
	return atoi(input);
}
int getFileNumAndLastName(char *path, char* type, char* lastName64)//64
{
	struct _finddata_t fa;
	long fHandle;

	char dstStr[64] = { 0 };
	memcpy(dstStr, path, strlen(path));
	strcat_s(dstStr, "*.");
	strcat_s(dstStr, type);
	//cout<<"Path: "<<dstStr<<endl; 

	int i = 0;
	char lastName[64] = "no user!";
	//char curName[64] = { 0 };
	if ((fHandle = _findfirst(dstStr, &fa)) == -1L)//这里可以改成需要的目录 
	{
		printf("当前目录下没有目标文件%s\n", type);
		//return 0;
		goto nofile;
	}
	else
		do
		{

			if (strcmp(lastName, fa.name))
				memcpy(lastName, fa.name,strlen(fa.name));
			i++;

		} while (_findnext(fHandle, &fa) == 0);
nofile:
		_findclose(fHandle);

		// I REAL FILEN NUM
		if (i)
			memcpy(lastName64, lastName, 9);
		else
			memcpy(lastName64, "0000", 4);
		
		return i;
}




