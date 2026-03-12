/*
   Demo of how CPU time can exceed wall time in multithreaded programs.

   Simplified version of an example at
     https://en.cppreference.com/w/c/chrono/clock.html
*/

#include <stdio.h>
#include <stdlib.h>
#include <threads.h>
#include <time.h>

// the function f() does some time-consuming work
int f(void* thr_data)
{
    (void) thr_data;
    volatile double d = 0;
    for (int n = 0; n < 10000; ++n)
       for (int m = 0; m < 10000; ++m)
           d += d * n * m;
    return 0;
}
 
int main(void)
{
    struct timespec t1, t2;

    clock_gettime(CLOCK_MONOTONIC, &t1);
    clock_t start_time = clock();
 
    thrd_t thr1, thr2;
    thrd_create(&thr1, f, NULL);
    thrd_create(&thr2, f, NULL);
    thrd_join(thr1, NULL);
    thrd_join(thr2, NULL);

    clock_gettime(CLOCK_MONOTONIC, &t2);
    clock_t end_time = clock();
 
    double cpu_time = 1000.0 * (end_time - start_time) / CLOCKS_PER_SEC;

    double wall_time = 1000.0 * t2.tv_sec + 1e-6 * t2.tv_nsec
                         - (1000.0 * t1.tv_sec + 1e-6 * t1.tv_nsec);
 
    printf("CPU time used    : %.2f ms\n", cpu_time);
    printf("Wall time passed : %.2f ms\n", wall_time);
}
