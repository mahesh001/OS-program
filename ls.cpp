#include<stdio.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<sys/types.h>
#include<dirent.h>
#include<malloc.h>
#include<string.h>
#include<grp.h>
#include<pwd.h>
#include<time.h>
int main(int argc,char* argv[])
{ // struct stat *s;
   char buf[100];
   int i,j;
   char P[10]="rwxrwxrwx",ap[10]=" ";
   struct passwd *p;
   struct group *g;
   struct tm *t;
   char time[26];
struct stat sbuf;
 //char *curr_dir=NULL;
DIR *dp=NULL;
struct dirent *dptr=NULL;
unsigned int count=0;
//curr_dir=getenv("PWD");
/*if(NULL==curr_dir)
{
printf("\nError! Couldnt get working directory");
return 0;
} */
dp= opendir(".");
if(NULL==dp)
{
printf("\nError:Couldnt open working directory\n");
return 0;

}
readdir(dp);
readdir(dp);
while((dptr=readdir(dp))!=NULL)
{   //strcpy(buf,(const char*)curr_dir);
   // strcat(buf,"/");
   // strcat(buf,dptr->d_name);
 //   struct stat sbuf;
    stat(dptr->d_name,&sbuf);
  if(!strcmp(argv[1],"-l"))
{
   // printf("%s\n",dptr->d_name);
    if(S_ISDIR(sbuf.st_mode))
    printf("d");
else if(S_ISREG(sbuf.st_mode))
    printf("-");


      else if(S_ISCHR(sbuf.st_mode))
    printf("c");
else if(S_ISBLK(sbuf.st_mode))
    printf("b");

else if(S_ISLNK(sbuf.st_mode))
    printf("l");
else if(S_ISFIFO(sbuf.st_mode))
    printf("p");
else if(S_ISSOCK(sbuf.st_mode))
    printf("s");
for(i=0,j=(1<<8);i<9;i++,j>>=1)
ap[i]=(sbuf.st_mode&j)?P[i]:'-';
printf("%s",ap);
printf("\t%ld",sbuf.st_nlink);
p=getpwuid(sbuf.st_uid);
printf("\t%s",p->pw_name);
g=getgrgid(sbuf.st_size);
printf("\t%s",g->gr_name);
printf("\t%ld",sbuf.st_size);
t=localtime(&sbuf.st_mtime);
strftime(time,sizeof(time),"%b %d %H:%M",t);
printf("\t%s",time);
printf("\t%s\n",dptr->d_name);

     //printf("%lld\n",(sbuf->st_size));
   // else if(strcmp(argv[1],"-a")==0)
   // printf("%s\n",dptr->d_name);
 }
  if(!strcmp(argv[1],"-a"))
{
   printf("%s \n",dptr->d_name);
}
   }
return 0;
}
