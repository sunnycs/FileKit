# FileKit
Returns file name list of the destination floder.
Just works under windows.

# Functions
- getFileNum("./database/", "bmp")

	Returns the number of .bmp files under floder "./database/"

- getFileListAndNum("./database/", "bmp", fileList, fileNum)

	Returns: true / false
	The memorty of fileList is automatically allocated, hence you should `release it manully`.

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
# How to use
```
using namespace std;
char* path = "D:/imgs/";

int main()
{
	int fN = 0;
	char** fileNames = NULL;//name list
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
```

# multi-version

