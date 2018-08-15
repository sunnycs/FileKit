# FileKit
Return file name list of the destination floder.
# getFileNum("./database/", "bmp")
Return the number of .bmp files under "./database/"
# getFileListAndNum("./database/", "bmp", fileList, fileNum)
Returns: true / false
```
char** fileList; //Data structure to store file names.
int num; //total number of the .bmp files
int ret = getFileListAndNum("./database/", "bmp", fileList, num);
if (!ret)
{
	cout << "file detection error" << endl;
	return -1;
}
```

