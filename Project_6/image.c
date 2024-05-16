#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "image.h"

int image_fd;
int image_open(char *filename, int truncate)
{
  if (truncate == 1){
    image_fd = open(filename, O_RDWR | O_TRUNC | O_CREAT, 0600);
  }
  else{
    image_fd = open(filename, O_RDWR | O_CREAT, 0600);
  }
return image_fd;
}

int image_close(void)
{

return close(image_fd);
}
