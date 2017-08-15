#ifndef _TPOOL_H_
#define _TPOOL_H_

static void* thread_routine(void* arg);
int createPool(int max_thr_num);
void destroyPool();
int addWorkPool(void*(*routine)(void*),void* arg);


#endif
