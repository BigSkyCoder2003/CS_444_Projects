#ifndef DIR_H
#define DIR_H


#define IS_DIRECTORY 2
#define DIRECTORY_ENTRY_SIZE 32
#define DIRECTORY_NAME_OFFSET 2
#define DIRECTORY_ENTRY_COUNT 2
#define ROOT_INODE_NUM 0
#define MAX_PATH_SIZE 1024
#define BLOCK_FREE_MAP_NUMBER 2

struct directory {
    struct inode *inode;
    unsigned int offset;
};

struct directory_entry {
    unsigned int inode_num;
    char name[16];
};

void mkfs();

struct directory *directory_open(int inode_num);

int directory_get(struct directory *dir, struct directory_entry *ent);

void directory_close(struct directory *dir);

struct inode *namei(char *path);

int directory_make(char *path);

#endif