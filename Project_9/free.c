#include "block.h"
#include "free.h"

void set_free(unsigned char *block, int num, int set)
{
  int byte_num = num / 8;
  int bit_num = num % 8;

  // int byte = block[byte_num];
  // block[byte_num] = (byte &  ~(1 << bit_num)) | (set << bit_num);
  if (set)
    block[byte_num] |= (1 << bit_num);
  else
    block[byte_num] &= ~(1 << bit_num);
}

int find_low_clear_bit(unsigned char x)
{
  for (int i = 0; i < 8; i++)
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
        return i*8+ zero_bit;

  }
  return -1;
  // for(int byte_num = 0; byte_num < BLOCK_SIZE; byte_num++)
  // {
  // int bit_num;
  // bit_num = find_low_clear_bit(block[byte_num]);
  // if(bit_num != -1)
  // {
  //   return((byte_num*8) +bit_num);

  // }


  
  // }
  // return -1;
}
