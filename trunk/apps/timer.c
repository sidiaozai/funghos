/*    (c) 2008 Jan Dlabal <dlabaljan@gmail.com>                               */
/*                                                                            */
/*     This file is part of FunghOS.                                          */
/*                                                                            */
/*     Funghos is free software: you can redistribute it and/or modify        */
/*     it under the terms of the GNU General Public License as published by   */
/*     the Free Software Foundation, either version 3 of the License, or      */
/*     any later version.                                                     */
/*                                                                            */
/*     FunghOS is distributed in the hope that it will be useful,             */
/*     but WITHOUT ANY WARRANTY; without even the implied warranty of         */
/*     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          */
/*     GNU General Public License for more details.                           */
/*                                                                            */
/*     You should have received a copy of the GNU General Public License      */
/*     along with FunghOS. If not, see <http://www.gnu.org/licenses/>.        */



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
