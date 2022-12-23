#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


struct someArgs {
    int *arr;
    size_t start;
    size_t finish;
    int res;
};

void* calcul(void* args) {
    struct someArgs* tmp = (struct someArgs*) args;
    for (size_t i = tmp->start; i < tmp->finish; i++) {
        tmp->res += tmp->arr[i];
    }

    return (void*) args;
}

int main(int argc, char **argv) {

    pthread_t threads[4];
    struct someArgs someArgs[4];
    int status;
    struct someArgs *res_addr;
    int res = 0;

    int arr[20];
    for (size_t i = 0; i < 20; i++) {
        arr[i] = i;
    }

    size_t start = 0;

    for (size_t i = 0; i < 4; i++) {
        someArgs[i].arr = arr;
        someArgs[i].start = start;
        someArgs[i].finish = start + 5;
        someArgs[i].res = 0;
        start += 5;
    }

    for (size_t i = 0; i < 4; i++) {
        status = pthread_create(&threads[i], NULL, calcul, (void*) &someArgs[i]);
        if (status != 0) {
            printf("main error: can't create thread, status = %d\n", status);
            exit(-1);
        }
    }


    for (size_t i = 0; i < 4; i++) {
        status = pthread_join(threads[i], (void**)&res_addr);
        if (status < 0) {
            printf("main error: can't join thread, status = %d\n", status);
            exit(-1);
        }
        res += res_addr->res;
    }

    printf("%d", res);

    return 0;
}