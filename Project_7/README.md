# Brandon Nelson & Daniel Lounsbury -- Project 6: Continuing the File System, managing free blocks

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
* `ctest.h`: A file for a lightweight C test framework suitable for this programs present functions
* `libvvsfs.a`: Static Library for object files made during compilation
* `Makefile`: used to compile the program to obtain executable and build object files

## Data

    - image file descriptor, included as an extern in image and block header files

    - off_t offset for the block memory allocation

    - BLOCK_SIZE constant for filling the appropriate size of block memory

    - *block pointer to a buffer used to copy an image from disk

    - inode map

    - data block map

    - free inode

    - free data block



## Functions

* `main()`Executes the main function of the program. Handles command line parsing. 

  * `*bread()*`: Takes a pointer to a buffer to load with the block data. It copies it out of the disk image into that buffer. It also returns a pointer to that same buffer.

  * `*bwrite()`: function takes a pointer to a buffer full of block data to write.

  * `*test_bread()*`: Test function to call CTEST_ASSERT on bread().

  * `*test_bwrite()*`: Test function to call CTEST_ASSERT on bwrite().

  * `*image_open()*`: Creates a file using open(), optionally sets truncate file, returns image file descriptor.

  * `*image_close()*`: Closes image file descriptor.

  * `*alloc()*`: returns the first free data block found in the block map.

  * `*ialloc()*`: returns the first free inode located in the inode map.



## Notes

