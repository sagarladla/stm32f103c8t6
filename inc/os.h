#pragma once

#define TASK_STACK_SIZE 3

typedef void (*funcptr)(void);
typedef struct tcb
{
        unsigned int stack[TASK_STACK_SIZE];
        unsigned int *sp;
        struct tcb *next;
} tcb_t;
void intr_en(void);
void intr_di(void);
void sys_init(void);
void create_thread(funcptr task);
