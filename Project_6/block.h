#ifndef BLOCK_H
#define BLOCk_H

#define BLOCK_SIZE 4096

unsigned char *bread(int block_num, unsigned char *block);

void bwrite(int block_num, unsigned char *block);

#endif