#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
pthread_mutex_t writer_wait,db,counter;
int no_of_readers=0;
void check_and_wait_w(int id)
{

  if(pthread_mutex_trylock(&writer_wait)!=0)
    {   printf("Writer %d waiting \n",id);
          pthread_mutex_lock(&writer_wait);
     }

 }
 void check_and_wait_r(int id)
 {    if(pthread_mutex_trylock(&writer_wait)!=0&&pthread_mutex_trylock(&db)!=0)
      {  printf("Reader %d waiting \n",id);
         pthread_mutex_lock(&writer_wait);
     }
 }
void read1(int id)
{  pthread_mutex_lock(&counter);
   no_of_readers++;
   pthread_mutex_unlock(&counter);
   if(no_of_readers==1)
      pthread_mutex_lock(&db);
   pthread_mutex_unlock(&writer_wait);
   printf("reader %d reading...\n",id);
   sleep(rand()%5);
   printf("reader %d finished \n",id);
   pthread_mutex_lock(&counter);
   no_of_readers--;
   pthread_mutex_unlock(&counter);
   if(no_of_readers==0)
   pthread_mutex_unlock(&db);

}
void write1(int id)
{    pthread_mutex_lock(&db);
     pthread_mutex_unlock(&writer_wait);
     printf("Writer %d writing...\n",id);
     sleep(rand()%5);
     printf("writer %d finished \n",id);
     pthread_mutex_unlock(&db);
}

void *reader(void *arg)
{     int id= *(int*)arg;
      printf("reader %d started \n",id);
      while(1)
      {  sleep(rand()%4);
           check_and_wait_r(id);
           read1(id);
      }
}
void* writer(void *arg)
{    int id =*(int*)arg;
     printf("Writer %d started \n",id);
     while(1)
     {   sleep(rand()%5);
         check_and_wait_w(id);
         write1(id);
         }
}
int main(void)
{    pthread_t R[5],W[5];
     int ids[5];
     int i;
     for( i=0;i<5;i++)
    {   ids[i]=i+1;
        pthread_create(&R[i],NULL,reader,(void*)&ids[i]);
        pthread_create(&W[i],NULL,writer,(void*)&ids[i]);
    }
   pthread_join(R[0],NULL);
   exit(0);
}


