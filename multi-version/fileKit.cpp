#ifdef _WIN32
//#include "stdafx.h"
#include <stdio.h>
#include<io.h> //traverse floder
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

/*
param:path, the input path(including the final '/')
param:type, image type, exclude '.'
param:fileList, the list of image names, just image names
return: file num
*/
int getFileListAndNum(char* path, char* type, char** &fileList)
{
	struct _finddata_t fa;
	long fHandle;

	char dstStr[64] = { 0 };
	memcpy(dstStr, path, strlen(path));
	strcat_s(dstStr, "*.");
	strcat_s(dstStr, type);
	//cout<<"Path: "<<dstStr<<endl; 
	int n = getFileNum(path, type);
	if (n <= 0) { cout << "get files number error!" << endl; return n; }

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
		

		return n;
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

#endif

#ifdef linux
#include <stdio.h>
//#include<io.h> //windows fileKit
//#include <opencv2/opencv.hpp>
#include <iostream>
#include <string.h>
#include <algorithm>
#include <dirent.h>//Linux?
#include <vector>
#include <sstream>

#include "fileKit.h"

using namespace std;

int getFileListAndNum(char* path, char** &fileList)
{
	int fileNum = 0;
	// DIR* dirp = opendir(path.c_str());
	DIR* dirp = opendir(path);
	if (!dirp)
	{
		return -1;
	}

	struct dirent *dir;
	vector<std::string> file_name;
	while ((dir = readdir(dirp)) != NULL)
	{
		if (strcmp(dir->d_name, ".") == 0 ||
			strcmp(dir->d_name, "..") == 0)
		{
			continue;
		}
		string name = dir->d_name;
		{
			file_name.push_back(name);
			fileNum++;
		}
	}

	closedir(dirp);

	if (fileNum == 0)
	{
		return 0;
	}
	fileList = (char**)new char*[fileNum];
	for (int i = 0; i<fileNum; i++)
	{
		fileList[i] = new char[128];
		memset(fileList[i], 0, 128);
	}

	sort(file_name.begin(), file_name.end());
	//sort(dir_name.begin(),dir_name.end());

	std::stringstream ss_ret;
	int count = 0;

	for (vector<string>::const_iterator i = file_name.begin(); i != file_name.end(); i++)
	{
		memcpy(fileList[count], i->c_str(), i->length());
		count++;
	}

	//    for (int i=0; i<fileNum; i++)
	//    {
	//        cout<<fileList[i]<<endl;
	//    }


	return fileNum;
}

int getFileNum(char *path)
{
	int i = 0;
	DIR* dirp = opendir(path);
	if (!dirp)
	{
		cout << "open dir failed!" << endl;
		return -1;
	}

	struct dirent *dir;

	while ((dir = readdir(dirp)) != NULL)
	{
		if (strcmp(dir->d_name, ".") == 0 ||
			strcmp(dir->d_name, "..") == 0)
		{
			continue;
		}

		{
			i++;
		}
	}

	closedir(dirp);

	return i;
}














/*
//if ret>0,DB is ok; else if ret<0 DB fail; ret ==0 initial floder
int checkDB(char *path,   int perUser)
{
int fileNum;
char** fileList;
int ret = getFileListAndNum( path, fileList, fileNum);std::cout<<"sdfafdadf:"<<ret<<std::endl;
if (ret==false)  return -5;
int i = 0;

int count = 0;
int erroFlag = false;
char lastName[64]={0};
char curName[64]={0};
for ( i=0; i<fileNum; i++)
{

if (i != 0)
{
memcpy(curName, fileList[i], 4);

if (strcmp(lastName, curName))
{

memcpy(lastName, fileList[i], 4);
if (count < perUser)
{
erroFlag = true;
goto nofile;
}

count = 1;
}
else
{

count++;
}


}
else
{
memcpy(lastName,  fileList[i], 4);
count++;
}

}
nofile:

if (fileNum)
{
for (int i=0; i<fileNum; i++)
delete []fileList[i];
delete []fileList;
}


if (i == 0)
{
return 0;
}
else if (erroFlag)
{
return -1;
}
else if (count<perUser)
return -2;

else
return i;

}
int getNewName(char *path,  char* newName64)//64
{
int fileNum;
char** fileList;
int ret = getFileListAndNum( path, fileList, fileNum);
if (ret==false)
{
memset(newName64, 0, 64);
return ret;
}

char lastName[64]={0};
char curName[64]={0};
int i=0;
for ( i=0; i<fileNum; i++)
{

if (i != 0)
{
memcpy(curName, fileList[i], 4);
//lastName[4] = 0;
if (strcmp(lastName, curName))
memcpy(lastName, fileList[i], 4);
}
else
{
memcpy(lastName, fileList[0], 4);
}
//  cout << "ok.." << ++i << endl;


}


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

if (fileNum)
{
for (int i=0; i<fileNum; i++)
delete []fileList[i];
delete []fileList;
}

return ret;
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

int getFileNumAndLastName(char *path,  char* lastName64)//64
{
int fileNum;
char** fileList;
int ret = getFileListAndNum( path, fileList, fileNum);
if (ret==false)
{
memcpy(lastName64, "0000", 4);
return -1;
}

char lastName[64]={0};
char curName[64]={0};
int i=0;
for ( i=0; i<fileNum; i++)
{

if (i != 0)
{
memcpy(curName, fileList[i], 4);
//lastName[4] = 0;
if (strcmp(lastName, curName))
memcpy(lastName, fileList[i], 4);
}
else
{
memcpy(lastName, fileList[0], 4);
}
//  cout << "ok.." << ++i << endl;


}

if (fileNum)
{
for (int i=0; i<fileNum; i++)
delete []fileList[i];
delete []fileList;
}


if (i)
memcpy(lastName64, lastName, 9);
else
memcpy(lastName64, "0000", 4);

return i;
}*/

#endif


