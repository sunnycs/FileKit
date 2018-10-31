#ifndef FILEKIT_H
#define FILEKIT_H	

#ifdef _WIN32
/*
param:path, the input path(including the final '/')
param:type, image type, exclude '.'
param:fileList, the list of image names, just image names
return: file num
*/
int getFileListAndNum(char* path, char* type, char** &fileList);

#endif


#ifdef linux
int getFileListAndNum(char* path, char** &fileList);
int getFileNum(char* path);

//typedef struct
//{
//    char name[64];
//    int userId;
//    int sampleNum;
//    char features[512];
//}dataUnit;
/*int getNewName(char *path,  char* newName64);//64
int getFileNumAndLastName(char *path,  char* lastName64);//64
int checkDB(char *path,int perUser);

int myitoa5(int i, char *indexname5);
int myatoi(char* input);*/
#endif

#endif

