#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

#define MAX_FILE_SIZE 1024
#define MAX_FILE_BLOCKS 1024 * 5

#define AR_MODE 0
#define AW_MODE 1
#define ARW_MODE 2

unsigned int next_free_file_block = 0;

typedef struct inode
{
  unsigned int block_number : 23;
  unsigned int size : 11;
  unsigned int mode : 3;
  time_t creation_time;
  time_t last_access;
  time_t last_modification;
} Inode;

Inode *inodes[MAX_FILE_BLOCKS];
int next_inode_idx = 0;

Inode *create_inode(unsigned int mode)
{
  Inode *inode = malloc(sizeof(Inode));

  inode->block_number = next_free_file_block;
  next_free_file_block += MAX_FILE_SIZE;

  inode->size = 0;
  inode->mode = mode;
  inode->creation_time = time(NULL);
  inode->last_access = time(NULL);
  inode->last_modification = time(NULL);

  return inode;
}

typedef struct file_inode
{
  char *filename;
  Inode *inode;
  struct file_inode *next;
} File_Inode;

File_Inode *first_fi = NULL;
File_Inode *last_fi = NULL;

Inode *find_inode(char *filename)
{
  File_Inode *p_walk = first_fi;

  while (p_walk)
  {
    if (strcmp(p_walk->filename, filename) == 0)
    {
      return p_walk->inode;
    }

    p_walk = p_walk->next;
  }

  return NULL;
}

File_Inode *create_fi(char *filename, Inode *inode)
{
  File_Inode *fi = malloc(sizeof(File_Inode));

  fi->filename = malloc(sizeof(char) * strlen(filename));
  strcpy(fi->filename, filename);

  fi->inode = inode;
  fi->next = NULL;

  return fi;
}

void add_fi(char *filename, Inode *inode)
{
  File_Inode *fi = create_fi(filename, inode);

  if (!first_fi)
  {
    first_fi = fi;
  }

  if (last_fi)
  {
    last_fi->next = fi;
  }

  last_fi = fi;
}

typedef struct open_file
{
  unsigned int mode : 3;
  unsigned int offset : 11;
  Inode *inode;
} Open_File;

Open_File *open_file_in_sys(unsigned int mode, unsigned int offset, Inode *inode)
{
  Open_File *open_file = malloc(sizeof(Open_File));

  open_file->mode = mode;
  open_file->offset = offset;
  open_file->inode = inode;

  return open_file;
}

Open_File *fd_table[10];

int add_to_fd_table(Open_File *open_file)
{
  int i = -1;
  while (fd_table[++i])
    ;

  fd_table[i] = open_file;

  return i;
}

int aOpen(char *filename, unsigned int mode)
{
  Inode *inode = find_inode(filename);

  if (!inode)
  {
    inode = create_inode(mode);
    inodes[next_inode_idx++] = inode;
    add_fi(filename, inode);
  }

  return add_to_fd_table(open_file_in_sys(mode, 0, inode));
}

void aClose(int fd)
{
  free(fd_table[fd]);
  fd_table[fd] = NULL;
}

void write_to_disc(int offset, char *buffer, int size)
{
  int fd = open("disc", O_WRONLY | O_EXCL);
  lseek(fd, offset, SEEK_SET);
  write(fd, buffer, size);
  close(fd);
}

void read_from_disc(int offset, char *buffer, int size)
{
  int fd = open("disc", O_RDONLY | O_EXCL);
  lseek(fd, offset, SEEK_SET);
  read(fd, buffer, size);
  close(fd);
}

void aWrite(int fd, char *buffer, int size)
{
  Open_File *open_file = fd_table[fd];
  Inode *inode = open_file->inode;

  if (inode->mode < AW_MODE)
  {
    perror("write: permission denied");
  }

  if (open_file->mode < AW_MODE)
  {
    perror("Not opened in write mode");
  }

  unsigned int block_number = inode->block_number;
  unsigned int offset = open_file->offset;

  write_to_disc(block_number + offset, buffer, size);

  open_file->offset += size;
  inode->last_modification = time(NULL);
  inode->last_access = time(NULL);
}

void aRead(int fd, char *buffer, int size)
{
  Open_File *open_file = fd_table[fd];
  Inode *inode = open_file->inode;

  if (inode->mode == AW_MODE)
  {
    perror("read: permission denied");
  }

  if (open_file->mode == AW_MODE)
  {
    perror("Not opened in read mode");
  }

  unsigned int block_number = inode->block_number;
  unsigned int offset = open_file->offset;

  read_from_disc(block_number + offset, buffer, size);

  open_file->offset += size;
  inode->last_modification = time(NULL);
  inode->last_access = time(NULL);
}

int main(void)
{
  fd_table[0] = NULL;

  int fd = aOpen("a.txt", AW_MODE);
  printf("%d\n", fd);

  aWrite(fd, "hello world", 11);

  // fd = aOpen("b.txt", AR_MODE);
  // printf("%d\n", fd);

  // aClose(fd);

  // fd = aOpen("c.txt", AW_MODE);
  // printf("%d\n", fd);

  return 0;
}
