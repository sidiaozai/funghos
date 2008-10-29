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
  struct header *h  = FIRST_HEADER;
  struct header *i;
  struct header *j;
  
  
  while ((h->used) || ((h->next - (h + sizeof(struct header))) < size))
    h = h->next;
  
  h->used = 1; //set the used bit
  i = h->next; // store the old next ptr
  h->next = (struct header *) h + sizeof(struct header) + size; // create the new one
  j = (struct header *) h->next;
  j->next = i; // write the ptr in the linked list
  
  return (h+sizeof(struct header));
}
