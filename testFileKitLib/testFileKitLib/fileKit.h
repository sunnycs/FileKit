#ifndef FILEKIT_H
#define FILEKIT_H	

int getFileNum(char *path, char* type);
bool getFileListAndNum(char* path, char* type, char** &fileList, int &fileNum);


#endif