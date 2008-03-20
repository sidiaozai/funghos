#include <system.h>
#include <stdio.h>
#include <apps/timer.h>



void stopwatch()
{
  static int running=0;
  while (1) {
  if (!running) {
    mkwin(34,10,46,15,0);
    txtclr(RED,LIGHT_GREY);
    puts("Stopwatch\n");
    txtclr(BLUE,LIGHT_GREY);
    running=TRUE;
    timer_hrs=timer_min=timer_sec=timer_ticks=0;
    puti(0);puti(timer_hrs);putch(':');puti(0);puti(timer_min);putch(':');puti(0);puti(timer_sec);
  } else {
    csr_x=rtwin(CSRX)+1;
    ///    puts("\b\b\b\b\b\b\b\b");

    if (timer_hrs<10) {puti(0);puti(timer_hrs);putch(':');} else {puti(timer_hrs);putch(':');}

    if (timer_min<10) {puti(0);puti(timer_min);putch(':');} else {puti(timer_min);putch(':');}

    if (timer_sec<10) {puti(0);puti(timer_sec);} else {puti(timer_sec);}

  }
  }
}
