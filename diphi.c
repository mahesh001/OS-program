


#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

main()
{
	int chopstick[5];
	int pid;
	int k;
	struct sembuf wait,signal;

	chopstick[0]=semget(0x10,1,IPC_CREAT|0666);
	chopstick[1]=semget(0x20,1,IPC_CREAT|0666);
	chopstick[2]=semget(0x30,1,IPC_CREAT|0666);
	chopstick[3]=semget(0x40,1,IPC_CREAT|0666);
	chopstick[4]=semget(0x50,1,IPC_CREAT|0666);

	semctl(chopstick[0],0,SETVAL,1);
	semctl(chopstick[1],0,SETVAL,1);
	semctl(chopstick[2],0,SETVAL,1);
	semctl(chopstick[3],0,SETVAL,1);
	semctl(chopstick[4],0,SETVAL,1);

	wait.sem_num=0;
	wait.sem_op=-1;
	wait.sem_flg=0;

	signal.sem_num=0;
	signal.sem_op=1;
	signal.sem_flg=0;

	for (;;)
	{
		printf("Enter the Philosopher Who is Hungry  :");
		scanf("%d",&k);	

		pid=fork();

		if (pid==0)
		{
			if ((k%2)==0)
			{
				printf("Philosopher is Hungry\n");
				semop(chopstick[k+1%5],&wait,1);
				semop(chopstick[k%5],&wait,1);

				printf("Philosopher %d is Eating\n",k);
				sleep(3);

				semop(chopstick[k+1%5],&signal,1);
				semop(chopstick[k%5],&signal,1);
				
				printf("philosopher %d has finished\n",k);
			}
			else
			{
				
				printf("Philosopher is Hungry\n");
				semop(chopstick[k%5],&wait,1);
				semop(chopstick[k+1%5],&wait,1);

				printf("Philosopher %d is Eating\n",k);
				sleep(3);

				semop(chopstick[k%5],&signal,1);
				semop(chopstick[k+1%5],&signal,1);

				printf("Philosopher %d has Finished\n",k);
			}
			exit(1);
		}
	}
}	

