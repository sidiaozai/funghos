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
#include <boot/multiboot.h>



unsigned int RAM_kb;
unsigned long *RAM_pages;



void i_memory(multiboot_info_t *mbd)
{
  if (mbd->flags & 1)
  {
/* puts("\n mbd->mem_lower = "); */
/*     puti((unsigned int) mbd->mem_lower); */
/*     puts("KB\n mbd->mem_upper = "); */
/*     puti((unsigned int) mbd->mem_upper); */
/*     puts("KB\n both = "); */
/*     puti((unsigned int) (mbd->mem_lower + mbd->mem_upper)); */
/*     puts("KB"); */
  }
  /* zjistit velikost RAM */
  RAM_kb = (unsigned int) (mbd->mem_lower) + (mbd->mem_upper);

  i_paging();

  RAM_pages = (unsigned long) malloc(RAM_kb/32);
}
