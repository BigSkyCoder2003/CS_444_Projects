#ifndef INODE_H
#define INODE_H

#include "block.h"

extern unsigned char inode_map[BLOCK_SIZE];

int ialloc(void);

#endif