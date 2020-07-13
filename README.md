# file-system-prac

```
  int fd0 = aOpen("a.txt", ARW_MODE);
  aWrite(fd0, "file1 content", 13);
  aWrite(fd0, "file1 content2", 14);

  int fd1 = aOpen("b.txt", ARW_MODE);
  aWrite(fd1, "file2 content", 13);
  aWrite(fd1, "file2 content2", 14);

  char *buffer = calloc(50, 1);
  aResetOffset(fd1);
  aRead(fd1, buffer, 27);
  printf("%s\n", buffer);
  aClose(fd1);

  free(buffer);
  buffer = calloc(50, 1);
  aResetOffset(fd0);
  aRead(fd0, buffer, 27);
  printf("%s\n", buffer);
  aClose(fd0);
  
  fd0 = aOpen("a.txt", AW_MODE);
  aWrite(fd0, "over writes content", 19);
  aClose(fd0);
  
  free(buffer);
  buffer = calloc(50, 1);
  aResetOffset(fd0);
  aRead(fd0, buffer, 50);
  printf("%s\n", buffer);
  aClose(fd0);
```
