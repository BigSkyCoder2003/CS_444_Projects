#include "dir.h"
#include "inode.h"
#include "pack.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


void mkfs()
{
int free_inode = ialloc();
int free_block = alloc();
struct inode *root = iget(free_inode);

root->flags = 2;
root->size = 64;
root->block_ptr[0] = free_block;

unsigned char block[BLOCK_SIZE];
write_u16(&block[0], free_inode);
strcpy((char*)&block[2], ".");
strcpy(&block[32], free_inode);
strcpy((char*)&block[34], "..");

bwrite(free_block, block);

iput(root);

} 

struct directory *directory_open(int inode_num)
{
  struct inode *inode = iget(inode_num);
  if (inode == NULL)
    return NULL;

  struct directory *dir = malloc(sizeof(struct directory));
  dir->inode = inode;
  dir->offset = 0;

  return dir;
}

int directory_get(struct directory *dir, struct directory_entry *ent)
{
  if (dir->offset >= dir->inode->size)
    return -1;
  
  

}