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



#ifndef MEM_H
#define MEM_H


#define HEADER_SIZE   sizeof(HEADER)  // header_size in bytes
#define FIRST_HEADER  0x400000
#define END_OF_MEMORY 0xFFFFFFFF


extern unsigned long *RAM_pages;

extern unsigned int RAM_kb;

extern void palloc(unsigned int start_addr, unsigned int end_addr);



typedef struct _header {
  unsigned size:12;     /* pages are 4kb = 4096 bytes, 2^12=4096 */
  unsigned free:1;
  unsigned big:1;       /* should handle blocks bigger than 4kb */
  unsigned flags:2;
} _HEADER;

typedef struct header {
  char used;      /* if set, that means that this block is free,
			 * so it can be used to allocate new memory.
			 */
  struct header *next;  /* this is simply a pointer to the next header,
			 * so malloc() can simply browse headers to find
			 * an empty one.
			 */
} HEADER;

#endif
