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
#include "win.h"



WIN *first_window;
WIN *currwin;



void scwin(WIN *window); /* scrolls a window */
int rtwin(int type); /* system function, returns a lot of values */
void drwin(WIN *window); /* draws a window, system */
int mkwin(int x, int y, int x2, int y2); /* creates a new window */
int rmwin(int winnum, int pid); /* removes a window */



void scwin(WIN *window) {
  screen_no_scroll=TRUE;
  puts("Press any key to continue...");
  (void) getchar();
  screen_no_scroll=FALSE;
  drwin(window);
  txtclr(TXTFOREGROUND,TXTBACKGROUND);
  csr_x = (window->x)+1;
  csr_y = (window->y)+1;
}



int rtwin(int type) {
  if (type==CSRX) {
	return (currwin->x);
  }
  
  if (type==WINEND) { 
    if (csr_x >= (currwin->x2)) {
	  return TRUE;
	} else {
	  return FALSE;
	}
  }
  
  if (type==WINSCROLL) {
    if ( (csr_y) >= ((currwin->y2)-1) ) {
	  return TRUE;
	} else {
	  return FALSE;
	}
  }
  
  if (type==CSRY2) return (currwin->y2);
  if (type==CSRY) return (currwin->y);
  if (type==CSRX2) return (currwin->x2);
}



int mkwin(int x, int y, int x2, int y2) {
  
  static unsigned int lcorn = 0;
  static unsigned int uline = 0;

  if (x==0||x<0)
    x=lcorn++;

  if (y==0||y<0)
    y=uline++;

  if (x2==0||x2<x)
    x2=x+WINSIZEX;

  if (y2==0||y2<y)
    y2=y+WINSIZEY;

  /* store the windows' data somewhere */

  WIN *new;

  new = malloc(sizeof(WIN));

  new->x    = x;
  new->y    = y;
  new->x2   = x2;
  new->y2   = y2;
  new->next = NULL;

  /* find the end of the windows' queue */

  WIN *tmp;

  tmp =& first_window;

  while (tmp->next != NULL)
    tmp =& tmp->next;

  tmp->next =& new;

  currwin = new;

  drwin(new);

}



void drwin(WIN *window) {
  csr_x = window->x;
  csr_y = window->y;
  txtclr(BDFOREGROUND,BDBACKGROUND);
  putcha(UPLEFTCORNER);
  while (csr_x<=((window->x2)-1)) {
    putcha(UPBORDER);
  } /* horni 'obruba' okna */
  putcha(UPRIGHTCORNER);

  csr_y=(window->y)+1;
  csr_x=window->x;

  int tmp=0;

  while (tmp==0) {
    if (csr_x==(window->x)||csr_x==(window->x2)) {
      txtclr(BDFOREGROUND,BDBACKGROUND);
      putcha(SIDEBORDER);
    } else {
      if (csr_x<(window->x2)) {
	txtclr(WINFOREGROUND,WINBACKGROUND);
	putcha(' ');
      } else {csr_y++;csr_x=(window->x);}
    }
    if (csr_y==(window->y2)) {tmp=1;}
  }
  /* okraje + vnitrky oken, nejdulezitejsi cast:D */

  csr_x=window->x;
  csr_y=window->y2; /* mozna zbytecne ?! */
  txtclr(BDFOREGROUND,BDBACKGROUND);
  putcha(DOWNLEFTCORNER);
  while (csr_x<=((window->x2)-1)) {
    putcha(DOWNBORDER);
  }
  putcha(DOWNRIGHTCORNER);
  csr_x=(window->x)+1;
  csr_y=(window->y)+1;
  move_csr();
 /* dolni 'obruba' okna */
 txtclr(TXTFOREGROUND,TXTBACKGROUND);
 /* nutne opet nastavit default, aby clovek nepsal v 'oknove' barve */
}



int rmwin(int winnum, int pid)
{
}
