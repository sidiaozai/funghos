#include <system.h>

/* maze buffer, pripravi na novy prikaz */
void bufdel() {
  int i;
  for (i=0;i<BUFFERSIZE;++i) {kbbuf[i]='\e';}
  kbpos=0;
}

void debug() {
  char x;
  x=getc();
  putch('\n');
  putch(x);
}

void help(int x) {
  bufdel();
  puts("Avaible commands are:\n");
  puts("help -- displays this message\n");
  puts("mkwin -- creates a new window\n");
  puts("stopwatch -- the name says it all\n");
}

/* volana kdyz je stisknut Enter, mela by vykonavat prikazy */
void cmdexec() {
  if (strcmp(kbbuf,"mkwin")==0) {
    mkwin(0,0,0,0,30);
  } else {
    if (strcmp(kbbuf,"reset")==0) {
      i_video();
      mkwin(0,0,0,0,24);
    } else {
      if (strcmp(kbbuf,"stopwatch")==0) {
	bufdel();
        stopwatch_on=TRUE;
      } else {
	if (strcmp(kbbuf,"debug")==0) {
	  bufdel();
	  Shutdown();
	} else {
	  if (strcmp(kbbuf,"help")==0) help(0);
      puts("For help, type help :) \n");
	}
      }
    }
  }
  bufdel();
}


void cmd_install() {
  kbprint_on=TRUE;
  cmd_on=TRUE;
  bufdel();
  mkwin(0,0,0,0,2);
  puts("Welcome to HoubOS v0.03.1. \n");
}
