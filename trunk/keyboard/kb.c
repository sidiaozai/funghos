#include <system.h>
#include "kbmap.h"
#include "kb.h"

KB_FLAGS kb_flags;
unsigned int getc_on=0;
unsigned int gets_on=0;
unsigned int kbprint_on=0;
unsigned int cmd_on=0;
unsigned int login_on=0;
unsigned int login_retry=0;
unsigned int shift=FALSE;

unsigned char kbdus[128] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
  '9', '0', '-', '=', '\b',	/* Backspace */
  '\t',			/* Tab */
  'q', 'w', 'e', 'r',	/* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
    0,			/* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
 '\'', '`',   '\S',		/* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
  'm', ',', '.', '/',   '\S',				/* Right shift */
  '*',
    0,	/* Alt */
  ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};

/* array pro shift */
unsigned char kbdus2[128] =
{
    0,  27, '!', '@', '#', '$', '%', '^', '&', '*',
  '(', ')', '_', '+', '\b',	/* Backspace */
  '\t',			/* Tab */
  'Q', 'W', 'E', 'R',	/* 19 */
  'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n',	/* Enter key */
    0,			/* 29   - Control */
  'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':',	/* 39 */
 '"', '~',   '\S',		/* Left shift */
 '|', 'Z', 'X', 'C', 'V', 'B', 'N',			/* 49 */
  'M', '<', '>', '?',   '\S',				/* Right shift */
  '*',
    0,	/* Alt */
  ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};



/* globalni */
char kbbuf[BUFFERSIZE];
int kbpos=0;
char *p_kbbuf=&kbbuf;

/* keyboard buffer, uklada vse co se stiskne */
void kbbuf_handler(char c) {
  if (kbpos<BUFFERSIZE&&c!='\n') {
    if (c=='\b') {
      kbbuf[kbpos--]=' ';
    } else {
    kbbuf[kbpos]=c;
    kbpos++;
    }
  } else {
    if (c=='\n') {
      kbbuf[kbpos++]='\0';
      if (login_on) {
	login(1);
      }
      if (cmd_on) cmdexec();
    }
  }
}


/* Handles the keyboard interrupt */
void keyboard_handler(struct regs *r)
{
  unsigned char scancode;
  scancode = inportb(0x60);
  if (kbprint_on==TRUE) {

    /* If the top bit of the byte we read from the keyboard is
     *  set, that means that a key has just been released*/
    if (scancode & 0x80)
    {
      if (scancode==170||scancode==182) kb_flags.shift=FALSE;
      /*170 - levy shift, 182 - pravy shift*/
    }
    else
    {
      if (kbdus[scancode]!='\S') {
        switch (kb_flags.shift) {
	case 0:putch(kbdus[scancode]);kbbuf_handler(kbdus[scancode]);break;
	case 1:putch(kbdus2[scancode]);kbbuf_handler(kbdus2[scancode]);break;
	}
      } else {
	kb_flags.shift=TRUE;
      }
    }

    if (login_on&&kbpos==9) {
      csr_x--;
      move_csr();
      kbprint_on=FALSE;
    }
  } else {
    /* if (kbdus[scancode]=='\b') { */
/*       csr_x--; */
/*       putch(' '); */
/*       csr_x--; */
/*       move_csr(); */
/*     } */
/*     switch (shift) { */
/*     case 0:kbbuf_handler(kbdus[scancode]);break; */
/*     case 1:kbbuf_handler(kbdus[scancode]);break; */
/*     } */
  }
}

void keyboard_install()
{
    /* Instaluje keyboard na  IRQ0 */
    irq_install_handler(1, keyboard_handler);
    bufdel();
    kb_flags.shift=FALSE;
}
