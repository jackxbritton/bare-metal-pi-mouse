include Makefile.inc

all:	kernel/kernel7.img

kernel/kernel7.img:
	cd genromfs-0.5.2 && make
	cd elf2bflt && make
	cd userspace && make image
	cd kernel && make

clean:	
	cd genromfs-0.5.2 && make clean
	cd elf2bflt && make clean
	cd kernel && make clean
	cd userspace && make clean
	rm -f *~

submit:
	make clean
	tar -czvf hw9_submit.tar.gz genromfs-0.5.2 elf2bflt userspace kernel Makefile Makefile.inc README
