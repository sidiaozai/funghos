#ifndef SYSTEM_H
#define SYSTEM_H

#define VERSION "FunghOS v0.03OpenSource" /* version name */

/* global */
#define OK 0
#define ERROR 1 /* 'vraceci' hodnota pri 'nezname' chybe */
#define SECURITYERROR 2 /* poruseni pravidel nekterym prog. atp. */
#define TRUE 1
#define FALSE 0

typedef unsigned int u32int;

/* global ** end */



/* main.c */
extern void *memcpy(unsigned char *dest, const unsigned char *src, int count);

extern void *memset(void *dest, char val, int count);

extern unsigned short *memsetw(unsigned short *dest, unsigned short val, int count);

extern int strlen(const char *str);

extern int strcmp(s1, s2);

extern void strcpy(char *s1, char *s2);

extern unsigned char inportb(unsigned short _port);
/* main.c ** end */


/* gdt.c */
extern void gdt_set_gate(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran);

extern void gdt_install(); 

/* gdt.c ** end */

/* idt.c */
extern void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags);

extern void idt_install();
/* idt.c ** end */

/* isrc.c */
struct regs
{
    unsigned int gs, fs, es, ds;      /* pushed the segs last */
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;  /* pushed by 'pusha' */
    unsigned int int_no, err_code;    /* our 'push byte #' and ecodes do this */
    unsigned int eip, cs, eflags, useresp, ss;   /* pushed by the processor automatically */ 
};

extern void isrs_install();
/* isrc.c ** end */

/* irq.c */
extern void irq_install_handler(int irq, void (*handler)(struct regs *r));

extern void irq_uninstall_handler(int irq);

extern void irq_install();
/* irq.c ** end */

/* kb.c */
#define BUFFERSIZE 100

extern char kbbuf[BUFFERSIZE];

extern int kbpos;

extern unsigned int shift;

extern unsigned int getc_on;

extern unsigned int gets_on;

extern unsigned int kbprint_on;

extern unsigned int cmd_on;

extern unsigned int login_on;

extern void keyboard_install();

extern void keyboard_handler(struct regs *r);
/* kb.c ** end */

/* scrn.c */
#define CSRX 0
#define CSRY 1

extern unsigned short *textmemptr;

extern int csr_x;

extern int csr_y;

extern void cls(void);

extern void move_csr(void);

extern void scroll(void);

extern void i_video(void);

extern void i_hello(void);

/* scrn.c ** end */




/* win.c */
#define SYSLINE 2 /* pocet radek zabranych systemem */
#define WINSIZEX 35  /* default sirka noveho okna */
#define WINSIZEY 10  /* default vyska noveho okna */
#define WINMAX 10 /* kolik muze byt zaroven otevreno oken, maximum +1 */
#define BDFOREGROUND 0  /* barva, kterou se budou psat mezery u okraju win :D */
#define BDBACKGROUND BLUE /* barva okraju oken */
#define WINFOREGROUND 0
#define WINBACKGROUND 7
#define TXTFOREGROUND 1
#define TXTBACKGROUND WINBACKGROUND
#define WINEND 2
#define WINSCROLL 3
#define CSRY2 4
#define CSRX2 5
/* CSRX a CSRY jsou definovane ve screen jako 0 a 1 !!!!!!! */
extern int currwin;

extern void scwin(int winnum);

extern void drwin(int winnum);

extern int mkwin(int x, int y, int x2, int y2, int pid); /* vytvoreni okna */

extern int rmwin(int winnum, int pid); /* smazani okna */

extern int wrwin(int winnum, int pid, int line, char *str[]);

extern int wherewin(int type);
/* win.c ** end*/

/* cmd.c */
extern void cmdexec();

extern void cmd_install();
/* cmd.c ** end */


/* timer.c */
extern void timer_install();

extern void stopwatch();
/* timer.c ** end */


/* menu.c */
#define MENUNAMELEN 25;
#define ROOTMENUSIZE 10;
#define MENUSIZE 50;

extern int menu_addentry(char *name, char *action, int rootmenu);

extern int menu_rementry(char *name);

extern void menu_install();

/* menu.c ** end */

extern void Shutdown();

#endif
/* eof system.h */
