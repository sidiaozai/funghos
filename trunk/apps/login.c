#include <stdio.h>
#include <system.h>



#define USERLEN 15
#define PASSLEN 15



void login(int x)
{
  
  static char username[USERLEN];
  static char password[PASSLEN];
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
    gets(username,USERLEN);
    login(1);
  }


if (x==1) {
  csr_x=36;
  csr_y=14;
  move_csr();
  gets(password,PASSLEN);
  login(2);
}


 if (x==2) {
   int userok=strcmp(username,"user");
   int passok=strcmp(password,"password");
   if (userok==0&&passok==0) {
     cmd_install();
   } else {
     login(0);
   }
 }

} /* konec funkce */
