#include "packer.h"
int main(int argc,char* argv[])
{
  BOOL ret;
 
 if(argc < 2 || argc > 4)
 {
  printf("ERROR: Not sufficient argument\n");
  return -1;
  }
 
 if((strcmp(argv[1],"-p")==0)||(strcmp(argv[1],"-P")==0))
 //if((stricmp(argv[1],"-p")==0))
 {
  ret =FilePacker(argv[2],argv[3]);
  if(ret != SUCCESS)
    { 
     DisplayError(ret);
    }
 }
 else if((strcmp(argv[1],"-u")==0)||(strcmp(argv[1],"-U")==0))
 //else if((stricmp(argv[1],"-u")==0))
 {
   ret = FileUnpacker(argv[2]);
  // ret=FileUnpacker(argv[2],argv[3]);
   if(ret != SUCCESS)
       {
        DisplayError(ret);
	}
 }
 else if((strcmp(argv[1],"-h")==0)||(strcmp(argv[1],"-H")==0))
 //else if((stricmp(argv[1],"-h")==0))
 {
  DisplayHelp();
 }
 else
  {
    printf("ERROR: Incorrect argument\n");
  }
  return 0;
}
  
