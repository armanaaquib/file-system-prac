#include <string.h>
#include <stdlib.h>

#include "metadata.h"

Fn_Md *first_fi = NULL;
Fn_Md *last_fi = NULL;

char blocks_info[NO_OF_BLOCKS];
Metadata *all_metadata[NO_OF_BLOCKS];
int next_metadata_idx = 0;

int get_free_block_number()
{
  for (size_t i = 0; i <= NO_OF_BLOCKS; i++)
  {
    if (blocks_info[i] != 1)
    {
      return i;
    }
  }

  return -1;
}

unsigned *add_block_number(unsigned *block_numbers, unsigned short no_of_blocks, unsigned new_block)
{
  unsigned *new_block_numbers = malloc(sizeof(unsigned) * (no_of_blocks + 1));

  for (size_t i = 0; i < no_of_blocks; i++)
  {
    new_block_numbers[i] = block_numbers[i];
  }

  new_block_numbers[no_of_blocks] = new_block;

  return new_block_numbers;
}

Metadata *create_metadata(unsigned int mode)
{
  Metadata *metadata = malloc(sizeof(Metadata));

  unsigned free_block = get_free_block_number();
  metadata->block_numbers = add_block_number(metadata->block_numbers, 0, free_block);
  metadata->no_of_blocks = 1;
  blocks_info[free_block] = 1;

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
