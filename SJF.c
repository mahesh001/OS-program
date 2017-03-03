#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
int main()
{int bt[10],pt[20],p[20],wt[20],tat[20],i,j,n,total=0,pos,temp;
float avgwt,avgtat;
printf("enter no of process");
scanf("%d",&n);
printf("enter brust time: \n");
for(i=0;i<n;i++)
{
printf("p%d",i+1);
scanf("%d",&bt[i]);
p[i]=i+1;
}
for(i=0;i<n;i++)
{
pos=i;
for(j=i+1;j<n;j++)
{
if(bt[j]<bt[pos])
pos=j;
}
temp=bt[i];
bt[i]=bt[pos];
bt[pos]=temp;
temp=p[i];
p[i]=p[pos];
p[pos]=temp;
}
wt[0]=0;
for(i=1;i<n;i++)
{
wt[i]=wt[i-1]+bt[i-1];
total+=wt[i];
}
avgwt=(float)total/n;
total=0;
printf(" nprocess   brust time    waiting time    turnaround time \n");
for(i=0;i<n;i++)
{
tat[i]=bt[i]+wt[i];
total+=tat[i];
printf("%d\t\t  %d\t\t  %d \t\t %d  \n",p[i],bt[i],wt[i],tat[i]);
}
avgtat=(float)total/n;
printf(" average waiting time:=%f",avgwt);
printf("\n");
printf("average turnaround time:=%f",avgtat);
return 0;
}

