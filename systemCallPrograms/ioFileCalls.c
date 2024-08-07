#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 30
#define FILE_PATH "example.txt"

int main()
{
      int fd = open(FILE_PATH, O_RDWR);
      if (fd == -1)
      {
            printf("failed to open file.\n");
            exit(1);
      }

      char buffer[BUFFER_SIZE];
      int n;

      printf("File Descriptor is %d \n", fd);

      // reading first 10 char
      printf("reading 10 characters form the file : \n");
      n = read(fd, buffer, 10);
      write(STDOUT_FILENO, buffer, n);
      printf("\n");

      // skipping 5 char
      printf("Skipping 5 characters form the current position in the fil e: \n");
      lseek(fd, 5, SEEK_CUR);
      n = read(fd, buffer, 10);
      write(STDOUT_FILENO, buffer, n);
      printf("\n");

      // going to 10 characters before the current position
      printf("going to 10 characters before the current position in the fil e; \n");
      lseek(fd, -10, SEEK_CUR);
      n = read(fd, buffer, 10);
      write(STDOUT_FILENO, buffer, n);
      printf("\n");

      // going to 5th char
      printf("going to 5th character in the file\n");
      lseek(fd, -5, SEEK_END);
      n = read(fd, buffer, 5);
      write(STDOUT_FILENO, buffer, n);
      printf("\n");

      // going to 3rd character
      printf("going to 3d char in the file\n");
      lseek(fd, 3, SEEK_SET);
      n = read(fd, buffer, 5);
      write(STDOUT_FILENO, buffer, n);
      printf("\n");

      close(fd);

      return 0;
}