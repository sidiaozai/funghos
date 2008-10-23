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



#include <stdio.h>



char *gets(char *string) /* insecure, use fgets instead */
{
  unsigned int i=0;
  char c='\0';
  while (c!='\n') {
    c = getchar();
    if (c=='\n') {
      string[i++]='\0';
      return string;
    } else {
      if (c=='\b') {
	    if (i!=0)
	      string[i--]=' ';
      } else {
	    string[i++]=c;
      }
    }
  }
}
