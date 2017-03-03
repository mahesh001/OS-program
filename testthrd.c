#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include "pthrd.c"
void fiber1(){
        int i;
        for(i=0;i<5;i++){
                printf("fiber #1:\n",i);
                fiberYield();
                }
        return;
}
void fibo(){
        int i;
        int fib[15];
        fib[0]=0;
        fib[1]=1;
        sleep(rand()%2);
        printf("fib(0) = 0\nfib(1) =1\n");
        sleep(rand()%5);
        for(i=2;i<15;i++){
        fib[i]=fib[i-1]+fib[i-2];
        printf("fib (%d) = %d\n",i,fib[i]);
        }
}
void square(){
        int i;
        for(i=0;i<10;i++){
                printf("%d*%d=%d\n",i,i,i*i);
                fiberYield();
        }
}
int main(){
        initFibres();
        spawnFiber(&fiber1);
        spawnFiber(&fibo);
        spawnFiber(&fibo);
        spawnFiber(&square);
        waitForAllFibers();
        return 0;
}

