
#include<stdio.h>
#include<string.h>
void  main(int argc,char *argv[])
{
   FILE *fp;
   int c=0,w=0,l=0;
   char ch;
   printf("%d\n",argc);
   printf("%s\n %s\n %s\n",argv[0],argv[1],argv[2]);
   if(argc<2)
{
   printf("COMMAND ERROR1");
   return;
}
if(argc>4)
{
   printf("Command error2\n");
return;
}
 if(argc==4)
{
    fp=fopen(argv[3],"r");
    if(fp==NULL)
{
    printf("Error in opening files");
   return;
}
}
  ch=fgetc(fp);
  while(!feof(fp))
{
    if(ch==' '||ch=='\n')
    w++;
   if(ch=='\n')
   l++;
c++;
ch=fgetc(fp);
}
if(!strcmp(argv[2],"-w"))
printf("Word count :%3d\n",w);
else if(!strcmp(argv[2],"-l"))
printf("Line count: %3d\n",l);
else if(!strcmp(argv[2],"-c"))
{
   printf("character count: %3d\n",c);
}

fclose(fp);
return;
}


