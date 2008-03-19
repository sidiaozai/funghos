#include <system.h>
#include <stdio.h>


void *memcpy(unsigned char *dest, const unsigned char *src, int count)
{
    const char *sp = (const char *)src;
    char *dp = (char *)dest;
    for(; count != 0; count--) *dp++ = *sp++;
    return dest;
}

void *memset(void *dest, char val, int count)
{
    char *temp = (char *)dest;
    for( ; count != 0; count--) *temp++ = val;
    return dest;
}

unsigned short *memsetw(unsigned short *dest, unsigned short val, int count)
{
    unsigned short *temp = (unsigned short *)dest;
    for( ; count != 0; count--) *temp++ = val;
    return dest;
}

int strlen(const char *str)
{
    int retval;
    for(retval = 0; *str != '\0'; str++) retval++;
    return retval;
}

unsigned char inportb(unsigned short _port)
{
    unsigned char rv;
    __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}

void outportb (unsigned short _port, unsigned char _data)
{
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));
}



int strcmp(s1, s2)
        register const char *s1, *s2;
{
        while (*s1 == *s2++)
                if (*s1++ == 0)
                        return (0);
        return (*(const unsigned char *)s1 - *(const unsigned char *)(s2 - 1));
}


void strcpy(char *s1, char *s2)
{
    while (*s1++ = *s2++)
      ;
}



void _main()
{


  gdt_install();
  idt_install();
  isrs_install();
  irq_install();
  keyboard_install();
  timer_install();
  i_video();
  __asm__ __volatile__ ("sti");
  mkwin(0,0,0,0,0);
  char string[15];
  gets(string);
  puts(string);
  login(0);
  bufdel();
  kbpos=0;
  //cmd_install();
  for (;;)
    ;
}
