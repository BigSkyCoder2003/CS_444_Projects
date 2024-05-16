#include "inode.h"
#include "block.c"
#include "free.c"
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>



int ialloc(void) {


    unsigned char inode_map[INODE_MAP_BLOCK];

    bread(BLOCK_SIZE, inode_map);

    int free_inode = find_free(inode_map);

    if (free_inode == -1) {
        return -1l
    }

    set_free(inode_map, free_inode, 0);

    bwrite(inode_map, INODE_MAP_BLOCK);
    
    return inode_map;

}
