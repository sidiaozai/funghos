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
#include <mem/paging.h>
#include <mem/mem.h>



void *malloc(unsigned int size)
{
  /* 1/ find a free page
     2/ find a free header
     3/ mark it as used
     4/ twidling with pointerz
     5/ return its address
   */

  HEADER *header_curr = FIRST_HEADER;

  while ((!header_curr->free)&&(header_curr->next-header_curr>=size))
  {
    palloc(header_curr->next, header_curr->next);
    header_curr =& header_curr->next;
  }
  header_curr->free=FALSE;
  unsigned int tmp = header_curr->next;
  header_curr->next=header_curr+size+1;
  HEADER *header_next;
  header_next = header_curr->next;
  header_next->next = tmp;
  header_next->free = TRUE;
  palloc(header_curr,header_curr->next);
  return header_curr+1;
}
