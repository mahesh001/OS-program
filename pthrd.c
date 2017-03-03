#include<stdlib.h>
#include<ucontext.h>
#define MAX_FIBERS 10
#define FIBER_STACK 1024*1024
typedef struct
{  ucontext_t context;
   int active;
   void* stack;
}fiber;
static fiber fiberList[MAX_FIBERS];
static int currentFiber=-1;
static int inFiber=0;
static int numFibers=0;
static ucontext_t mainContext;

void initFibres()
{
        int i;
        for(i=0;i<MAX_FIBERS;i++)
        {
                fiberList[i].active=0;
        }
        return;
}

void fiberYield()
{
        if(inFiber)
        {
                swapcontext(&fiberList[currentFiber].context,&mainContext);
        }
        else
        {
                if(numFibers==0) return;
                currentFiber=(currentFiber +1 )%numFibers;
                inFiber=1;
                swapcontext(&mainContext,&fiberList[currentFiber].context);
                inFiber=0;
                if(fiberList[currentFiber].active==0)
                {
                        free(fiberList[currentFiber].stack);
                        --numFibers;
                        if(currentFiber!=numFibers)
                        {
                                fiberList[currentFiber]=fiberList[numFibers];
                        }
                        fiberList[numFibers].active=0;
                }
        }
        return;
}
static void fiberStart(void(*func)(void))
{
        fiberList[currentFiber].active=1;
        func();
        fiberList[currentFiber].active=0;
        fiberYield();
}
int spawnFiber(void(*func)(void))
{
        getcontext(&fiberList[numFibers].context);
        fiberList[numFibers].context.uc_link=0;
        fiberList[numFibers].stack=malloc(FIBER_STACK);
        fiberList[numFibers].context.uc_stack.ss_sp=fiberList[numFibers].stack;
        fiberList[numFibers].context.uc_stack.ss_size=FIBER_STACK;
        fiberList[numFibers].context.uc_stack.ss_flags=0;
        makecontext(&fiberList[numFibers].context,(void(*)(void))&fiberStart,1,func);
        ++numFibers;

}
int waitForAllFibers()
{
        int fibersRemaining=0;
        if(inFiber)fibersRemaining=1;
        while(numFibers>fibersRemaining)
        {
          fiberYield();
        }
}
