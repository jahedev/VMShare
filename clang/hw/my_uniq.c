#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> // bool -- true/false values
#include <string.h> // comparing buffers with strcmp - stands for string compare
#include <fcntl.h> // this is for the open() system call
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h> // this is for read() and write() system calls
#include <errno.h>


#define MAX_STRING_LENGTH 500

extern int errno;


// ./my_uniq [inputfile] [outputfile]


// reads a line from file fd and writes to buffer. 
// return the number of characters read, minus newline
int read_line(int fd, char * buffer){
  int count = 0;
  int ret; 
  
  ret = read(fd, buffer, 1);

  if (ret == -1){
	perror("Read call failed");
    exit(EXIT_FAILURE);
  } else if (ret == 0){
   	// nothing to read, so exit
    return count;
  }

  // check if initial character is a new line
  bool lineIsEmpty = (*buffer == '\n');

  while( ret == 1 && (*buffer != '\n' || lineIsEmpty)){
    lineIsEmpty = false;
   	 buffer++;
     count++;
     if (count > MAX_STRING_LENGTH){
        errno = ENOBUFS; /* No buffer space available */
      	perror("Maximum line length exceeded!");
        exit(EXIT_FAILURE);
     }
     ret = read(fd, buffer, 1);
  }
  
  *buffer = '\0';
  return count;
}

char cur_arg[1024];

int main(int argc, char * argv[]){
 	 int in_fd, out_fd, ret;
  	 
  	 switch(argc){
       case 1:
         in_fd = STDIN_FILENO;
         out_fd = STDOUT_FILENO;
         break;
       case 2:
         if (strcmp(argv[1], "-c") == 0){
          	 in_fd = STDIN_FILENO;
         } else {
          	 in_fd = open(argv[1], O_RDONLY);
           	 if (in_fd == -1){ 
              	perror("open failed!");
                exit(EXIT_FAILURE);
             }
         }
         out_fd = STDOUT_FILENO;
         break;
       case 3:
         // input file is equal to dash
         if (strcmp(argv[1], "-") == 0){
          	 in_fd = STDIN_FILENO;
         } else {
          	 in_fd = open(argv[1], O_RDONLY);
           	 if (in_fd == -1){ 
              	perror("open failed!");
                 exit(EXIT_FAILURE);
             }
         }
         
         // output file is equal to dash
         if (strcmp(argv[2], "-") == 0){
          	 out_fd = STDOUT_FILENO;
         } else {
          	 out_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
           	 if (out_fd == -1){ 
              	perror("open failed!");
                exit(EXIT_FAILURE);
             }
         }
         break;
       default:
         perror("too many command line arguments!");
         exit(EXIT_FAILURE);
         break;
         // print an error: too many command line arguments.
         // exit
     }
  	 //char buffer1[MAX_STRING_LENGTH];
  	 char * buffer1 = malloc(MAX_STRING_LENGTH + 1);
     char * buffer2 = malloc(MAX_STRING_LENGTH + 1);
  	 
  	 // read first line of input
  	 ret = read_line(in_fd, buffer1);
  	 // check return value here for errors or 0 (empty file)
     // write first line to output, because there cannot yet be a duplicate
  	 ret = write(out_fd, buffer1, ret);
  
     if (ret == -1){
      	perror("write failed!");
        exit(EXIT_FAILURE);
     }
     write(out_fd, "\n", 1);
  
  	// read next line of input into buffer2
  	ret = read_line(in_fd, buffer2);
  	
  	 while (strlen(buffer2) > 0 && ret != 0){
      	// are buffers unique?
        if (strcmp(buffer1, buffer2) != 0){
         	 // write content of buffer 2 to the output
             ret = write(out_fd, buffer2, ret);
             if (ret == -1){
              	perror("write failed!");
        	    exit(EXIT_FAILURE); 
             }

             // only write to output if last output was not a new line character
             if (strcmp(buffer2, "\n") != 0) write(out_fd, "\n", 1);

             // error check value of return just to be save
             char * temp = buffer1;
             // swapping buffers
             buffer1 = buffer2;
             buffer2 = temp;
        }
        ret = read_line(in_fd, buffer2);
        // error check return again for sanity's sake
     }
     // free aquired resources
	  close(in_fd);
	  close(out_fd);
	  free(buffer1);
	  free(buffer2);
	  // exit gracefully
	  return EXIT_SUCCESS;
}
