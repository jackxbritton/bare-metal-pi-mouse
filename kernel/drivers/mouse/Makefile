include ../../../Makefile.inc
include ../../Makefile_kernel.inc

INCLUDE = -I../../include

all:	mouse.armv7.a

#### ARMV7

mouse.armv7.a:	mouse.armv7.o
	$(CROSS)$(AR) crs mouse.armv7.a mouse.armv7.o

mouse.armv7.o:	mouse.c
	$(CROSS)$(CC) $(CFLAGS_ARMV7) $(INCLUDE) -o mouse.armv7.o -c mouse.c

####

clean:
	rm -f *~ *.o *.a



