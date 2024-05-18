#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "image.h"
#include "block.h"
#include "ctest.h"
#include "free.h"
#include "inode.h"

void test_bread(void)
{

  unsigned char block[BLOCK_SIZE];
  unsigned char data[BLOCK_SIZE] = {1, 2, 3, 4, 5, 6, 7, 8};

  bwrite(0, data);

  unsigned char *read_block = bread(0, block);

  CTEST_ASSERT(memcmp(read_block, data, BLOCK_SIZE) == 0, "checking memory block against test data");
}

void test_bwrite()
{

  unsigned char block[BLOCK_SIZE];
  unsigned char data[BLOCK_SIZE] = {1, 2, 3, 4, 5, 6, 7, 8};

  bwrite(0, data);

  unsigned char *read_block = bread(0, block);

  CTEST_ASSERT(memcmp(read_block, data, BLOCK_SIZE) == 0, "checking memory block against test data");
}

void test_ialloc(void)
{
  int free_inode1 = ialloc();
  printf("free_inode1: %d\n", free_inode1);
  CTEST_ASSERT(free_inode1 == 0, "checking if inode is allocated");

  int free_inode2 = ialloc();
  printf("free_inode2: %d\n", free_inode2);
  CTEST_ASSERT(free_inode2 == 1, "checking if inode is allocated");

  set_free(inode_map, free_inode1, 0);
  set_free(inode_map, free_inode2, 0);
  bwrite(INODE_MAP_BLOCK, inode_map);
}

void test_set_free(void)
{

  unsigned char block[BLOCK_SIZE];
  unsigned char data[BLOCK_SIZE] = {1, 2, 3, 4, 5, 6, 7, 8};

  bwrite(0, data);

  unsigned char *read_block = bread(0, block);

  CTEST_ASSERT(memcmp(read_block, data, BLOCK_SIZE) == 0, "checking memory block against test data");

  set_free(block, 0, 1);

  CTEST_ASSERT(block[0] == 1, "checking if block is set to 1");

  set_free(block, 0, 0);

  CTEST_ASSERT(block[0] == 0, "checking if block is set to 0");
}

void test_find_free(void)
{

  unsigned char block[BLOCK_SIZE] = {0b11111011};

  int zero_bit = find_free(block);

  CTEST_ASSERT(zero_bit == 2, "checking if zero bit is found");
}

int main(void)
{
  image_open("image", 0);

  CTEST_VERBOSE(1);

  test_bread();
  test_bwrite();
  test_ialloc();
  test_set_free();
  test_find_free();

  CTEST_RESULTS();

  CTEST_EXIT();

  image_close();
}
