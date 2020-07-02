#include <time.h>

#ifndef __METADATA_H_
#define __METADATA_H_

#define MAX_FILE_BLOCKS 1024 * 5
#define MAX_FILE_SIZE 1024

typedef struct metadata
{
  unsigned int block_number : 23;
  unsigned int size : 11;
  unsigned int mode : 3;
  time_t creation_time;
  time_t last_access;
  time_t last_modification;
} Metadata;

typedef struct fn_md
{
  char *filename;
  Metadata *metadata;
  struct fn_md *next;
} Fn_Md;

Metadata *create_metadata(unsigned int mode);
void add_metadata(Metadata *metadata);
Metadata *find_metadata(char *filename);
Fn_Md *create_fn_md(char *filename, Metadata *metadata);
void add_fn_md(char *filename, Metadata *metadata);

#endif
