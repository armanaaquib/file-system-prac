#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#include "fs.h"
#include "disc.h"

Open_File_Meta *open_file_in_sys(unsigned int mode, unsigned int offset, Metadata *metadata)
{
  Open_File_Meta *open_file = malloc(sizeof(Open_File_Meta));

  open_file->mode = mode;
  open_file->offset = offset;
  open_file->metadata = metadata;

  return open_file;
}

Open_File_Meta *fd_table[10];

int add_to_fd_table(Open_File_Meta *open_file)
{
  int i = -1;
  while (fd_table[++i])
    ;

  fd_table[i] = open_file;

  return i;
}

int aOpen(char *filename, unsigned int mode)
{
  Metadata *metadata = find_metadata(filename);

  if (!metadata)
  {
    metadata = create_metadata(ARW_MODE);
    add_metadata(metadata);
    add_fn_md(filename, metadata);
  }

  return add_to_fd_table(open_file_in_sys(mode, 0, metadata));
}

void aClose(int fd)
{
  free(fd_table[fd]);
  fd_table[fd] = NULL;
}

void aWrite(int fd, char *buffer, int size)
{
  Open_File_Meta *open_file = fd_table[fd];
  Metadata *metadata = open_file->metadata;

  if (metadata->mode < AW_MODE)
  {
    printf("write: permission denied\n");
  }

  if (open_file->mode < AW_MODE)
  {
    printf("Not opened in write mode\n");
  }

  unsigned int block_number = metadata->block_numbers[metadata->no_of_blocks - 1];
  unsigned int offset = open_file->offset;

  write_to_disc(block_number + offset, buffer, size);

  open_file->offset += size;
  metadata->last_modification = time(NULL);
  metadata->last_access = time(NULL);
}

void aRead(int fd, char *buffer, int size)
{
  Open_File_Meta *open_file = fd_table[fd];
  Metadata *metadata = open_file->metadata;

  if (metadata->mode == AW_MODE)
  {
    printf("read: permission denied\n");
  }

  if (open_file->mode == AW_MODE)
  {
    printf("Not opened in read mode\n");
  }

  unsigned int block_number = metadata->block_numbers[metadata->no_of_blocks - 1];
  unsigned int offset = open_file->offset;

  read_from_disc(block_number + offset, buffer, size);

  open_file->offset += size;
  metadata->last_modification = time(NULL);
  metadata->last_access = time(NULL);
}

void aResetOffset(int fd)
{
  fd_table[fd]->offset = SEEK_SET;
}
