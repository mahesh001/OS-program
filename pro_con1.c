#include<string.h>
#include<unistd.h>
#include<stdio.h>
#include<malloc.h>
#define size 5;
pthread_mutex_t full,empty,acc;
int x=1;
int eflag=0,fflag=0;
int  f=0,r=0,id=1;
int cnt=0;
int *q;
void* pro()
{    printf("producer started \n");
     while(1)
     {   pthread_mutex_lock(&acc);
         if(cnt==5)
         {  printf("Producer waiting...\n");
            fflag=1;
            pthread_mutex_lock(&full);
            pthread_mutex_unlock(&acc);
            sleep(rand()%2);
            pthread_mutex_lock(&acc);
          }
          cnt++;
          q[f]=id++;
          if(cnt==1&&eflag==1)
          {  eflag=0;
             pthread_mutex_unlock(&empty);
           }
           printf("produced item %d\n",q[f]);
           f=(f+1)%size;
           pthread_mutex_unlock(&acc);
           sleep(rand()%3);
      }
}
void* con()
{
    printf("Consumer started \n");
    while(1){
        if(cnt==0)
        {   printf("consumer waiting...\n");
            eflag=1;
            pthread_mutex_unlock(&acc);
            pthread_mutex_lock(&empty);
            sleep(rand()%2);
            pthread_mutex_lock(&acc);
          }
          cnt--;
          printf("Consumed item %d\n",q[r]);
          r=(r+1)%size;
          if(cnt==4 && fflag==1)
          {  fflag=0;
             pthread_mutex_unlock(&full);
           }
           pthread_mutex_unlock(&acc);
           sleep(rand()%2);
     }
}
int main()
{   q=(int*)calloc(5,sizeof(int));
    pthread_t prod,cons;
    pthread_create(&prod,NULL,pro,NULL);
    pthread_create(&cons,NULL,con,NULL);
    pthread_join(prod,NULL);

}

