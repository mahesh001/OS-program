//#include<stdio.h>
//#include<semaphore.h>
#include<pthread.h>
//#include<stdlib.h>
#include "semaphore.c"
#define BUFSIZE 10
pthread_mutex_t mutex;
pthread_t tidP,tidC;
int full,empty;
int counter;
int buffer[BUFSIZE];
void initialise()
{
     pthread_mutex_init(&mutex,NULL);
    full= sem_init(1,1);
    empty=sem_init(1,10);
     counter=0;
}
void write1(int item)
{
        buffer[counter++]=item;
}
int read1()
{
        return(buffer[--counter]);
}
void* producer(void * param)
{      while(1) {
        int wt,item,i;
        item= rand()%5;
        if(item<0)
        item=item*-1;
        wt=rand()%5;
        //sem_wait(&empty);
        sem_change(empty,0,-1);
        pthread_mutex_lock(&mutex);
     if(item<0)
        item=item*-1;

        printf("\n Prodeucer has produced item %d \n",item%5);
        write1(item);
        pthread_mutex_unlock(&mutex);
//      sem_post(&full);
        sem_change(full,0,1);
        sleep(rand()%3);
}
}
void* consumer(void *param)
{      while(1)
{
        int wt,i,item;
        wt=rand()%5;
        //sem_wait(&full);
        sem_change(full,0,-1);
        pthread_mutex_lock(&mutex);
        item=read1();
             if(item<0)
        item=item*-1;

        printf("\n Consumer has consumed item %d\n",item%5);
        pthread_mutex_unlock(&mutex);
//      sem_post(&empty);
        sem_change(empty,0,-1);
        sleep(rand()%2);
}
}
int main()
{
        int n1,n2,i;
        initialise();
     // printf("\nEnter no. of Producers:\n");
      //        scanf("%d",&n1);
//      printf("Enter no. of consumers :\n");
//      scanf("%d",&n2);
//      for(i=0;i<n1;i++)
        pthread_create(&tidP,NULL,&producer,NULL);
//      for(i=0;i<n2;i++)
        pthread_create(&tidC,NULL,&consumer,NULL);
//      for(i=0;i<n1;i++)
        pthread_join(tidP,NULL);
//      for(i=0;i<n2;i++)
        pthread_join(tidC,NULL);
        exit(0);
}
                        

