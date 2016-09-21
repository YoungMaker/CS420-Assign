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
    printf("You must specify an integer value as an argument\n");
    return 1;
  }

  val mem_key = smget(sizeof(struct ipc_struct));

  if(mem_key < 0 ) {
    printf("Error allocating shared shmemory");
    return -1;
  }

  struct ipc_struct* shared_mem = (struct ipc_struct*) shmat(mem_key);


  return 0;
}

