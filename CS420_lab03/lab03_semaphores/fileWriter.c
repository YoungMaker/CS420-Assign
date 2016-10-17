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


void *fileOperation(void *params);
struct params {
    int thread_id;
    char* filename;
};

int main(int argc, char** argv)
{
    int num_threads = 0;
    char* filename = NULL;

    if(argc != 3) {
        fprintf(stderr, "FileWriter %d: Not enough arguments\n", getpid());
    }

    num_threads = atoi(argv[1]);
    filename = argv[2];
    printf("FileWriter %d: num threads: %d\n", getpid(), num_threads);
    printf("FileWriter %d: Filename: %s\n", getpid(), filename);


    //TODO: spawn off t threads!
    pthread_attr_t attr; //thread attributes
    pthread_t pthread_ids[num_threads];

    pthread_attr_init(&attr); //set default attributes
    struct params args[num_threads];
    for(int i=0; i<num_threads; i++) {
        args[i].filename = filename;
        args[i].thread_id = i;
        if(pthread_create(&pthread_ids[i], &attr, fileOperation, &args[i]) <0)
        {
            fprintf(stderr, "FileWriter %d: Error creating thread!\n", getpid());
            return -1;
        }
    }
    //TODO: wait for all threads to complete
    for(int i=0; i<num_threads; i++) {
     pthread_join(pthread_ids[i], NULL);
    }

    return 0;
}

void *fileOperation(void *params) {
//    sem_t *semo;
    struct params *args = (struct params*)(params);
//    if((semo = sem_open("awalsh6", O_EXCL)) < 0) {
//        fprintf(stderr, "FileWriter %d: Error getting semaphore named awalsh6", getpid());
//        void *exit = (void *)(-1);
//        pthread_exit(exit); //how to exit non-cleanly? -1 is an error. Trying this?
//    }
    printf("Thread %d is running, filename is %s\n", args->thread_id, args->filename);
    //TODO: use sem_wait to gain access  to the &filename resource. Decrement this semaphore
//    if(sem_wait(semo) <0) {
//        fprintf(stderr, "FileWriter %d: Error calling sem_wait", getpid());
//    } //we should now have exclusive access to the &filename resource
//
    //TODO: open file and traverse using fseek to the last line of the file.
//    FILE *fhandle
    //TODO: read the last line of the file and convert to integer (atoi()?)

    //TODO: increment and write out to the last line of the file

    pthread_exit(0);
}