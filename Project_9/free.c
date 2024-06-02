#include "block.h"
#include "free.h"

void set_free(unsigned char *block, int num, int set)
{
  int byte_num = num / BYTE_SIZE;
  int bit_num = num % BYTE_SIZE;

  if (set)
    block[byte_num] |= (1 << bit_num);
  else
    block[byte_num] &= ~(1 << bit_num);
}

int find_low_clear_bit(unsigned char x)
{
  for (int i = 0; i < BYTE_SIZE; i++)
    if (!(x & (1 << i)))
      return i;

  return -1;
}

int find_free(unsigned char *block)
{
  int zero_bit = -1;
  for (int i = 0; i < BLOCK_SIZE; i++)
  {
    zero_bit = find_low_clear_bit(block[i]);
    if (zero_bit != -1)
      return i * BYTE_SIZE + zero_bit;
  }
  return -1;
}
