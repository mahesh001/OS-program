#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
#include<stdlib.h>
#define BUFSIZE 10
pthread_mutex_t mutex;
pthread_t tidP,tidC;
sem_t full,empty;
int counter;
int buffer[BUFSIZE];
void initialise()
{
     pthread_mutex_init(&mutex,NULL);
     sem_init(&full,1,0);
     sem_init(&empty,1,BUFSIZE);
     counter=0;
}
void write(int item)
{
        buffer[counter++]=item;
}
int read()
{
        return(buffer[--counter]);
}
void* producer(void * param)
{      while(1) {
        int wt,item,i;
        item=rand()%5;
        wt=rand()%5;
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        printf("\n Prodeucer has produced item %d \n",item);
        write(item);
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
        sleep(rand()%3);
}
}
void* consumer(void *param)
{      while(1)
{
        int wt,i,item;
        wt=rand()%5;
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        item=read();
        printf("\n Consumer has consumed item %d\n",item);
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
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
                  
