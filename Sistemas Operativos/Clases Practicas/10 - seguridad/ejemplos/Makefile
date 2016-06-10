CC = gcc
CFLAGS = -m32 -fno-stack-protector -Wall -O0 -g -ggdb \
	-Wl,-z,norelro -z execstack

.PHONY: all clean

all: fs hola primero saludo saludodump

fs: fs.c
	$(CC) $(CFLAGS) -o $@ $^

hola: hola.c
	$(CC) $(CFLAGS) -o $@ $^

primero: primero.c
	$(CC) $(CFLAGS) -o $@ $^

saludo: saludo.c
	$(CC) $(CFLAGS) -o $@ $^

saludodump: saludo
	objdump --no-show-raw-insn -d -M intel $^ | grep '<saludo>:' -A15 > $@

clean:
	rm -f fs
	rm -f hola
	rm -f primero
	rm -f saludo

	rm -f saludodump
