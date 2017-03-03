#include<stdio.h>
#include<sys/sem.h>
#include<pthread.h>
#define MAXCHAIRS 4
int nextCustomerNo=1;
int f=0,l=0;
int waitingCustomerCount=0;
int custNos[MAXCHAIRS];
pthread_mutex_t lck;
pthread_cond_t custCond[MAXCHAIRS];
pthread_cond_t brbrCond;
void wakeUpbarber()
{    pthread_cond_signal(&brbrCond);
}
void customerWait(int chair)
{   pthread_cond_wait(&custCond[chair],&lck);
}
int checkVacancyAndWait(void)
{
    int chair;
    int custNo;
    pthread_mutex_lock(&lck);
    if(waitingCustomerCount==MAXCHAIRS)
    {
      pthread_mutex_unlock(&lck);
      return 0;
      }
    else
    {  chair=l;
       custNo=custNos[chair]=nextCustomerNo++;
       l=(l+1)%MAXCHAIRS;
       waitingCustomerCount++;
       if(waitingCustomerCount==1)
       wakeUpbarber();
       customerWait(chair);
       pthread_mutex_unlock(&lck);
       return custNo;
      }
 }
 int checkCustomerAndSleep(void)
 {   pthread_mutex_lock(&lck);
     if(waitingCustomerCount==0)
     pthread_cond_wait(&brbrCond,&lck);
     }
 void serviceCustomer()
 {    int custNo,chair;
      chair=f;
      f=(f+1)%MAXCHAIRS;
      custNo =custNos[chair];
      waitingCustomerCount--;
      pthread_cond_signal(&custCond[chair]);
      pthread_mutex_unlock(&lck);
      printf("barber Servicing %d Customer \n",custNo);
      sleep(3);
  }
 void*barber()
  {  while(1)
     {

     checkCustomerAndSleep();
     serviceCustomer();
     }
  }
  void* customer()
  {
      int custno;
      while(1)
      {
        custno=checkVacancyAndWait();
        if(custno!=0)
        {
           printf("Customer %d getting serviced...\n",custno);
           sleep(3);
        }
        else
        {  printf("No chair is vacant and customer leaving,...\n");
           sleep(3);
         }
      }
 }
 int main()
 {     int i;
        pthread_t brbr,cust[MAXCHAIRS+1];
        pthread_create(&brbr,NULL,barber,NULL);
        for(i=0;i<MAXCHAIRS+1;i++)
        pthread_create(&cust[i],NULL,customer,NULL);
        pthread_join(brbr,NULL);
}

