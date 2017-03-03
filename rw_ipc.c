#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
sem_t rca;//reader count access
sem_t dba;//database access
int rc=0;
void* reader(void *arg);
void* writer(void *arg);
int main()
{
        int i=0,readerthread=0,writerthread=0;
        sem_init(&rca,0,1);
        sem_init(&dba,0,1);
        pthread_t rtid[5],wtid[5];
        for(i=0;i<5;i++)
        pthread_create(&rtid[i],NULL,(void*)&reader,(void*)&i);
        for(i=0;i<5;i++)
        pthread_create(&wtid[i],NULL,(void*)&writer,(void*)&i);
        pthread_join(wtid[4],NULL);
        pthread_join(rtid[4],NULL);
        sem_destroy(&dba);
        sem_destroy(&rca);
        return 0;
}
void* writer(void *arg)
{       int temp=*(int*)arg;
         while(1)
        {
                sleep(rand()%2);
                printf("Writer %d trying to enter \n",temp);
                sem_wait(&dba);
                printf("Writer %d is  writing into DB \n",temp);
                printf("Writer %d  is leaving \n",temp);
                sem_post(&dba);
        }
}
void* reader(void *arg)
{      int temp=*(int*)arg;
        while(1)
        {
                sleep(rand()%3);
                sem_wait(&rca);
                rc++;
                if(rc==1)
                sem_wait(&dba);
                printf("Reader %d reading \n",temp);
                sem_post(&rca);
                sem_wait(&rca);
                rc--;
                printf("Reader %d is leaving\n",temp);

                if(rc==0)
                {  sem_post(&dba);
                }
                sem_post(&rca);
        }
}

