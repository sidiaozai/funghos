# Makefile for JamesM's kernel tutorials.
# The C and C++ rules are already setup by default.
# The only one that needs changing is the assembler
# rule, as we use nasm instead of GNU as.

SOURCES=drivers/dvtab.o drivers/pcspkr.o drivers/ps2mouse.o mem/memory.o mem/palloc.o mem/malloc.o mem/free.o drivers/floppy.o mem/paging.o mem/utils.o apps/login.o apps/stopwatch.o boot/gdt.o boot/idt.o boot/irq.o boot/isrs.o boot/loader.o boot/main.o keyboard/kb.o keyboard/getchar.o keyboard/gets.o screen/scrn.o screen/win.o apps/cmd.o drivers/timer.o

CFLAGS=-nostdlib -nostdinc -fno-builtin -fno-stack-protector -I ./
LDFLAGS=-Tlink.ld
ASFLAGS=-felf

all: $(SOURCES) link 

clean:
	rm kernel
	rm apps/*.o
	rm boot/*.o
	rm keyboard/*.o
	rm screen/*.o
	rm drivers/*.o

link:
	ld $(LDFLAGS) -o kernel $(SOURCES)

.s.o:
	nasm $(ASFLAGS) $< 
