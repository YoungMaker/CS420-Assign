#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include "ipcEx.h"


int main(int argc, char** argv)
{

  /* Print out usage statement when no value is specified */
  if (argc != 2) {
    fprintf(stderr, "PARENT: You must specify an integer value as an argument\n");
    return 1;
  }

  int mem_key = shmget(IPC_PRIVATE, sizeof(struct ipc_struct), S_IRUSR | S_IWUSR); //opens private shared memory with user read and write privileges
  if(mem_key < 0 ) {
    fprintf(stderr,"PARENT: Error allocating shared sh memory\n");
    return -1; //quit, fatal error
  }
  printf("PARENT: Created shared memory with segment id %d \n", mem_key);

  struct ipc_struct* shared_mem = (struct ipc_struct*) shmat(mem_key, NULL, 0);
  if(shared_mem < 0) {
    fprintf(stderr, "PARENT: Error attaching to shared memory\n");
    return -1;
  }

  int repeat_times;
  sscanf(argv[1], "%d", &repeat_times);
  shared_mem->repeat_val =  repeat_times;

  //okay, we have a hold on our shared memory, now lets fork off

  int pid = fork();

  if(pid < 0) {
    fprintf(stderr, "PARENT: Fork failed\n");
    return -1; //quit, fatal error
  }
  else if(pid == 0) {
    //we are now in the child process. execlp() to start the childproc
    int len = snprintf(NULL, 0, "%i", mem_key); //calculates char length of mem_key
    char mem_key_str[len];// = malloc((size_t)len); //creates a char array with length the same as the amount of chars in mem_key
    sprintf(mem_key_str, "%i", mem_key);

    if(execlp("./childProc", "childProc", mem_key_str, (char *)NULL) < 0) {
      fprintf(stderr, "CHILD: Error replacing process with childProc\n");
      return -1;
    }
  }
  else {
    //fork has executed correctly and we are still in the parent process
    wait(NULL); //wait for the child process to finish executing.
    //todo: retrieve the data stored in shared memory, print.
    printf("PARENT: child process with pid=%d complete\n", pid);
    printf("PARENT: =================  BUFFER START =================\n");

    for(int i=0; i<BUFFER_SIZE; i++) {
      printf("%c", shared_mem->data[i]);
    }
    printf("PARENT: ================= BUFFER END =================\n");

    if(shmdt(shared_mem) < 0) { //detach from mem
      fprintf(stderr, "PARENT: Error detaching from shared memory.\n");
    }
    if(shmctl(mem_key, IPC_RMID, NULL)< 0) { //mark shared memory segment for removal
      fprintf(stderr, "PARENT: Error marking memory segment for removal\n");
    }
  }

  return 0;
}

