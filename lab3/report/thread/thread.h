#ifndef __thread__h
#define __thread__h

#include<stdio.h>
#include<stdarg.h>

#define maxThread 256
#define  maxStackSize (64*1024)
#define asmV __asm__ __volatile__


enum threadStatus{
    status_empty,
    status_ready,
    status_run,
    status_finish
};

//thread control block
typedef struct tcb{
    //<src>-><target>
    __uint32_t tarESP, tarEIP, tarResValue; //子线程（当前tcb对应线程）
    __uint8_t stack[maxStackSize];          //栈
    enum threadStatus status;               //线程状态
} tcb;

//创建线程
int create_thread(__uint32_t func, int argNum, ...);

//继续运行线程
int launch_thread(int cur_id, int id);

//暂停线程
void yield_thread(int id,int target_id);

//销毁线程
void destory_thread(int target_id);

//获取线程状态
enum threadStatus getThreadStatus(int id);

#endif