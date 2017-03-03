
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>

pthread_t phil[5];
pthread_mutex_t chops[5];
void* func(int n)
{     // int n= *(int*)t;
       int p= (n)%5;
       while(1){
        printf("\n Philosopher %d is thinking", n);
       pthread_mutex_lock(&chops[n-1]);
       pthread_mutex_lock(&chops[p]);
   
       printf("\n Philosopher %d is eating using chops %d and %d",n,n-1,p);
       sleep(2);
       pthread_mutex_unlock(&chops[n-1]);
       pthread_mutex_unlock(&chops[p]);
       printf("\n Philosopher %d finished eating",n);
       }
 }

int main()
{
    int i,k;
    char msg[10];
    for(i=1;i<=5;i++)
    {  k=pthread_mutex_init(&chops[i-1],NULL);
       if(k==-1)
       {   printf("\n Mutex Init failed");
           exit(1);
       }
    }
    for(i=1;i<=5;i++)
    {   k=pthread_create(&phil[i-1],NULL,func,i);
        if(k!=0)
        {   printf("\nThread creation error");
            exit(0);
        }
    }
    for(i=1;i<=5;i++)
    {k= pthread_join(phil[i-1],(void*)&msg);
     if(k!=0)
     {   printf("\n Thread join failed");
         exit(1);
     }

}

     return 0;}

