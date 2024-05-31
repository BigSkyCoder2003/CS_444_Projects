# Brandon Nelson & Daniel Lounsbury -- Project 8:  Continuing the File System, adding directories

## Building

Command line:

* `make` to build. An executable called `testfs` will be produced.
* `make test` builds testfs if necessary and runs it
* `make clean` to clean up all build products except the executable.
* `make pristine` to clean up all build products entirely.

## Files


* `testfs.c`: The main file of the program. This has the test framework functions included from ctest.h and the main function of the program.
* `block.c`: Home to two functions, bread(), bwrite(), and alloc()
* `block.h`: Header file to block.c
* `image.c`: Contains two functions, image_open() and image_close()
* `image.h`: Header file to image.c
* `inode.c`: Contains the function ialloc()
* `inode.h`: Header file to image.c
* `pack.c`: Contains the read and write "packing" helper functions for blocks of different sizes
* `pack.h`: Header file to pack.c
* `free.c`: file with functions used to find and mark free bits in the inode and block map
* `free.h`: Header file to free.c
* `dirbasename.c`: 
* `dirbasename.h`: 
* `dir.c`: Contains 3 functions, mkfs(), directory_get(), directory_open()
* `dir.h`: Header file to dir.c; Includes definitions for directory and directory_entry structure
* `ctest.h`: A file for a lightweight C test framework suitable for this programs present functions
* `libvvsfs.a`: Static Library for object files made during compilation
* `Makefile`: used to compile the program to obtain executable and build object files

## Data

    - image file descriptor, included as an extern in image and block header files

    - off_t offset for the block memory allocation

    - BLOCK_SIZE constant for filling the appropriate size of block memory

    - *block pointer to a buffer used to copy an image from disk

    - inode map array of BLOCK_SIZE

    - data block map

    - free inode

    - free data block

    - directory structure with attributes of inode and an offset

    - directory entry with attributes of it's inode number and name of file



## Functions

* `main()`Executes the main function of the program. Handles command line parsing. 

  * `*unsigned char *bread(int block_num, unsigned char *block)*`: Takes a pointer to a buffer to load with the block data. It copies it out of the disk image into that buffer. It also returns a pointer to that same buffer.

  * `*void bwrite(int block_num, unsigned char *block)`: function takes a pointer to a buffer full of block data to write.

  * `*void test_bread()*`: Test function to call CTEST_ASSERT on bread().

  * `*void test_bwrite()*`: Test function to call CTEST_ASSERT on bwrite().

  * `*int image_open(char *filename, int truncate)*`: Creates a file using open(), optionally sets truncate file, returns image file descriptor.

  * `*int image_close(void)*`: Closes image file descriptor.

  * `*int alloc(void)*`: returns the first free data block found in the block map.

  * `*struct inode *ialloc(void)*`: returns the first free inode located in the inode map.

  * `void ifree(int inode_num)*`: returns the first free inode located in the inode map.

  * `*struct inode *incore_find_free(void)*`: finds the first free in-core inode in the incore array. It returns a pointer to that in-core inode or NULL if there are no more free in-core inodes.

  * `*struct inode *incore_find(unsigned int inode_num)*`: finds an in-core inode record in the incore array by the inode number. It returns a pointer to that in-core inode or NULL if it can't be found.

  * `*void incore_free_all(void)*`: sets the ref_count to all in-core inodes to 0.

  * `*void read_inode(struct inode *in, int inode_num)*`: This takes a pointer to an empty struct inode that you're going to read the data into.

  * `*void write_inode(struct inode *in)*`: stores the inode data pointed to by in on disk.

  * `*struct inode *iget(int inode_num)*`: returns a pointer to an in-core inode for a given inode number, or null on failure.

  * `*void iput(struct inode *in)*`: decrement the reference count on the inode. If it falls to 0, write the inode to disk. Esssentialy frees an inode if it is not in use.

  * `*unsinged int read_u32(void *addr)*`: Reads data in block sizes of 4 bytes.

  * `*unsigned short read_u16(void *addr)*`: Reads data in block sizes of 2 bytes.

  * `*unsigned char read_u8(void *addr)*`: Reads data in block sizes of 1 byte.

  * `*void write_u32(void *addr, unsigned long value)*`: Writes data to a block size of 4 bytes.

  * `*void write_u16(void *addr, unsigned int value)*`: Writes data to a block size of 2 bytes.

  * `*void write_u8(void *addr, unsigned char value)*`: Writes data to a block size of 1 byte.

  * `*void set_free(unsigned char *block, int num, int set)*`:  set a specific bit to the value in set (0 or 1).

  * `*int find_free(unsigned char *block)*`: find a 0 bit and return its index (i.e. the block number that corresponds to this bit).

  * `*void mkfs()*`: Creates the root directory by allocating memory space for the inode and free memory block before committing the root block.

  * `*struct directory *directory_open(int inode_num)*`: Returns the directory where the passed inode resides.

  * `*int directory_get(struct directory *dir, struct directory_entry *ent)*`: performs a read on a directory by taking a pointer to the directory obtained by directory_open() and also a pointer to a directory entry to fill in the directory information.

  * `*int directory_make(char *path)*`: Creates a directory.

  * `*struct inode *namei(char *path)*`: maps a file specified by a path to that file's in-core inode.

  * `*void directory_close(struct directory *dir)*`: Closes a specified directory.

  * `*void ls(void)*`: lists all files found in directory.


## Notes

