#include "metadata.h"

#ifndef __FS_H_
#define __FS_H_

#define AR_MODE 0
#define AW_MODE 1
#define ARW_MODE 2

int aOpen(char *filename, unsigned int mode);
void aClose(int fd);
void aWrite(int fd, char *buffer, int size);
void aRead(int fd, char *buffer, int size);
void aResetOffset(int fd);

typedef struct open_file_meta
{
  unsigned int mode : 3;
  unsigned int offset : 11;
  Metadata *metadata;
} Open_File_Meta;

#endif
