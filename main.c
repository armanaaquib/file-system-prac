#include <stdio.h>
#include <stdlib.h>
#include "fs.h"

int main(void)
{
  int fd0 = aOpen("a.txt", ARW_MODE);
  aWrite(fd0, "file1 content\n", 14);
  aWrite(fd0, "file1 content2", 14);

  int fd1 = aOpen("b.txt", ARW_MODE);
  aWrite(fd1, "file2 content", 13);
  aWrite(fd1, "file2 content2", 14);

  char *buffer = malloc(50);

  aResetOffset(fd1);
  aRead(fd1, buffer, 28);
  printf("%s\n", buffer);
  aClose(fd1);

  aResetOffset(fd0);
  aRead(fd0, buffer, 28);
  printf("%s\n", buffer);
  aClose(fd0);

  fd0 = aOpen("a.txt", AW_MODE);
  aWrite(fd0, "over written content", 20);
  aClose(fd0);

  fd0 = aOpen("a.txt", AR_MODE);
  char *buff = malloc(50);
  aRead(fd0, buff, 28);
  printf("%s\n", buff);
  aClose(fd0);

  int fd2 = aOpen("c.txt", AW_MODE);
  aWrite(fd2, "Hello World!", 12);
  aClose(fd2);

  fd0 = aOpen("a.txt", AR_MODE);
  fd1 = aOpen("b.txt", AR_MODE);
  fd2 = aOpen("c.txt", AR_MODE);

  char *buff1 = malloc(50);
  aRead(fd0, buff1, 28);
  printf("%s\n", buff1);

  char *buff2 = malloc(50);
  aRead(fd1, buff2, 20);
  printf("%s\n", buff2);

  char *buff3 = malloc(50);
  aRead(fd1, buff3, 8);
  printf("%s\n", buff3);

  char *buff4 = malloc(50);
  aRead(fd2, buff4, 12);
  printf("%s\n", buff4);

  aClose(fd0);
  aClose(fd1);
  aClose(fd2);

  return 0;
}
