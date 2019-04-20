
//产生一条CPU暂停指令
#define PAUSE() asm volatile("pause": : :"memory")
//编译器内存屏蔽,防止编译器生成乱序的代码
#define BARRIER asm volatile ("" : : : "memory")
//CPU内存屏障,防止CPU乱序执行指令
#define MB() asm volatile("mfence":::"memory")

#define RMB() asm volatile("lfence":::"memory")

#define WMB() asm volatile("sfence":::"memory")


