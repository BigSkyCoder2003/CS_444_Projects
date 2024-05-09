#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "image.h"
#include "block.h"
#include "ctest.h"


void test_bread(void){
  
    unsigned char block[BLOCK_SIZE];
    unsigned char data[BLOCK_SIZE] = {1,2,3,4,5,6,7,8};

    bwrite(0, data);

    unsigned char *read_block = bread(0, block);

    CTEST_ASSERT(memcmp(read_block, data, BLOCK_SIZE) == 0, "checking memory block against test data");

    }
   

void test_bwrite(){
    
   unsigned char block[BLOCK_SIZE];
    unsigned char data[BLOCK_SIZE] = {1,2,3,4,5,6,7,8};

    bwrite(0, data);

    unsigned char *read_block = bread(0, block);

    CTEST_ASSERT(memcmp(read_block, data, BLOCK_SIZE) == 0, "checking memory block against test data");


}

int main(void)
{
    image_open("image",0);

    CTEST_VERBOSE(1);

    test_bread();
    test_bwrite();

    CTEST_RESULTS();

    CTEST_EXIT();
    image_close();
}

// #else

// int main(void)
// {
//     printf("Running normally!\n");
//     printf("1 + 2 = %d\n", adder(1, 2));
// }

// #endif