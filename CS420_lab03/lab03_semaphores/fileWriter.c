#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <semaphore.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "utils.h"



int main(int argc, char** argv)
{
    int num_threads = 0;
    sem_t semo;
    char* filename = NULL;

    if(argc != 4) {
        fprintf(stderr, "FileWriter %d: Not enough arguments\n", getpid());
    }
    printf("FileWriter %d: semo: %s\n", getpid(), argv[1]);
    num_threads = atoi(argv[2]);
    printf("FileWriter %d: num threads: %d\n", getpid(), num_threads);

    return 0;
}