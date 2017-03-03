#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
void main(int argc,char *argv[])
{
   int fd,i;
   char temp;
  if(argc==1)
  {
     printf("Enter filename to display!");
    return;
}
 for(i=1;i<argc;i++)
{
    fd=open(argv[i],O_RDONLY);
   if(fd<=0)
    printf("FILE DOES NOT EXIST");
    else
    {
      while((read(fd,&temp,1))>0)
      write(1,&temp,1);
      printf("\n");
      close(fd);
    }
}
return;
}

