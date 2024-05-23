#include "block.h"
#include "image.h"
#include "free.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

unsigned char block_map[BLOCK_SIZE];

unsigned char *bread(int block_num, unsigned char *block)
{
  int offset = block_num * BLOCK_SIZE;
  lseek(image_fd, offset, SEEK_SET);
  read(image_fd, block, BLOCK_SIZE);
  return block;
}
void bwrite(int block_num, unsigned char *block)
{
  int offset = block_num * BLOCK_SIZE;
  lseek(image_fd, offset, SEEK_SET);
  write(image_fd, block, BLOCK_SIZE);
}

int alloc(void)
{

  bread(BLOCK_MAP_BLOCK, block_map);

  int free_data = find_free(block_map);

  if (free_data == -1)
  {
    return -1;
  }

  set_free(block_map, free_data, 0);

  bwrite(BLOCK_MAP_BLOCK, block_map);

  return free_data;
}