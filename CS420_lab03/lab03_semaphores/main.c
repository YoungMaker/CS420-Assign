#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include "utils.h"



int main(int argc, char** argv)
{
    char* filename = NULL;  // DO NOT MODIFY THIS VARIABLE NAME
    int num_procs = 0;      // DO NOT MODIFY THIS VARIABLE NAME
    int num_threads = 0;    // DO NOT MODIFY THIS VARIABLE NAME
    char* thread_amt = NULL;  // store thread num as char* to make passing it into fileWriter.c via execlp easier



    // TODO: parse arguments

    if(argc != 7 ) {
        fprintf(stderr, "USAGE : ./main -p <num_procs> -t <num_threads> -f <filename>\n"
                " -p : the number of processes to create\n"
                " -t : the number of threads to create per process\n"
                " -f : the name of the shared file in which to write output\n");
        return -1; //exit program here, we do not have correct amount of args.
    }

    int opt;
    while((opt = getopt(argc, argv, "p:t:f:")) != -1) {
        switch(opt) {
            case 'p':
                //todo: handle num processes
                num_procs = atoi(optarg);
                printf("MAIN: num processes is %d\n", num_procs);
                break;
            case 't':
                //todo: handle num threads
                thread_amt = optarg;
                num_threads = atoi(optarg);
                printf("MAIN: num threads is %d\n", num_threads);
                break;
            case 'f':
                //todo: handle filename
                filename = optarg;
                printf("MAIN: File name is %s\n", filename);
                break;
            case '?':
                fprintf(stderr, "USAGE : ./main -p <num_procs> -t <num_threads> -f <filename>\n"
                        " -p : the number of processes to create\n"
                        " -t : the number of threads to create per process\n"
                        " -f : the name of the shared file in which to write output\n");
                return -1; //exit program here, we have incorrect args.
            default:
                //what is going on here?
                break;
        }
    }
    
    
    // TODO: write initial '0' to file
    FILE *fhandle = open_file(filename, "w");
    fprintf(fhandle, "0\n");
    close_file(fhandle);
    

    // TODO: create a named semaphore
    //TODO: From this point an, all termination paths MUST close semo
    sem_t *semo = sem_open("awalsh6", O_CREAT);
    
    // TODO: fork off child processes and wait for them to finish- send them the sem, num threads, and the file name.
    int pid;
    for(int i= 0; i< num_procs; i++) {
        pid = fork();
        if(pid == 0) {
           execlp("./fileWriter", "fileWriter", thread_amt, filename, NULL);
        }
        if(pid < 0 ) {
            //todo: exit, clean sem.
            if(sem_close(semo)<0) {
                fprintf(stderr, "MAIN: could not close semaphore!");
            }
        }
    }

    wait(NULL);
    
    // TODO: clean up and close named semaphore
    sem_close(semo);
    
    
    
    
    
    
    /////////////////////////////////////////////////////////////////////////////////////
    //
    // ** IMPORTANT: DO NOT REMOVE/CHANGE/MODIFY/EDIT OR DO ANYTHING TO THE CODE BETWEEN
    //               HERE AND THE END OF THIS FILE.  YOU CANNOT CHANGE THIS CODE TO MAKE
    //               IT WORK WITH YOUR PROGRAM.  IF YOUR PROGRAM DOESN'T WORK WITH THIS
    //               CODE, THEN YOUR PROGRAM -DOES NOT WORK-.  CHANGE YOUR PROGRAM AS
    //               NECESSARY TO WORK WITH THIS CODE.  ANY CHANGES TO THE CODE BELOW WILL
    //               RESULT IN 0 CREDIT FOR THIS LAB.  BE SURE ALL OF YOU CHILD PROCESSES
    //               HAVE TERMINATED BEFORE THIS POINT.
    //
    /////////////////////////////////////////////////////////////////////////////////////
    // This section checks the output file to see if everthing went as planned.  A message
    // is printed to the terminal indicated if everything works correctly.
    /////////////////////////////////////////////////////////////////////////////////////
    FILE* fpt = open_file(filename, "r");   // open the file for reading
    int max_value = num_procs * num_threads;
    int value;
    int success = 1;
    
    // The following loop will read the file after it has been written by all of the
    // child processes and threads.  It will read each line and compare it to the
    // expected value.  If an error is encoutered, the 'success' flag will be set
    // to false.
    for (int expected_value=0; expected_value <= max_value; expected_value++) {
        fscanf(fpt, "%i", &value);
        if (expected_value != value) {
            success = 0;
            break;
        }
    }
    close_file(fpt);                        // close the file
    
    
    if (success) {
        printf("\n\n-SUCCESS-\n\n");
    } else {
        printf("\n\n-EPIC FAIL-\n\n");
    }
    /////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////
    
    return 0;
}

