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



WIN window[WINMAX];
int currwin = 0;



void scwin(int winnum); /* scrolls a window */
int rtwin(int type); /* system function, returns a lot of values */
void drwin(int winnum); /* draws a window, system */
int mkwin(int x, int y, int x2, int y2); /* creates a new window */
int rmwin(int winnum, int pid); /* removes a window */



void scwin(int winnum) {
  screen_no_scroll=TRUE;
  puts("Press any key to continue...");
  (void) getchar();
  screen_no_scroll=FALSE;
  drwin(winnum);
  txtclr(TXTFOREGROUND,TXTBACKGROUND);
  csr_x = window[winnum].x+1;
  csr_y = window[winnum].y+1;
}



int rtwin(int type) {
  if (type==CSRX) return (window[currwin].x);

  if (type==WINEND) { 
    if (csr_x>=window[currwin].x2) {return TRUE;} else {return FALSE;}
  }
  if (type==WINSCROLL) {
    if (csr_y>=(window[currwin].y2-1)) {return TRUE;} else {return FALSE;}
  }
    if (type==CSRY2) return (window[currwin].y2);
    if (type==CSRY) return (window[currwin].y);
    if (type==CSRX2) return (window[currwin].x2);
}



void drwin(int winnum) {
  unsigned short bg,fg;
  bg = BD_BG_NORM;
  fg = BD_FG_NORM;
  txtclr(fg,bg);
  csr_x = window[winnum].x;
  csr_y = window[winnum].y;
  putcha(UPLEFTCORNER);
  while (csr_x<=(window[winnum].x2-1)) {
    putcha(UPBORDER);
  } /* horni 'obruba' okna */
  putcha(UPRIGHTCORNER);

  csr_y=window[winnum].y+1;
  csr_x=window[winnum].x;
  int tmp=0;
  while (tmp==0) {
    if (csr_x==window[winnum].x||csr_x==window[winnum].x2) {
          txtclr(fg,bg);
          putcha(SIDEBORDER);
        } else {
          if (csr_x<window[winnum].x2) {
          txtclr(WINFOREGROUND,WINBACKGROUND);
          putcha(' ');
          } else {csr_y++;csr_x=window[winnum].x;}
        }
        if (csr_y==window[winnum].y2) {tmp=1;}
  }
  /* okraje + vnitrky oken, nejdulezitejsi cast:D */

  csr_x=window[winnum].x;
  csr_y=window[winnum].y2; /* mozna zbytecne ?! */
  txtclr(fg,bg);
  putcha(DOWNLEFTCORNER);
  while (csr_x<=(window[winnum].x2-1)) {
    putcha(DOWNBORDER);
  }
  putcha(DOWNRIGHTCORNER);
  csr_x=window[winnum].x+1;
  csr_y=window[winnum].y+1;
  move_csr();
 /* dolni 'obruba' okna */
 txtclr(TXTFOREGROUND,TXTBACKGROUND);
 /* nutne opet nastavit default, aby clovek nepsal v 'oknove' barve */
}



int mkwin(int x, int y, int x2, int y2) {
  int pid = 27; //random number
  static int lcorn=1; static int uline=1;
  if (x==0||x<0) {x=lcorn; lcorn++;}
  if (y==0||y<SYSLINE) {y=uline+SYSLINE; uline++; }
  if (x2==0||x2<x) {x2=x+WINSIZEX; }
  if (y2==0||y2<y) {y2=y+WINSIZEY; }
  
  /* zjisti volne okno, a tam se umisti */
  int i,end=0;
  for (i=0;window[i].pid;i++) ;
  window[i].x=x; window[i].y=y; window[i].x2=x2; window[i].y2=y2; window[i].pid=pid;
  currwin=i;
  drwin(i);
  return i;
}

int rmwin(int winnum, int pid) {
  if (pid==window[winnum].pid) {
    window[winnum].pid=0; window[winnum].x=0; window[winnum].y=0;
    window[winnum].x2=0; window[winnum].y2=0;
    return OK;
  } else {
    return SECURITYERROR;
  }
}

