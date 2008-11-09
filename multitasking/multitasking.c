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
#include "multitasking.h"


#define KSTACKEND 1081048


process_t *task_curr; // global ptr to current task
process_t *task_new; // used when switching process's
process_t *lastproc;
unsigned int kstackend = KSTACKEND; // not sure about this


static q_t *ready_f = 0;
static q_t *ready_l = 0;


void schedule();
void q_ready_add(process_t *p);


process_t *task_create(entry_t entry,int priority){
  //various initialization stuff may be done before reaching the below described operations.
  //filling in the kstack for start up:
  unsigned int  *stacksetup; //temporary pointer - will be set to the kstacktop
                             //and afterwards saved in esp of proc structure
  stacksetup=malloc(16)+16;  // ugh.. hope this works..
  *stacksetup--;
  *stacksetup--=0x0202;
  *stacksetup--=0x08;
  *stacksetup--=(unsigned int)entry; //This is the adress of the process' entry point (i.e. main());
  *stacksetup--=0;    //ebp
  *stacksetup--=0;    //esp
  *stacksetup--=0;    //edi
  *stacksetup--=0;    //esi
  *stacksetup--=0;    //edx
  *stacksetup--=0;    //ecx
  *stacksetup--=0;    //ebx
  *stacksetup--=0;    //eax
  *stacksetup--=0x10; //ds
  *stacksetup--=0x10; //es
  *stacksetup--=0x10; //fs
  *stacksetup--=0x10; //gs

  // creating and allocating the struct
  process_t *newproc;
  if ((newproc = malloc(sizeof(process_t))) == NULL)
    panic("Can't allocate memory for newproc.");

  newproc->esp = (unsigned int) stacksetup;
  newproc->ss = 0x10;
  //newproc->kstack = (unsigned int)&kstacks[d][KSTACKTOP];
  //newproc->ustack = (unsigned int)&stacks[d][USTACKTOP];
  newproc->next = NULL;

  lastproc->next = newproc; // put the process in the last addr ptr
  lastproc = newproc;

  return newproc;
}


void q_ready_add(process_t *p)
{
  if (ready_l)
  {
    ready_l->proc = p;
    ready_l->next = malloc(sizeof(q_t));
    ready_l = ready_l->next;
  } else {
    ready_f = malloc(sizeof(q_t));
    ready_f->next = malloc(sizeof(q_t));
    ready_f->proc = p;
    ready_l = ready_f->next;
  }
}


q_t *q_ready_getf()
{
  q_t *ret;
  ret = ready_f;
  ready_f = ready_f->next;
  return ret;
}


//the isr
void timer_handler2 (struct regs *r) {
  if(task_curr->timetorun>0) {
    task_curr->timetorun--;
  } else {
    task_curr->esp = r->esp;
    task_curr->ss = r->ss;
    schedule();
  }
}


//the scheduler:
void schedule() {

  if ( task_curr->timetorun<1 ) {
    q_ready_add(task_curr);
    task_new = q_ready_getf();
    task_new->timetorun = DEF_TIMESLICE;
    ctxsw();
  }
}



void ctxsw()
{
  // does the actual context switch
  __asm__ ("cli"); // disable interrupts
  
  // 1. save the things to the task_curr
  
  __asm__ ("movl %%esp, %0;"
	   :"=r"(task_curr->esp)        /* output */
	   );
  
  __asm__ ("movl %%ss, %0;"
	   :"=r"(task_curr->ss)        /* output */
	   );

  task_curr = task_new; // change the task_curr pointer

  // 2. restore things from task_new

  __asm__ ("movl %0, %%esp;"
	   :
	   :"r" (task_curr->esp)
	   );

  __asm__ ("movl %0, %%ss;"
	   :
	   :"r" (task_curr->ss)
	   );
  
  __asm__ ("sti"); // enable interrupts again
}
