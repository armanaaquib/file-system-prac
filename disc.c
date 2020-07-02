#include <unistd.h>
#include <fcntl.h>
#include "disc.h"

void write_to_disc(int offset, char *buffer, int size)
{
  int fd = open("disc", O_WRONLY);
  lseek(fd, offset, SEEK_SET);
  write(fd, buffer, size);
  close(fd);
}

void read_from_disc(int offset, char *buffer, int size)
{
  int fd = open("disc", O_RDONLY);
  lseek(fd, offset, SEEK_SET);
  read(fd, buffer, size);
  close(fd);
}
