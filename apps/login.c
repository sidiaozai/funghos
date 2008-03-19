#include <stdio.h>
#include <system.h>


void login(int x)
{
  
  static char username[15];
  static char password[15];
  if (x==0) {
    strcpy(username,"");
    strcpy(password,"");
    int i;
    int loginwin=mkwin(30,9,50,16,1);
    static int ok=FALSE;
    txtclr(WHITE,BLUE);
    puts("      Welcome!     "); /* \n */
    puts("      Login:       "); /* \n */
    puts("     ");
    txtclr(BLACK,WHITE);
    puts("         ");
    txtclr(WHITE,BLUE);
    puts("     "); /* \n */
    puts("     Password:     "); /* \n */
    puts("     ");
    txtclr(BLACK,WHITE);
    puts("         ");
    txtclr(WHITE,BLUE);
    puts("     "); /* \n */
    puts("                  ");
    putcha(' ');
    csr_x=36;
    csr_y=12;
    move_csr();
    txtclr(RED,WHITE);
    gets(username);
    login(1);
  }


if (x==1) {
  csr_x=36;
  csr_y=14;
  move_csr();
  gets(password);
  login(2);
}


 if (x==2) {
   int userok=strcmp(username,"user");
   int passok=strcmp(password,"password");
   if (userok==0&&passok==0) {
     cmd_install();
   } else {
     puts("\nBad username\nor password...");
     login(0);
   }
 }

} /* konec funkce */
