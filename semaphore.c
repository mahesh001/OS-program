#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/sem.h>
#include<sys/ipc.h>
union senum
{
   int val;
   int *array;
};
int state=1;
int sem_init(int num,int val)
{       int i;
        key_t key=ftok(".",state++);
    int sem_id= semget(key,num,IPC_CREAT|0666);
     union senum tmp;
     tmp.val=val;
     for(i=0;i<num;i++)
     semctl(sem_id,i,SETVAL,tmp);
     return sem_id;
 }
 int sem_init_diff(int num,int a[])
 {
     key_t key=ftok(".",state++);
     int sem_id=semget(key,num,IPC_CREAT|0666);
     union senum temp;
     temp.array=0;
    semctl(sem_id,num,SETALL,temp);
     return sem_id;
 }
 void sem_change(int sem_id,int sem_no,int amount)
 {
       struct sembuf tmp;
        tmp.sem_num=sem_no;
        tmp.sem_flg=0;
        tmp.sem_op=amount;
        semop(sem_id,&tmp,1);
}
~

