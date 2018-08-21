CC=gcc
CCFLAGS=-Wall -o
TARGET=main
OTHER_TARGETS=matrix

all:
	@$(clean)
	@$(CC) $(CCFLAGS) $(TARGET) -o main.c matrix.c matrix.h;

clean:
	@rm -f $(TARGET) $(OTHER_TARGETS);

