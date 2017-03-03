#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#define SIZE 5
pthread_mutex_t chops[5];
void pinit(int a, int *b,int *c)
{   *b=(a>0)?(a-1):5;
    *c=a;
    printf("Philosopher %d started",a+1);
    return;
}
int check_spoon(int a,int b,int c)
{
       int sum=0;
       if(a&1)
       {
      ( sum=(pthread_mutex_trylock(&chops[c])))==0 ? 0:10;
       (sum+= ( pthread_mutex_trylock(&chops[b])))==0 ?0:1;
      //  sum=(pthread_mutex_trylock(&chops[c])==0)?0:10;
       // sum+= (pthread_mutex_trylock(&chops[b])==0)?0:1;

       }
       else
      { //  sum=(pthread_mutex_trylock(&chops[b])==0)?0:1;
         // sum+= (pthread_mutex_trylock(&chops[c])==0)?0:10;
         (sum= (pthread_mutex_trylock(&chops[b])))==0?0:1;
         (sum+=(pthread_mutex_trylock(&chops[c])))==0?0:10;
          }
          return sum;
}
void rel(int a,int b,int c)
{     if(a&1)
      {
         pthread_mutex_unlock(&chops[b]);
         pthread_mutex_unlock(&chops[c]);
      }
      else
      {
          pthread_mutex_unlock(&chops[c]);
          pthread_mutex_unlock(&chops[b]);


 }
 //         sleep(rand());
 }

 void wait(int a,int b,int c,int d)
  {   switch(a)
      {
       case 1:printf("Philosopher %d waiting: r unavailable\n",b+1);
             pthread_mutex_lock(&chops[c]);
  break;
       case 10: printf("Philosopher %d waiting: l unavailable\n",b+1);
               pthread_mutex_lock(&chops[d]);
  break;
       case 11: printf("philosopher %d waiting: land r unavilable\n",b+1);

                pthread_mutex_lock(&chops[c]);
                pthread_mutex_lock(&chops[d]);

                break;
       }
    return;
  }

  void eat(int a)
 {    printf("phil %d eating \n",a+1);
      sleep(rand()%5);
      printf("phil %d finished\n",a+1);
 }
 void *phil(void *arg){
     int back,front,tmp;
     int id= *(int*)arg;
     pinit(id,&back,&front);
     while(1)
     {
         printf("phil %d thinking \n",id+1);
         sleep(rand()%6);

         if((tmp=check_spoon(id,back,front))!=0)
         {
            // printf("temp--> %d\n",tmp);
             wait(tmp,id,back,front);
             eat(id);
             rel(id,back,front);
         }
    }
 }
 int main()
 {    pthread_t ph[5];
      int *q;
      int i;
char msg[10];
      for(i=0;i<5;i++)
      {  pthread_mutex_init(&chops[i],NULL);
      }
      q=(int*)malloc(5*sizeof(int));
      for(i=0;i<5;i++)
      {
         q[i]=i;
         pthread_create(&ph[i],NULL,phil,(void*)&q[i]);
         }

         pthread_join(ph[0],NULL);



}

