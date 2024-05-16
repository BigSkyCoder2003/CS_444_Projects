#include "inode.h"
#include "block.c"
#include "free.c"
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>



int ialloc(void) {


    unsigned char inode_map[BLOCK_SIZE];

    bread(INODE_MAP_BLOCK, inode_map);

    int free_inode = find_free(inode_map);

    if (free_inode == -1) {
        return -1;
    }

    set_free(inode_map, free_inode, 0);

    bwrite(inode_map, INODE_MAP_BLOCK);

    return free_inode;

}
