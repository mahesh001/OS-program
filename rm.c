#include<unistd.h>
#include<stdio.h>
#include<string.h>
void main(int argc, char *argv[])
{ int i;
   if(argc==1)
   { printf("File not specified!");
    return;
   }
  for(i=1;i<argc;i++)
   {
      unlink(argv[i]);
      printf("\n%s File removed",argv[i]);
      }
    return;
}


