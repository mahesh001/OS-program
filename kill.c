
#include<stdio.h>
#include<sys/types.h>
#include<signal.h>
#include<string.h>
void main(int argc, char *argv[])
{    int i=1;
     if(argc==1)
     {
        printf("Specify process IDs!");
        return;
     }
     int a= argv[2][1]-'0';

    for(i=3;i<argc;i++)
{
     int pid=atoi(argv[i]);
     kill(pid,a);
 }
return;
}

