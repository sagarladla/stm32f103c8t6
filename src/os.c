#include <os.h>

tcb_t thread_pool[THREAD_POOL_SIZE];
tcb_t *exec_queue;
tcb_t *curr_thread;
tcb_t *next_thread;


// void create_thread(funcptr task)
// {
//         __disable_irq();
//         unsigned int *sp;
//         tcb_t *tasks = &thread_pool;
//         return;
// }
// void sys_clock_init(void)
// {
//         // Initialize the system clock
//         sys_clock_update();
// }
