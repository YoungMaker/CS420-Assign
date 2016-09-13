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
  int sfhandle = open(src_file, O_RDONLY);

  if(sfhandle < 0)
  {
    switch(errno) {
        case ENOENT:
          printErr("Source file or directory does not exist\n");
        break;
        case EACCES:
          printErr("Access to source file is denied\n");
        break;
    }
    printErr("Error opening file\n");
    exit(1);
  }

  // TODO
  // Determine the permission of the source file
  // Again, be sure to check for errors!
  struct stat  filestats;
  if(fstat(sfhandle, &filestats) < 0) {
    switch(errno) {
      case ENOENT:
        printErr("File or directory does not exist\n");
            break;
      case EACCES:
        printErr("Access to that file is denied\n");
            break;
    }
    printErr("Error reading file attributes\n");
    exit(1);
  }

  if(!S_ISREG(filestats.st_mode)) {
    printErr("Source filepath is a directory, not a file\n");
    exit(1);
  }

  // TODO
  // Open the destination file, be sure to apply appropriate permissions
  // BE SURE TO CHECK FOR ERRORS WHEN OPENING FILES
  // If an error occurs, report the error and terminate the program
  int dfhandle = open(dst_file, O_CREAT | O_WRONLY| O_TRUNC, filestats.st_mode);

  if(dfhandle < 0)
  {
    switch(errno) {
      case ENOENT:
        printErr("Dest file or directory does not exist\n");
            break;
      case EACCES:
        printErr("Access to dest file is denied\n");
            break;
    }
    printErr("Error opening file\n");
    exit(1);
  }

  // TODO
  // Output a status message here, something like
  // "Copying AAA to BBB"
  printStr("Copying file ");
  printStr(src_file);
  printStr(" to destination ");
  printStr(dst_file);
  printStr("\n");
  // TODO
  // Do the work to actually copy the file here
  // Be efficient and copy CHUNKS of data
  // DO NOT COPY ONE BYTE AT AT TIME
  // DO NOT READ THE ENTIRE FILE INTO MEMORY
  // Again, be sure to check for errors!
//    while(1){
//        if(read(sfhandle, data_buf, BUFFER_SIZE)< 0)
//        {
//            printErr("Error reading file \n");
//        }
//
//    }



  // TODO
  // Close the source and destination files here
  // As always, check for any errors that may be generated
  if(close(sfhandle) < 0 || close(dfhandle) < 0) {
    printErr("Error closing files\n");
    exit(1);
  }

  return 0;
}

int printStr(char *str)
{
    //TODO: write to STDOUT
    return write(STDOUT, str, strlen(str));
}

int printErr(char *str)
{
    //TODO: write to STDERR
    return write(STDERR, str, strlen(str));
}