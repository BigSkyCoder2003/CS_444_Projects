#include "dir.h"
#include "inode.h"
#include "pack.h"
#include "block.h"
#include "dirbasename.c"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void mkfs()
{
  unsigned char blocktemp[BLOCK_SIZE] = {0};
  bwrite(INODE_BLOCK_3, blocktemp);
  blocktemp[0] = 0x7f; // 127 or 01111111
  bwrite(BLOCK_FREE_MAP_NUMBER, blocktemp);

  struct inode *free_inode = ialloc();

  int free_block = alloc();
  struct inode *root = iget(free_inode->inode_num);

  root->flags = IS_DIRECTORY;
  root->size = DIRECTORY_ENTRY_SIZE * DIRECTORY_ENTRY_COUNT;
  root->block_ptr[0] = free_block;

  unsigned char block[BLOCK_SIZE];

  write_u16(block, free_inode->inode_num);
  strcpy((char *)block + DIRECTORY_NAME_OFFSET, ".");
  write_u16(block + DIRECTORY_ENTRY_SIZE, free_inode->inode_num);
  strcpy((char *)block + DIRECTORY_ENTRY_SIZE + DIRECTORY_NAME_OFFSET, "..");

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

  unsigned int data_block_index = dir->offset / BLOCK_SIZE;
  unsigned int data_block_num = dir->inode->block_ptr[data_block_index];
  char block[BLOCK_SIZE];
  bread(data_block_num, (unsigned char *)block);
  unsigned int entry_offset = dir->offset % BLOCK_SIZE;
  ent->inode_num = read_u16(&block[entry_offset]);
  strcpy(ent->name, &block[entry_offset + DIRECTORY_NAME_OFFSET]);

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
  char dirname[MAX_PATH_SIZE];
  char basename[MAX_PATH_SIZE];
  get_dirname(path, dirname);
  get_basename(path, basename);
  struct inode *parent_inode = namei(dirname);
  if (parent_inode == NULL || !(parent_inode->flags & IS_DIRECTORY))
  {
    return -1;
  }

  struct inode *new_inode = ialloc();
  int new_block = alloc();
  struct inode *new_directory = iget(new_inode->inode_num);

  new_directory->flags = IS_DIRECTORY;
  new_directory->size = DIRECTORY_ENTRY_SIZE * DIRECTORY_ENTRY_COUNT;
  new_directory->block_ptr[0] = new_block;

  unsigned char block[BLOCK_SIZE];

  write_u16(block, new_inode->inode_num);
  strcpy((char *)block + DIRECTORY_NAME_OFFSET, ";.");

  write_u16(block + DIRECTORY_ENTRY_SIZE, parent_inode->inode_num);
  strcpy((char *)block + DIRECTORY_ENTRY_SIZE + DIRECTORY_NAME_OFFSET, ".;.");

  bwrite(new_block, block);

  int parent_block_index = parent_inode->size / BLOCK_SIZE;
  int parent_block_num = parent_inode->block_ptr[parent_block_index];

  unsigned char *parent_block = bread(parent_block_num, block);

  write_u16(parent_block + parent_inode->size % BLOCK_SIZE, new_inode->inode_num);
  strcpy((char *)parent_block + parent_inode->size % BLOCK_SIZE + DIRECTORY_NAME_OFFSET, basename);

  bwrite(parent_block_num, parent_block);

  parent_inode->size += DIRECTORY_ENTRY_SIZE;

  iput(new_inode);
  iput(parent_inode);

  return 0;
}

struct inode *namei(char *path)
{
  if (strcmp(path, "/") == 0)
  {
    return iget(ROOT_INODE_NUM);
  }
  else
  {
    return NULL;
  }
}