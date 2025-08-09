#pragma once

#define TASK_STACK_SIZE         10
#define THREAD_POOL_SIZE        4
#define MAIN_STACK_SIZE         128
#define NULL                    ((void *) 0x00)

typedef void (*funcptr)(void);
typedef struct tcb
{
        unsigned int stack[TASK_STACK_SIZE];
        unsigned int *sp;
        struct tcb *next;
} tcb_t;

void __enable_irq(void);
void __disable_irq(void);
void create_thread(funcptr task);

void sys_init(void);

