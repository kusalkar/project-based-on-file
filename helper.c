#include "packer.h"
BOOL FilePacker(char* DirName,char* Filename)
{
 DIR *dir;
 struct dirent *entry;
 struct stat filestat;
 char name[100]={'\0'};
 char buff[256]={'\0'};
 char *ptr=NULL;
 int icnt=0,fd,fdread,retread,ret,fdnew,temp;
 char key;
 FILEINFO obj;

 if((dir=opendir(DirName))==NULL)
 {
   printf("\n ERROR:Unable to open specified directory\n");
   return ERR_ACCESS; //2
 }

  fd=creat(Filename,0666); //read write
   
  if(fd==-1)
  {
    printf("ERROR:Unable to create file\n");
    return ERR_ACCESS; //2
  }

  key=strlen(Filename);
  
  write(fd,"marvellous21",strlen("marvellous21"));
  write(fd,&key,1);
  
  printf("key wriiten...\n");
  while((entry =readdir(dir))!=NULL)
  {
    sprintf(name,"%s/%s",DirName,entry->d_name);
    stat(name,&filestat);
    if(S_ISREG(filestat.st_mode))
     {
       fdread=open(name,O_RDONLY);
       strcpy(obj.name,entry->d_name);
       obj.size=filestat.st_size;
   
      write(fd,&obj,sizeof(obj));
      while((retread=read(fdread,buff,sizeof(buff)))!=0)
      {
        temp=retread;
        while(temp !=0)   //encryption
	{
	  buff[temp]+=key;
           temp--;
  	}
 	 write(fd,buff,retread);
      }
	close(fdread);
 	icnt++;
     }//end of if
 }
  closedir(dir);
  printf("%d Files successfully combined\n",icnt);
  return SUCCESS;
}

BOOL FileUnpacker(char* FileName)
{
 DIR *dir;
 struct dirent *entry;
 struct stat filestat;
 char name[100]={'\0'};
 char buff[256]={'\0'};
 char *ptr=NULL;
 
 int fd,fdread,retread,ret,fdnew,temp,icnt=0;
 char key;
 FILEINFO obj;
 fd=open(FileName,O_RDONLY);
 
  if(fd==-1)
  {
    printf("ERROR:Unable to open file\n");
    return ERR_ACCESS; //2
  }
 
  ret=read(fd,buff,strlen("marvellous21"));
  if(ret<=0)
  {
    printf("ERROR:Unable to open file\n");
    return ERR_ACCESS; //2
  }
  if(strcmp(buff,"marvellous21")!=0)
  {
   printf("ERROR:Fail to read merge file\n");
   return ERR_INVALID;
  }
  read(fd,&key,1);
  while((ret=read(fd,&obj,sizeof(obj)))!=0)
  {
    fdnew=creat(obj.name,0666);   
    ptr=(char*)malloc(obj.size*sizeof(char));
    read(fd,ptr,obj.size); 
    temp=obj.size;
      while(temp !=0)  //decryption
	{
	  ptr[temp]-=key;
           temp--;
  	}
     write(fdnew,ptr,obj.size);
     close(fdnew);
     free(ptr);
     icnt++;
  }
  close(fd); 
  printf("%d Files successfully recreated\n",icnt);
  return SUCCESS;
}//end of unpacker

void DisplayHelp()
{
  printf("\n................FILE PACKER AND UNPACKER...................\n");
  printf("Devloped by-Miracle of BSCS\n");
  printf("............................................................\n");
  printf("To pack files\n");
  printf("\tExe_name -p Directory_name  File_name\n");
  printf("TO unpack files\n");
  printf("\tExe_name -u File_name\n");
 }

void DisplayError(BOOL ret)
{
 switch(ret)
 {
  case ERR_INVALID:
          printf("ERROR:Invalid file for unpacking\n");
          break;
 case  ERR_ACCESS:
	  printf("ERROR:Access defined");
          break;
  }
}

