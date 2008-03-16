#include <system.h>

/* tohle bych mohl pozdeji vyuzit pro uptime */
int timer_ticks = 0;
int timer_sec = 0;
int timer_min = 0;
int timer_hrs = 0;
int stopwatch_on;


void timer_show() {
  csr_x=rtwin(CSRX)+13;
  txtclr(GREEN,TXTBACKGROUND); puti(timer_hrs); putch(':');
  txtclr(LIGHT_GREEN,TXTBACKGROUND); puti(timer_min); putch(':');
  txtclr(RED,TXTBACKGROUND); puti(timer_sec); putch(' ');
  txtclr(TXTFOREGROUND,TXTBACKGROUND);
}

void timer_init() {
  csr_x=rtwin(CSRX)+1;
  timer_ticks=0;
  timer_sec=0;
  timer_min=0;
  timer_hrs=0;
  puts("To exit, press x.\n");
  puts("Stopwatch: ");
}

/* 18.222Hz?  */
/* tahle funkce slouzi jako stopky, pokud je timer zapnuty */
void timer_handler(struct regs *r)
{
    if (stopwatch_on) {
      if (timer_ticks==0) timer_init();
      timer_ticks++;
      if (timer_ticks % 18==0) timer_sec++;
      if (timer_sec==60) {timer_min++;timer_sec=0;}
      if (timer_min==60) {timer_hrs++;timer_min=0;}
      /* dny? */
      timer_show();
      if (kbbuf[0]=='x') {
	stopwatch_on=FALSE;
	putch('\b');
	putch(' ');
	puts("Exiting...\n");
	bufdel();
      } else {bufdel();}
    }

}

/* Sets up the system clock by installing the timer handler
*  into IRQ0 */
void timer_install()
{
    /* Installs 'timer_handler' to IRQ0 */
    irq_install_handler(0, timer_handler);
}
