SRCS = mkdev.c
EXTRA_CFLAGS :=-g
obj-m += mkdev.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

TAGS: $(SRCS)
	find . -regex ".*\.[cChH]\(pp\)?" -print | etags -

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
