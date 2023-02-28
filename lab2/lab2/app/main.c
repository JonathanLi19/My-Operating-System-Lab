#include "lib.h"
#include "types.h"

//用户程序，在用户空间，lab测试方法：make clean后make，然后make play


int uEntry(void) {
	//下面三行不用管
	uint16_t selector;
	asm volatile("movw %%ss, %0":"=m"(selector)); // necessary or not, iret may reset ds in QEMU
	asm volatile("movw %%ax, %%ds"::"a"(selector));
	
	
	printf("I/O test begin...\n");
	printf("the answer should be:\n");
	printf("#######################################################\n");
	printf("Hello, welcome to OSlab! I'm the body of the game.\n");
	printf("Now I will test your printf:\n");
	printf("1 + 1 = 2, 123 * 456 = 56088, 0, -1, -2147483648, -1412505855, -32768, 102030, 0, ffffffff, 80000000, abcdef01, ffff8000, 18e8e\n");
	printf("Now I will test your getChar: ");
	printf("1 + 1 = 2\n2 * 123 = 246\n");
	printf("Now I will test your getStr: ");
	printf("Alice is stronger than Bob\nBob is weaker than Alice\n");
	printf("#######################################################\n");
	printf("your answer:\n");
	printf("=======================================================\n");
	printf("%s %s%scome %co%s", "Hello,", "", "wel", 't', " ");
	printf("%c%c%c%c%c! ", 'O', 'S', 'l', 'a', 'b');
	printf("I'm the %s of %s.\n", "body", "the game");
	printf("Now I will test your printf:\n");
	printf("%d + %d = %d, %d * %d = %d, ", 1, 1, 1 + 1, 123, 456, 123 * 456);
	printf("%d, %d, %d, %d, %d, %d, ", 0, 0xffffffff, 0x80000000, 0xabcedf01, -32768, 102030);
	printf("%x, %x, %x, %x, %x, %x\n", 0, 0xffffffff, 0x80000000, 0xabcedf01, -32768, 102030);
	printf("Now I will test your getChar: ");
	printf("1 + 1 = ");
	char num = getChar();
	printf("%c * 123 = 246\n",num);
	printf("Now I will test your getStr: ");
	printf("Alice is stronger than ");
	char name[20];
	getStr(name,20);
	printf("%s is stronger than Alice\n",name);
	printf("=======================================================\n");
	printf("Test end!!! Good luck!!!\n");
	printf("Now I will test your scanf: ");
	char c1 = 0;char c2 = 0;
	scanf("%c %c", &c1,&c2);
	printf("Get %c %c\n",c1,c2);
	int d1 = 0;
	scanf("%d", &d1);
	printf("Get %d\n",d1);
	uint32_t x1 = 0;
	scanf("%x", &x1);
	printf("Get %x\n",x1);
	char str1[20];
	scanf("%s",str1);
	printf("Get %s\n",str1);
	while(1);
	return 0;
}
