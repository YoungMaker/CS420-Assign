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


  // TODO:
  // Insert your code here



  return 0;
}

