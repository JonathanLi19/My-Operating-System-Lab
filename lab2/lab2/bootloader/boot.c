#include "boot.h"

#define SECTSIZE 512
#define LOAD 1

void bootMain(void) {
	int i = 0;
	int phoff = 0x34;
	//int offset = 0x1000;
	unsigned int elf = 0x200000;
	void (*kMainEntry)(void);
	kMainEntry = (void(*)(void))0x100000;

	for (i = 0; i < 200; i++) {
		readSect((void*)(elf + i*512), 1+i);
	}

	// TODO: 填写kMainEntry、phoff、offset...... 然后加载Kernel（可以参考NEMU的某次lab）
	kMainEntry = (void(*)(void))((struct ELFHeader *)elf)->entry;
	phoff = ((struct ELFHeader *)elf)->phoff;
	ProgramHeader* ph=(ProgramHeader*)(elf+phoff);
	for(int k = 0; k < ((struct ELFHeader *)elf)->phnum; k++) {
		if (ph[k].type == LOAD) {
			for(i = 0; i < ph[k].filesz; i++)
			{
				*(unsigned char *)(ph[k].paddr + i) = *(unsigned char *)(elf + ph[k].off + i);
			}
			for(; i < ph[k].memsz; i++) {
				*(unsigned char *)(ph[k].paddr + i) = 0;
			}
		}
	}
	kMainEntry();
}

void waitDisk(void) { // waiting for disk
	while((inByte(0x1F7) & 0xC0) != 0x40);
}

void readSect(void *dst, int offset) { // reading a sector of disk
	int i;
	waitDisk();
	outByte(0x1F2, 1);
	outByte(0x1F3, offset);
	outByte(0x1F4, offset >> 8);
	outByte(0x1F5, offset >> 16);
	outByte(0x1F6, (offset >> 24) | 0xE0);
	outByte(0x1F7, 0x20);

	waitDisk();
	for (i = 0; i < SECTSIZE / 4; i ++) {
		((int *)dst)[i] = inLong(0x1F0);
	}
}
