/* win.c - functions for creating, removing, drawing & editing windows */
#include "system.h"

 typedef struct {
    int x;
    int y;
    int x2;
    int y2;
    int pid;
  } WIN;

WIN window[WINMAX+1];

int currwin = 0;

/* funkce na 'scrollovani' oken */
void scwin(int winnum) {
  /* je treba:
     1/ smazat prvni radek okna
     2/ prepsat ho druhym radkem
     3/ smazat druhy radek okna......
     ZATIM JEN MAZE OKNO, "REDIRECT"
  */
  drwin(winnum);
  txtclr(TXTFOREGROUND,TXTBACKGROUND);
  csr_x = window[winnum].x+1;
  csr_y = window[winnum].y+1;
  
}



/* funkce ktera jenom vraci ruzne blbosti */
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
/* zde je jiz konec funkce ! */




/* funkce pro putch, rika kam hodit znak */
int wherewin(int type) {
  //int static nextline=FALSE;

  if (type==CSRX) {
    if (csr_x<=window[currwin].x) {
      return (window[currwin].x+1); /* pokud je pred zacatkem okna, hodit ho na*/ 
    }			       /*prvni misto ZA obrubou */
    
    if (csr_x>=window[currwin].x2) {
      //nextline=TRUE;
      return (window[currwin].x+1);
    }
  }

  // if (type==CSRY&&nextline==TRUE) {
  //  csr_y++;
  // }

  if (type==CSRY) {
    if (csr_y<=window[currwin].y) {
      return (window[currwin].y+1);
    }
    if (csr_y>=window[currwin].y2) {
      scwin(currwin);
      return (window[currwin].y2-1);
    }
  }
}

/* funkce na 'kresleni' oken, volana systemem */
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
  /// DEBUG!
  csr_x=window[winnum].x+1;
  csr_y=window[winnum].y+1;
  move_csr();
#ifdef DEBUG
puts("TEST");
#endif /* dolni 'obruba' okna */
 txtclr(TXTFOREGROUND,TXTBACKGROUND);
 /* nutne opet nastavit default, aby clovek nepsal v 'oknove' barve */
}


/* mkwin -- create a new window
 * parametry: x,y - souradnice, kde 'zacina' okno.
 *            x2,y2 - souradnice, kde 'konci' okno.
 */
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

int wrwin(int winnum, int pid, int line, char *str[]) {
  if (pid==window[winnum].pid) {
    csr_x=window[winnum].x+1;
    csr_y=window[winnum].y+line;
    txtclr(TXTFOREGROUND,TXTBACKGROUND);
    puts(str);
  } else {
    return SECURITYERROR;
  }
}
