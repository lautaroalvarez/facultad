CFLAGS= -Wall -O0 -g -ggdb -m32
NASMFLAGS= -g -ggdb
LDFLAGS=-static -m32 -L'/usr/lib32'
CC=gcc

BINS=copia_hai

OBJS=$(BINS:=.o)

all: $(BINS)

# Dependencias
copia_hai.o: copia_hai.c

clean:
	rm -rf $(OBJS) $(BINS)
