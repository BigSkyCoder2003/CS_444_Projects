#include "dir.h"
#include "inode.h"
#include "pack.h"
#include "block.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>



void mkfs()
{
struct inode *free_inode = ialloc();
int free_block = alloc();
struct inode *root = iget(free_inode->inode_num);

root->flags = IS_DIRECTORY;
root->size = DIRECTORY_ENTRY_SIZE * DIRECTORY_ENTRY_COUNT;
root->block_ptr[0] = free_block;

unsigned char block[BLOCK_SIZE];

write_u16(block, free_inode->inode_num);
strcpy((char*)block+DIRECTORY_NAME_OFFSET, ".");
write_u16(block+DIRECTORY_ENTRY_SIZE, free_inode->inode_num);
strcpy((char*)block+DIRECTORY_ENTRY_SIZE+DIRECTORY_NAME_OFFSET, "..");

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
  {
    return -1;
  }

    unsigned int data_block_index = dir->offset / 4096;
    unsigned int data_block_num = dir->inode->block_ptr[data_block_index];
    char block[BLOCK_SIZE];
    bread(data_block_num, (unsigned char*)block);
    unsigned int entry_offset = dir->offset % 4096;
    ent-> inode_num = read_u16(&block[entry_offset]);
    strcpy(ent->name, &block[entry_offset + 2]);

    dir->offset += DIRECTORY_ENTRY_SIZE;
    return 0;
}

void directory_close(struct directory *dir)
{
  iput(dir->inode);
  free(dir);
}


int directory_make(char *path)
{
return 0;
}

struct inode *namei(char *path)
{
if(strcmp(path, "/") == 0)
{
  return iget(ROOT_INODE_NUM);
}
else
{
  return NULL;
}
}