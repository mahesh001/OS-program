#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
int main()
{int bt[10],pr[20],p[20],wt[20],tat[20],i,j,n,total=0,pos,temp;
float avgwt,avgtat;
printf("enter no of process");
scanf("%d",&n);
printf("enter brust time: \n");
for(i=0;i<n;i++)
{
printf("p%d",i+1);
scanf("%d",&bt[i]);

}

wt[0]=0;
for(i=1;i<n;i++)
{
wt[i]=0;
for(j=0;j<i;j++)
wt[i]+=bt[j];
total+=wt[i];
}
avgwt=(float)total/n;
total=0;
printf("   brust time      waiting time    turnaround time \n");
for(i=0;i<n;i++)
{
tat[i]=bt[i]+wt[i];
total+=tat[i];
printf("  %d\t\t  %d \t\t %d  \n",bt[i],wt[i],tat[i]);
}
avgtat=(float)total/n;
printf(" average waiting time:=%f",avgwt);
printf("\n");
printf("average turnaround time:=%f",avgtat);
return 0;
}

