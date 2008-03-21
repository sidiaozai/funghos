#include <system.h>
#include <stdio.h>



 typedef struct {
    int x;
    int y;
    int x2;
    int y2;
    int pid;
  } WIN;



WIN window[WINMAX+1];
int currwin = 0;



void scwin(int winnum); /* scrolls a window */
int rtwin(int type); /* system function, returns a lot of values */
void drwin(int winnum); /* draws a window, system */
int mkwin(int x, int y, int x2, int y2, int pid); /* creates a new window */
int rmwin(int winnum, int pid); /* removes a window */



void scwin(int winnum) {
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
    if (csr_y>=(window[currwin].y2)) {return TRUE;} else {return FALSE;}
  }
    if (type==CSRY2) return (window[currwin].y2);
    if (type==CSRY) return (window[currwin].y);
    if (type==CSRX2) return (window[currwin].x2);
}



void drwin(int winnum) {
  csr_x = window[winnum].x;
  csr_y = window[winnum].y;
  txtclr(BDFOREGROUND,BDBACKGROUND);
  while (csr_x<=window[winnum].x2) {
    putcha(' ');
  } /* horni 'obruba' okna */

  csr_y=window[winnum].y+1;
  csr_x=window[winnum].x;
  int tmp=0;
  while (tmp==0) {
    if (csr_x==window[winnum].x||csr_x==window[winnum].x2) {
	  txtclr(BDFOREGROUND,BDBACKGROUND);
	  putcha(' ');
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
  txtclr(BDFOREGROUND,BDBACKGROUND);
  while (csr_x<=window[winnum].x2) {
    putcha(' ');
  }
  csr_x=window[winnum].x+1;
  csr_y=window[winnum].y+1;
  move_csr();
 /* dolni 'obruba' okna */
 txtclr(TXTFOREGROUND,TXTBACKGROUND);
 /* nutne opet nastavit default, aby clovek nepsal v 'oknove' barve */
}



int mkwin(int x, int y, int x2, int y2, int pid) {
  static int lcorn=0; static int uline=0;
  if (x==0||x<0) {x=lcorn; lcorn++;}
  if (y==0||y<SYSLINE) {y=uline+SYSLINE; uline++; }
  if (x2==0||x2<x) {x2=x+WINSIZEX; }
  if (y2==0||y2<y) {y2=y+WINSIZEY; }
  
  /* zjisti volne okno, a tam se umisti */
  int i,end=0;
  for (i=0;end!=1;++i) {
    if (window[i].pid==0) {end=1;}
  }
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
