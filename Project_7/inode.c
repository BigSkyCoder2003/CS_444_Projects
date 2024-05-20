#include "inode.h"
#include "block.h"
#include "free.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

unsigned char inode_map[BLOCK_SIZE];

int ialloc(void)
{

  bread(INODE_MAP_BLOCK, inode_map);

  int free_inode = find_free(inode_map);

  if (free_inode == -1)
  {
    return -1;
  }

  set_free(inode_map, free_inode, 1);

  bwrite(INODE_MAP_BLOCK, inode_map);

  return free_inode;
}
