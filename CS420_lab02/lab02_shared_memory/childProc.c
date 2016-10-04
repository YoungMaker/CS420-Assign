#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>
#include "ipcEx.h"


int main(int argc, char** argv)
{
  char data_string[] = "Hello Shared Memory!\n";

  // TODO:
  // Insert your code here
  if(argc != 2) {
    fprintf(stderr, "CHILD: incorrect argument length\n");
    return -1;
  }
  printf("CHILD: received 2 arguments\n");

  int mem_key;
  sscanf(argv[1], "%d", &mem_key);

  printf("CHILD: attempting to access segment ID %d\n", mem_key);
  struct ipc_struct *shared_memory = (struct ipc_struct*) shmat(mem_key, NULL, 0);
  if(shared_memory < 0) {
    fprintf(stderr, "CHILD: Error attaching to shared memory\n");
  }

  printf("CHILD: parent requested that I store my data %d times \n", shared_memory->repeat_val);
  int len =0;
  for(int i=0; i< shared_memory->repeat_val; i++) {
    len += sprintf(shared_memory->data + len, "%s", data_string);
  }

  if(shmdt(shared_memory) < 0 ) {
    fprintf(stderr, "CHILD: Error detaching from shared memory segment");
  }

  return 0;
}



