#include<sys/types.h>
#include<dirent.h>
#include<stdio.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>


#define SUCCESS 1
#define ERR_ACCESS 2   //macro for error
#define ERR_INVALID 3  //macro for error
#define TRUE 1
#define FALSE 0
typedef int BOOL;
typedef struct     //unnamed struct
{
  char name[50];  //name of file
  int size;       //size of file
}FILEINFO;

BOOL FilePacker(char*,char*);
BOOL FileUnpacker(char*);
//BOOL FileUnpacker(char*,char*);
void DisplayHelp();
void DisplayError(BOOL);



