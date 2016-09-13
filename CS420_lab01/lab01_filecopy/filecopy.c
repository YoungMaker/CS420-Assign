#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <strings.h>
#include <sys/stat.h>
#include <errno.h>

#define STDIN  0
#define STDOUT 1
#define STDERR 2

#define BUFFER_SIZE 256


int printStr(char *str);
int printErr(char *str);

int main(int argc, char** argv)
{
  char *src_file, *dst_file;
  char data_buf[BUFFER_SIZE];

  // TODO
  // Declare any other variables
  // you may need here

  // verify the user has supplied the correct number of arguments
  // and assign source and destination file names
  if (argc != 3) {
    printErr("Error: Incorrect number of arguments\n");
    exit(-1);
  } else {

    // TODO
    // Make appropriate assignments if correct
    // number of arguments were supplied
    src_file = argv[1];
    dst_file = argv[2];
  }



  // TODO
  // Open the source file, be sure to apply appropriate permissions
  // BE SURE TO CHECK FOR ERRORS WHEN OPENING FILES
  // If an error occurs, report the error and terminate the program
  int fhandle = open(src_file, O_RDONLY);

  if(fhandle < 0)
  {
    switch(errno) {
        case ENOENT:
          printErr("File or directory does not exist\n");
        break;
        case EACCES:
          printErr("Access to that file is denied\n");
        break;
    }
    printErr("Error opening file\n");
    exit(1);
  }

  // TODO
  // Determine the permission of the source file
  // Again, be sure to check for errors!

  // TODO
  // Open the destination file, be sure to apply appropriate permissions
  // BE SURE TO CHECK FOR ERRORS WHEN OPENING FILES
  // If an error occurs, report the error and terminate the program



  // TODO
  // Output a status message here, something like
  // "Copying AAA to BBB"

 

  // TODO
  // Do the work to actually copy the file here
  // Be efficient and copy CHUNKS of data
  // DO NOT COPY ONE BYTE AT AT TIME
  // DO NOT READ THE ENTIRE FILE INTO MEMORY
  // Again, be sure to check for errors!



  // TODO
  // Close the source and destination files here
  // As always, check for any errors that may be generated


  return 0;
}

int printStr(char *str)
{
    //TODO: write to STDOUT
    return write(STDOUT, str, strlen(str));
}

int printErr(char *str)
{
    //TODO: write to STDOUT
    return write(STDERR, str, strlen(str));
}