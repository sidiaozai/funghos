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



struct win *first_window;
struct win *currwin;



void scwin(struct win *window); /* scrolls a window */
int rtwin(int type); /* system function, returns a lot of values */
void drwin(struct win *window); /* draws a window, system */
int mkwin(int x, int y, int x2, int y2); /* creates a new window */
int rmwin(struct win *window); /* removes a window */



void scwin(struct win *window) {
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
  static int init = 0;
  static unsigned int lcorn = 1;
  static unsigned int uline = 1;

  if (x==0||x<0)
    x=lcorn++;

  if (y==0||y<0)
    y=uline++;

  if (x2==0||x2<x)
    x2=x+WINSIZEX;

  if (y2==0||y2<y)
    y2=y+WINSIZEY;

  /* store the windows' data somewhere */
  if (!init)
  {
  	first_window = malloc(sizeof(struct win));
  	first_window->x = x;
  	first_window->y = y;
  	first_window->x2 = x2;
  	first_window->y2 = y2;
  	first_window->next = NULL;
  	
  	currwin = first_window;
  	
  	drwin(first_window);
  	
  	init = 1; // init done, from now on use the other part (linked list thingy)
  } else {
  	
    struct win *newin;

    newin = malloc(sizeof(struct win));

    newin->x    = x;
    newin->y    = y;
    newin->x2   = x2;
    newin->y2   = y2;
    newin->next = NULL;

    /* find the end of the windows' queue */

    struct win *tmp;

    tmp = first_window;

    while (tmp->next != NULL)
      tmp = tmp->next;

    tmp->next = newin;

    currwin = newin;

    drwin(newin);
  }

}



void drwin(struct win *window) {
  csr_x = window->x;
  csr_y = window->y;
  txtclr(BD_FG_NORM,BD_BG_NORM);
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
      txtclr(BD_FG_NORM,BD_BG_NORM);
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
  txtclr(BD_FG_NORM,BD_BG_NORM);
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



int rmwin(struct win *window)
{
  struct win *tmp;
  tmp = first_window;
  if (tmp == window)
  {
  	first_window = tmp->next;
  } else {
    while (tmp->next != window)
      tmp = tmp->next;
    tmp->next = window->next;
  }
  if (currwin == window) // if the killed window was the current one, select another one
    currwin = tmp;		 // the "alghortim" for selecting the new one is as you see
  						 // pretty simple. random. LOL. This may be changed in future.
  free(window);
  cls();
  tmp = first_window;
  while (tmp)			 // redraw all the windows. This is subject to change in future
  						 // to preserve what window was on top of what etc.
  {
    drwin(tmp);
    tmp = tmp->next;
  }
  return 0; // return OK
}
