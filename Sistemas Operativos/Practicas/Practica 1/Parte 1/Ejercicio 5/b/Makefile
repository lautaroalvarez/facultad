CFLAGS= -Wall -O0 -g -ggdb -m32
NASMFLAGS= -g -ggdb
LDFLAGS=-static -m32 -L'/usr/lib32'
CC=gcc

BINS=main

OBJS=$(BINS:=.o)

all: $(BINS)

# Dependencias
main.o: main.c

clean:
	rm -rf $(OBJS) $(BINS)
