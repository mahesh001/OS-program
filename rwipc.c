#include<stdio.h>
//#include<pthread.h>
#include "semaphore.c"
int  rca;//reader count access
int  dba;//database access
int rc=0;
void* reader(void *arg);
void* writer(void *arg);
int main()
{
        int i=0,readerthread=0,writerthread=0;
        rca= sem_init(1,1);
        dba=sem_init(1,1);
        pthread_t rtid[5],wtid[5];
        for(i=0;i<5;i++)
        pthread_create(&rtid[i],NULL,(void*)&reader,(void*)&i);
        for(i=0;i<5;i++)
        pthread_create(&wtid[i],NULL,(void*)&writer,(void*)&i);
        pthread_join(wtid[4],NULL);
        pthread_join(rtid[4],NULL);
       // sem_destroy(&dba);
       // sem_destroy(&rca);
        return 0;
}
void* writer(void *arg)
{       int temp=*(int*)arg;
         while(1)
        {
                sleep(rand()%2);
                printf("Writer %d trying to enter \n",temp);
                //sem_wait(&dba);
                sem_change(dba,0,-1);
                printf("Writer %d is  writing into DB \n",temp);
                printf("Writer %d  is leaving \n",temp);
                //sem_post(&dba);
                sem_change(dba,0,1);
        }
}
void* reader(void *arg)
{      int temp=*(int*)arg;
        while(1)
        {
                sleep(rand()%3);
                //sem_wait(&rca);
                sem_change(rca,0,-1);
                rc++;
                if(rc==1)
                //sem_wait(&dba);
                sem_change(dba,0,-1);
                printf("Reader %d reading \n",temp);
                //sem_post(&rca);
                //sem_wait(&rca);
                sem_change(rca,0,1);
                sem_change(rca,0,-1);
                rc--;
                printf("Reader %d is leaving\n",temp);

                if(rc==0)
                {
                 sem_change(dba,0,1);
                 //sem_post(&dba);
                }
                sem_change(rca,0,1);
        }
}

