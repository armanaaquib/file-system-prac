#include <string.h>
#include <stdlib.h>

#include "metadata.h"

Fn_Md *first_fi = NULL;
Fn_Md *last_fi = NULL;

Metadata *all_metadata[MAX_FILE_BLOCKS];
int next_metadata_idx = 0;

unsigned int next_free_file_block = 0;

Metadata *create_metadata(unsigned int mode)
{
  Metadata *metadata = malloc(sizeof(Metadata));

  metadata->block_number = next_free_file_block;
  next_free_file_block += MAX_FILE_SIZE;

  metadata->size = 0;
  metadata->mode = mode;
  metadata->creation_time = time(NULL);
  metadata->last_access = time(NULL);
  metadata->last_modification = time(NULL);

  return metadata;
}

void add_metadata(Metadata *metadata)
{
  all_metadata[next_metadata_idx++] = metadata;
}

Metadata *find_metadata(char *filename)
{
  Fn_Md *p_walk = first_fi;

  while (p_walk)
  {
    if (strcmp(p_walk->filename, filename) == 0)
    {
      return p_walk->metadata;
    }

    p_walk = p_walk->next;
  }

  return NULL;
}

Fn_Md *create_fn_md(char *filename, Metadata *metadata)
{
  Fn_Md *fi = malloc(sizeof(Fn_Md));

  fi->filename = malloc(sizeof(char) * strlen(filename));
  strcpy(fi->filename, filename);

  fi->metadata = metadata;
  fi->next = NULL;

  return fi;
}

void add_fn_md(char *filename, Metadata *metadata)
{
  Fn_Md *fi = create_fn_md(filename, metadata);

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
