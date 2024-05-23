CC = gcc
AR = ar
CFLAGS = -DCTEST_ENABLE -Wall -Wextra -g
LIB = libvvsfs.a
OBJS = block.o image.o inode.o free.o testfs.o pack.o
all: $(LIB) testfs
$(LIB): $(OBJS)
		$(AR) rcs $@ $^
%.o: %.c
		$(CC) $(CFLAGS) -c $< -o $@
testfs: $(LIB)
		$(CC) $(CFLAGS) -o $@ testfs.o $(LIB)
test: testfs
		./testfs
clean:
		rm -f *.o
pristine: clean
		rm -f $(LIB) testfs testfs.exe image


# CC = gcc
# AR = ar
# CFLAGS = -DCTEST_ENABLE -Wall -Wextra -g
# LIB = libvvsfs.a
# OBJS = block.o image.o testfs.o inode.o

# all: $(LIB) testfs

# $(LIB): $(OBJS)
# 	$(AR) rcs $@ $^

# %.o: %.c
# 	$(CC) $(CFLAGS) -c $< -o $@

# testfs: $(LIB)
# 	$(CC) $(CFLAGS) -o $@ testfs.o $(LIB)

# test: testfs
# 	./testfs

# clean:
# 	rm -f *.o

# pristine: clean
# 	rm -f $(LIB) testfs testfs.exe image


	