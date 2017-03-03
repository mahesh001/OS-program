#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<malloc.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<sys/stat.h>
#define bool int
#define true 1
#define false 0
#define size 1024
char* s_string()
{ char* str= (char*)malloc(sizeof(char)*size);
  strcpy(str,"\nCmd$");
return str;
}
char* readcom()
{  char* buf=(char*)malloc(sizeof(char)*size);
   gets(buf);
   return (buf);
}
char** parsecmd(char* buf,int* cnt,bool* flag)
{
   int i=0;
   int n=strlen(buf);
   char **args=(char**)malloc(size);
    while(i<n)
   {   while(i<n&&buf[i]==' ')i++;



        char *arg=(char*)malloc(sizeof(char)*size);
        int idx=0;
       while(i<n&&buf[i]!=' '){
       if(buf[i]=='>'||buf[i]=='<'){
            *flag=true;
             int j=i;
            char *inf=(char*)malloc(sizeof(char)*size);
         char *outf=(char*)malloc(sizeof(char)*size);
        int indx=0,outdx=0;
   while(j<n)
{
      if(j<n&&buf[j]=='<')
       {
         j++;
       while(j<n&&buf[j]==' ')j++;
        while(j<n&&buf[j]!=' ')
       inf[indx++]=buf[j++];
       }


    while(j<n&&buf[j]==' ')j++;

      if(j<n&&buf[j]=='>')
       { j++;
         while(j<n&&buf[j]==' ')j++;
         while(j<n&&buf[j]!=' ')
          outf[outdx++]=buf[j++];
       }
    while(j<n&&buf[j]==' ')j++;
    }
     args[(*cnt)++]=inf;
     args[(*cnt)++]=outf;
    i=j;
  }
   if(*flag)break;
   arg[idx++]=buf[i++];
}
   if(*flag)break;
   args[(*cnt)++]=arg;
    }
return args;
}
  void redirect(char *inf, char *outf)
 {
     if(inf!=NULL)
    {    int ifd= open(inf,O_RDONLY);
         dup2(ifd,STDIN_FILENO);
         close(ifd);
    }
    if(outf!=NULL)
   {
       int ofd=open(outf,O_WRONLY|O_CREAT,0666);
       dup2(ofd,STDOUT_FILENO);
       close(ofd);
   }
}

bool execute(char **args,int cnt,bool flag)
{
        pid_t pid,wpid;
        int status;
        pid=fork();
       if(pid==0)
     {
            if(flag)
             {
                 redirect(args[cnt-2],args[cnt-1]);
                  args[cnt-2]=args[cnt-1]=NULL;
              }
              if(execvp(args[0],args)==-1)
                    perror("exec_child");
         }
        else  if(pid<0) exit(0);
       else
       {
         //  printf("Waiting for child (%d)\n",pid);
           // pid=wait(RET_STATUS);
          // printf("child(%d) finished \n",pid);
         do
            {   wpid=waitpid(pid,&status,WUNTRACED);
                }while(!WIFEXITED(status)&&!WIFSIGNALED(status));

      }
     return true;
}

void bash()
{   bool status=true;
    while(status)
    {   printf("%s",s_string());
        char *buf=(char*)malloc(sizeof(char)*size);
          buf=readcom();
           int cnt=0;
         bool flag=false;
         char **args=(char**)malloc(size);
         args=parsecmd(buf,&cnt,&flag);
         status=execute(args,cnt,flag);
        }
    return;
   }
int main()
{
    bash();
     return;
}


