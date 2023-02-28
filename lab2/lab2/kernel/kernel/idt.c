#include "x86.h"
#include "device.h"

#define INTERRUPT_GATE_32   0xE
#define TRAP_GATE_32        0xF

/* IDT表的内容 */
struct GateDescriptor idt[NR_IRQ]; // NR_IRQ=256, defined in x86/cpu.h

/* 初始化一个中断门(interrupt gate) */
static void setIntr(struct GateDescriptor *ptr, uint32_t selector, uint32_t offset, uint32_t dpl) {
	/* TODO: 初始化interrupt gate，
		ptr是结构体首地址；
		selector是段选择子，但是似乎不能直接让ptr->selector=selector....
		请理解后再填，弄清楚offset和dpl是啥玩意儿
		结构体声明在某个文件里
	*/
	ptr->offset_15_0 = offset & 0xFFFF;
	ptr->segment = selector << 3;
	ptr->pad0 = 0;
	ptr->type = INTERRUPT_GATE_32;
	ptr->system = 0;
	ptr->privilege_level = dpl;
	ptr->present = 1;
	ptr->offset_31_16 = (offset >> 16) & 0xFFFF;
}

/* 初始化一个陷阱门(trap gate) */
static void setTrap(struct GateDescriptor *ptr, uint32_t selector, uint32_t offset, uint32_t dpl) {
	/* TODO: 初始化trap gate
		要求同上
	*/
	ptr->offset_15_0 = offset & 0xFFFF;
	ptr->segment = selector << 3;
	ptr->pad0 = 0;
	ptr->type = TRAP_GATE_32;
	ptr->system = 0;
	ptr->privilege_level = dpl;
	ptr->present = 1;
	ptr->offset_31_16 = (offset >> 16) & 0xFFFF;
}

/* 声明函数，这些函数在汇编代码里定义 */
void irqEmpty();
void irqErrorCode();

void irqDoubleFault(); // 0x8
void irqInvalidTSS(); // 0xa
void irqSegNotPresent(); // 0xb
void irqStackSegFault(); // 0xc
void irqGProtectFault(); // 0xd
void irqPageFault(); // 0xe
void irqAlignCheck(); // 0x11
void irqSecException(); // 0x1e
void irqKeyboard(); 

void irqSyscall();


//256 interrupt vector
void initIdt() {
	int i;
	/* 为了防止系统异常终止，所有irq都有处理函数(irqEmpty)。 */
	for (i = 0; i < NR_IRQ; i ++) {
		setTrap(idt + i, SEG_KCODE, (uint32_t)irqEmpty, DPL_KERN);
	}
	/*init your idt here 初始化 IDT 表, 为中断设置中断处理函数*/
	
	/* Exceptions with error code */
	// TODO: 填好剩下的表项，参考上面那个，是不是就会了？
	setTrap(idt + 0x8, SEG_KCODE, (uint32_t)irqDoubleFault, DPL_KERN);
	setTrap(idt + 0xa, SEG_KCODE, (uint32_t)irqInvalidTSS, DPL_KERN);
	setTrap(idt + 0xb, SEG_KCODE, (uint32_t)irqSegNotPresent, DPL_KERN);
	setTrap(idt + 0xc, SEG_KCODE, (uint32_t)irqStackSegFault, DPL_KERN);
	setTrap(idt + 0xd, SEG_KCODE, (uint32_t)irqGProtectFault, DPL_KERN);
	setTrap(idt + 0xe, SEG_KCODE, (uint32_t)irqPageFault, DPL_KERN);
	setTrap(idt + 0x11, SEG_KCODE, (uint32_t)irqAlignCheck, DPL_KERN);
	setTrap(idt + 0x1e, SEG_KCODE, (uint32_t)irqSecException, DPL_KERN);
	setIntr(idt + 0x21, SEG_KCODE, (uint32_t)irqKeyboard, DPL_KERN);
    //8259A的15个中断都为内核级可以禁止用户程序用int指令模拟硬件中断！！！而syscall对应的门描述符的dpl......





	/* Exceptions with DPL = 3 */
	// TODO: 填好剩下的表项，哪个dpl是3，手册里都说了，别看往年代码，都是错的，小心被抓 ：）
	setIntr(idt + 0x80,SEG_KCODE,(uint32_t)irqSyscall,DPL_USER);


	/* 写入IDT */
	saveIdt(idt, sizeof(idt));//use lidt
}
