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
#include <screen/win.h>

#ifndef MULTITASKING_H
#define MULTITASKING_H

// default time slice for a process
#define DEF_TIMESLICE 10000

// process states
#define PRCURR   0x1
#define PRREADY  0x2
#define PRRECV   0x3
#define PRSLEEP  0x4
#define PRSUSP   0x5
#define PRWAIT   0x6

typedef struct process {
  unsigned int pid;
  unsigned char state;
  unsigned int esp;    //actual position of esp
  unsigned int ss;     //actual stack segment.
  unsigned int kstack; //stacktop of kernel stack
  unsigned int ustack; //stacktop of user stack
  unsigned int cr3;
  unsigned int owner;
  unsigned int group;
  unsigned int timetorun;
  unsigned int sleep;
  unsigned int priority;
  struct win *window;
  // memtree_t *vmm_alloc; //memory management info concerning the process 
  unsigned char name[32];
  struct process *next;
} process_t;


typedef struct {
  unsigned short backlink, __blh;
  unsigned int esp0;
  unsigned short ss0, __ss0h;
  unsigned int esp1;
  unsigned short ss1, __ss1h;
  unsigned int esp2;
  unsigned short ss2, __ss2h;
  unsigned int cr3;
  unsigned int eip;
  unsigned int eflags;
  unsigned int eax, ecx, edx, ebx;
  unsigned int esp, ebp, esi, edi;
  unsigned short es, __esh;
  unsigned short cs, __csh;
  unsigned short ss, __ssh;
  unsigned short ds, __dsh;
  unsigned short fs, __fsh;
  unsigned short gs, __gsh;
  unsigned short ldt, __ldth;
  unsigned short trace, bitmap;
} tss_t;

typedef struct q_tt {
  process_t *proc;
  struct q_tt *next;
} q_t;

typedef void (*entry_t)(void);


extern process_t *task_curr;


#endif
