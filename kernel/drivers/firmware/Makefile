include ../../../Makefile.inc
include ../../Makefile_kernel.inc

INCLUDE = -I../../include

all:	firmware.armv7.a

#### ARMV7

firmware.armv7.a:	mailbox.armv7.o
	$(CROSS)$(AR) crs firmware.armv7.a mailbox.armv7.o

mailbox.armv7.o:	mailbox.c
	$(CROSS)$(CC) $(CFLAGS_ARMV7) $(INCLUDE) -o mailbox.armv7.o -c mailbox.c

####

clean:
	rm -f *~ *.o *.a
