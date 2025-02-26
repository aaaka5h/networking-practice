#include "compute.h"

#include <stddef.h>
#include <stdio.h>
#include <pthread.h>

#define N 6

struct compute_item {
    int input;
    int output;
};

static void *task(void *data) {
    struct compute_item *item = data;
    item->output = compute(item->input);
}

struct mutation_item {
    int input;
    pthread_mutex_t *mutex;
    long *output;
};

static void *mutate_task(void *data) {
    struct mutation_item *item = data;
    int result = compute(item->input);
    pthread_mutex_lock(item->mutex);
    *(item->output) += result;
    pthread_mutex_unlock(item->mutex);
}

int main() {
    // Serial version ---------------------------------------------------------
    long result = 0;
    for (int i = 0; i < N; ++i) {
        result += compute(i);
    }
    printf("serial: %ld\n", result);

    // Run all computations, one per thread -----------------------------------
    struct compute_item items[N];
    pthread_t threads[N];

    /* Problem 1: Your goal is to rewrite the serial computation above using
     * threads - specifically with the pthread library.
     * Start by creating one thread per call to compute. When all threads
     * finish execution, sum up the results.
     *
     * You might find `struct compute_item` and `task()` useful for this task,
     * although you may write your own variants.
     *
     * Documentation: https://man.archlinux.org/man/pthreads.7#SEE_ALSO */
     long result2 = 0;
     for (int i = 0; i < N; ++i) {
         items[i].input = i;
         pthread_create(&threads[i], NULL, task, &items[i]);
     }

    for (int i = 0; i < N; ++i) {
        pthread_join(threads[i], NULL);
        result2 += items[i].output;
    }

    printf("parallel: %ld\n", result2);

    // Run all computations but increment the result as soon as the processing-
    // is finished ------------------------------------------------------------
    struct mutation_item mut_items[N];
    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, NULL);
    long result3 = 0;

    /* Problem 2: This task is the same as problem 1, except we now add each
     * element to the result as soon as the computation is finished, instead
     * of waiting for all the threads to finish. One way of doing this is to
     * guard the memory accesses to the result variable using a mutex.
     *
     * You might find `struct mutation_item` and `mutate_task` useful!
     */
    for (int i=0; i<N; ++i) {
        mut_items[i].input = i;
        mut_items[i].mutex = &mutex;
        mut_items[i].output = &result3;
        pthread_create(&threads[i], NULL, mutate_task, &mut_items[i]);
    }

    for (int i=0; i<N; ++i) {
        pthread_join(threads[i], NULL);
    }
    
    pthread_mutex_destroy(&mutex);
    printf("parallel: %ld\n", result3);

     /* Bonus: If you have made it this far, read on! One way to know if your
      * multithreaded code is thread-safe is to use a tool like valgrind. Build
      * your executable and run it under valgrind using
      * `valgrind --tool=helgrind ./path/to/binary` */
    return 0;
}
