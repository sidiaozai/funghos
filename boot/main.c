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


char getc() {
  bufdel();
  getc_on=TRUE;
  while (kbbuf[kbpos]!='\0')
    ;
  getc_on=FALSE;
  return kbbuf[0];
}

char *gets() {
  bufdel();
  gets_on=TRUE;
  while (kbbuf[kbpos]!='\0')
    ;
  gets_on=FALSE;
  return kbbuf;
}

void login(int x)
{
  
  static char username[15];
  static char password[15];
  if (x==0) {
  login_on=TRUE;
  kbprint_on=TRUE;
  bufdel();
  kbpos=0;
  int i;
  int loginwin=mkwin(30,9,50,16,1);
  static int ok=FALSE;
  txtclr(WHITE,LIGHT_BLUE);
  puts("      Welcome!     "); /* \n */
  puts("      Login:       "); /* \n */
  puts("     ");
  txtclr(BLACK,WHITE);
  puts("         ");
  txtclr(WHITE,LIGHT_BLUE);
  puts("     "); /* \n */
  puts("     Password:     "); /* \n */
  puts("     ");
  txtclr(BLACK,WHITE);
  puts("         ");
  txtclr(WHITE,LIGHT_BLUE);
  puts("     "); /* \n */
  puts("                  ");
  putcha(' ');
  csr_x=36;
  csr_y=12;
  move_csr();
  txtclr(RED,WHITE);
  for (;;) {;}
  }


if (x==1) {
  static int xx=0;
  if (xx==0) {
    strcpy(username,kbbuf);
    bufdel();
    xx=1;
    csr_x=36;
    csr_y=14;
    move_csr();
  } else {
    strcpy(password,kbbuf);
    bufdel();
    login(2);
  }
}


 if (x==2) {
   int userok=strcmp(username,"user");
   int passok=strcmp(password,"password");
   if (userok==0&&passok==0) {
     login_on=FALSE;
     bufdel();
     cmd_install();
   } else {
     puts("\nBad username\nor password...");
     login(0);
   }
 }

} /* konec funkce */


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
  bufdel();
  kbpos=0;
  cmd_on=FALSE;
  login_on=FALSE;
  mkwin(0,0,0,0,0);
  char c=getchar();
  putch(c);
  login(0);
  bufdel();
  kbpos=0;
  //cmd_install();
  for (;;)
    ;
}
