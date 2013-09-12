SHELL = /bin/sh

grand: grand.c
	$(CC) -std=c99 -o $@ $<

clean:
	rm -f grand

