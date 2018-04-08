include ../../../Makefile.inc
include ../../Makefile_kernel.inc

INCLUDE = -I../../include

all:	framebuffer.armv7.a

#### ARMV7

framebuffer.armv7.a:	framebuffer.armv7.o framebuffer_console.armv7.o
	$(CROSS)$(AR) crs framebuffer.armv7.a framebuffer.armv7.o framebuffer_console.armv7.o

framebuffer.armv7.o:	framebuffer.c
	$(CROSS)$(CC) $(CFLAGS_ARMV7) $(INCLUDE) -o framebuffer.armv7.o -c framebuffer.c

framebuffer_console.armv7.o:	framebuffer_console.c
	$(CROSS)$(CC) $(CFLAGS_ARMV7) $(INCLUDE) -o framebuffer_console.armv7.o -c framebuffer_console.c

####

clean:
	rm -f *~ *.o *.a

