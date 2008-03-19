#include <system.h>
#include <stdio.h>



void timer_handler(); /* function called when the timer fires */
void timer_install(); /* installs the timer_handler */



unsigned int ticks=0;
unsigned int ticks_debug=0;




void timer_handler(struct regs *r)
{
  ticks++;
  if ((ticks%100)==0) ticks_debug++;
}



void timer_install()
{
    /* Installs 'timer_handler' to IRQ0 */
    irq_install_handler(0, timer_handler);
}
