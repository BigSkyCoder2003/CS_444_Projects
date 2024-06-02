#include "block.h"
#include "image.h"
#include "free.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

unsigned char *bread(int block_num, unsigned char *block)
{
  int offset = block_num * BLOCK_SIZE;
  lseek(image_fd, offset, SEEK_SET);
  /*int n = */ read(image_fd, block, BLOCK_SIZE);
  // printf("n: %d\n", n);
  return block;
}
void bwrite(int block_num, unsigned char *block)
{
  // printf("111block_num: %d\n", block_num);
  int offset = block_num * BLOCK_SIZE;
  lseek(image_fd, offset, SEEK_SET);
  write(image_fd, block, BLOCK_SIZE);
}

int alloc(void)
{
  unsigned char block_map[BLOCK_SIZE];

  bread(BLOCK_MAP_BLOCK, block_map);

  int free_data = find_free(block_map);
  // printf("free_data: %d\n", free_data);

  if (free_data == -1)
  {
    return -1;
  }

  set_free(block_map, free_data, 1);

  bwrite(BLOCK_MAP_BLOCK, block_map);

  return free_data;
}