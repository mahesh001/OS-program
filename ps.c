
#include<stdio.h>
#include<sys/types.h>
#include<dirent.h>
#include<string.h>
void main(int argc,char *argv[])
{

    DIR *dp;
    struct dirent *dir;
    dp=opendir("/proc");
    dir=readdir(dp);
char path[100];
while(dir!=NULL)
{
      if(isdigit(dir->d_name[0]))
     {
        strcpy(path,"/proc/");
        strcat(path,dir->d_name);
        strcat(path,"/stat");
        FILE *fp;
     fp=fopen(path,"r");
     int a;
 char b[50];
 char c[2];
fscanf(fp,"%d",&a);
fscanf(fp,"%s",b);
fscanf(fp,"%s",c);
fclose(fp);
if(!strcmp(c,"R"))
printf("%d\t%s\t%s\n",a,b,c);
}
dir=readdir(dp);
}
return;
}

