#include <system.h>
#include <stdio.h>



void timer_handler(); /* function called when the timer fires */
void timer_install(); /* installs the timer_handler */



unsigned int timer_ticks=0;
unsigned int timer_sec=0;
unsigned int timer_min=0;
unsigned int timer_hrs=0;



void timer_handler(struct regs *r)
{
  timer_ticks++;
  if ((timer_ticks%18==0)&&(timer_ticks!=0)) {timer_ticks=0;timer_sec++;}
  if ((timer_sec%60==0)&&(timer_sec!=0)) {timer_sec=0;timer_min++;}
  if ((timer_min%60==0)&&(timer_min!=0)) {timer_min=0;timer_hrs++;}
}



void timer_install()
{
    /* Installs 'timer_handler' to IRQ0 */
    irq_install_handler(0, timer_handler);
}
