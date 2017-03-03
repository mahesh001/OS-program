#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/sem.h>
#include<sys/ipc.h>
#include<sys/types.h>

#define shmsize 10           //shared memory size(to store varible readcount in this case)
#define shmkey 111          //key used for shared memory creation
#define chairno 3 
char* shmpointer;
union semun
{
	int val;
	struct semid_ds *buf;
	unsigned short *array;	
}arg;

void wait(int semid)                            //wait(i.e.,p)
{
	struct sembuf sem={0,-1,0};
	semop(semid,&sem,1);
}
void signal(int semid)                                 //signal(i.e.,v)
{
	struct sembuf sem={0,1,0};
	semop(semid,&sem,1);
}
int creat_init_semph(int key,int initial_val)          //function to create and initiate a semaphor with some intial value
{
	int semid;
	if((semid=semget(key,1, 0666 | IPC_CREAT))==-1)
	{
		perror("semget\n");
		exit(1);
	}
	arg.val=initial_val;
	semctl(semid,0,SETVAL,arg);
	return semid;
}
int creat_shmemory(int key)                           //function to create shared memory
{
	int shmid;
	if((shmid=shmget(key,shmsize,0666 | IPC_CREAT))==-1)
	{
		perror("shmget\n");
		exit(1);
	}
	return shmid;
}
char* attach_shmemory(int shmid)                      //function to attach shared memory to the process area
{
	char* shmpointer;
	if((shmpointer=shmat(shmid,NULL,0))==(char*)-1)
	{
		perror("shmat\n");
		exit(1);
	}
	return shmpointer;
}
int getshm()                          //funtion to return the value stored in shared memory in integer form
{
	char* s=shmpointer;
	int rcount=0;
	while(*s!='\0')
	{
		rcount=rcount*10+(*s-'0');
		s++;
	}
	return rcount;
}
void setshm(int count)            //function to store readercount in shared memory in string format
{
	char *s=shmpointer;
	char buf[10];
	int i=0;
	while(count)
	{
		buf[i++]=(count%10)+'0';
		count/=10;
	}
	i--;
	while(i>=0)
		*s++=buf[i--];
	*s='\0';
}
int main()
{
		
	int barber=creat_init_semph(0x10,0);      
	int customer=creat_init_semph(0x30,0);
	int mutex_chair=creat_init_semph(0x50,1);             //chair number access mutex for locking and unlocking
	shmpointer=attach_shmemory(creat_shmemory(shmkey));              
	setshm(chairno);
	int nooffreechair=chairno;
	while(1)
	{
		
	       if(getshm()==chairno)
		{
			printf("barber is sleeping......\n");
		}
		wait(customer);
		wait(mutex_chair);
		nooffreechair=getshm()+1;
		setshm(nooffreechair);
		signal(barber);
		signal(mutex_chair);
		printf("barber is cutting hair.....\n");
		sleep(5);
	}
	return 0;
}



