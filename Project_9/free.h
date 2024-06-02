#ifndef FREE_H
#define FREE_H

#define INODE_MAP_BLOCK 1
#define BLOCK_MAP_BLOCK 2
#define BYTE_SIZE 8

void set_free(unsigned char *block, int num, int set);

int find_free(unsigned char *block);

#endif