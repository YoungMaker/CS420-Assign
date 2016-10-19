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

struct params {
    int thread_id;
    char* filename;
};
void *fileOperation(void *params);

int main(int argc, char** argv)
{
    int num_threads = 0;
    char* filename = NULL;

    if(argc != 3) {
        fprintf(stderr, "FileWriter %d: Not enough arguments\n", getpid());
    }

    num_threads = atoi(argv[1]);
    filename = argv[2];
    //printf("FileWriter %d: num threads: %d\n", getpid(), num_threads);
    //printf("FileWriter %d: Filename: %s\n", getpid(), filename);


    //spawn off t threads!
    pthread_attr_t attr; //thread attributes
    pthread_t pthread_ids[(num_threads-1)]; //array thread structs

    pthread_attr_init(&attr); //set default attributes
    struct params args[(num_threads-1)]; //array of structs for arguments to pthread runner function

    for(int i=0; i<num_threads; i++) {
        args[i].filename = filename; //set the correct arguments in the ith arg struct
        args[i].thread_id = i; //this is so we can ID the thread later.
        if(pthread_create(&pthread_ids[i], &attr, fileOperation, &args[i]) <0) //create thread, send in arg struct
        {
            fprintf(stderr, "FileWriter %d: Error creating thread!\n", getpid());
            return -1;
        }
    }
    //wait for all threads to complete
    for(int i=0; i<num_threads; i++) {
     pthread_join(pthread_ids[i], NULL);
    }
    printf("Filewriter %d: all threads should now be closed.\n", getpid());
    return 0;
}

void *fileOperation(void *params) {
    sem_t *semo;
    struct params *args = (struct params*)(params);
    if((semo = sem_open("awalsh6", O_RDONLY)) < 0) {
        fprintf(stderr, "FileWriter %d: Error getting semaphore named awalsh6", getpid());
        void *exit = (void *)(-1);
        pthread_exit(exit); //how to exit non-cleanly? -1 is an error. Trying this?
    }
    //printf("Thread %d is running, filename is %s\n", args->thread_id, args->filename);
    //use sem_wait to gain access to the &filename resource. Decrement this semaphore
    if(sem_wait(semo) <0) {
        fprintf(stderr, "FileWriter %d: Error calling sem_wait", getpid());
    } //we should now have exclusive access to the &filename resource
    //all calls to exit the thread should now sem_post
    //open file handle
    FILE *fhandle = open_file(args->filename, "a+cat ");
    printf("Filewriter process %d, thread %d now has access to the file\n", getpid(), args->thread_id);

    int num = 0;
    fseek(fhandle, 0L, SEEK_END);
    //printf("FileWriter process %d, thread %d the file is %ld bytes long\n", getpid(), args->thread_id, ftell(fhandle));
    if(ftell(fhandle) > 2) {
        //TODO: traverse using fseek to the last line of the file.
        fseek(fhandle, -2L, SEEK_END); //seek to one character before the last '\n', so that we do not immediately fgetc the last '\n'
        int cur = fgetc(fhandle); //this traverses one forward!
        while(cur != '\n' && ftell(fhandle) > 2 ) {//greater than 0? greater than 2? what is the edge case where we can't find a '\n'?
            fseek(fhandle, -2L, SEEK_CUR); //traverse two back, this is only if the char read in was not a '\n'
            cur = fgetc(fhandle); //read and traverse one forward
            //printf("Filewriter %d, thread %d found char %c at location %ld\n", getpid(), args->thread_id, cur, ftell(fhandle));
        }
        //we have now found a'\n' char, now read from the location (which should be just one head of the '\n' if I am correct.
        fscanf(fhandle, "%d", &num); //read in the next int.
    }
    //if the file just contains 2 bytes (0\n) we don't need to read anything. All we have to do is increment and print.
    //increment and store new number
    num++;
    fprintf(fhandle, "%d", num);
    fprintf(fhandle, "\n");


    //close file

    close_file(fhandle);
    //increment semaphore to release hold on filename resource

    sem_post(semo);
    //exit thread cleanly.

    pthread_exit(0);
}
