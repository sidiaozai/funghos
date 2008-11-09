;    (c) 2008 Jan Dlabal <dlabaljan@gmail.com>
;                                                                            
;     This file is part of FunghOS.                                          
;                                                                            
;     Funghos is free software: you can redistribute it and/or modify        
;     it under the terms of the GNU General Public License as published by   
;     the Free Software Foundation, either version 3 of the License, or      
;     any later version.                                                     
;                                                                            
;     FunghOS is distributed in the hope that it will be useful,             
;     but WITHOUT ANY WARRANTY; without even the implied warranty of         
;     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          
;     GNU General Public License for more details.                           
;                                                                            
;     You should have received a copy of the GNU General Public License      
;     along with FunghOS. If not, see <http://www.gnu.org/licenses/>.        

[EXTERN task_curr] ; pointer to current task
[EXTERN kstackend] ; ? ? ?
	
%macro REG_SAVE 0
      ;save all registers in the kernel-level stack of the process and switch to the kernel stack
        cld
        pushad
        push ds
        push es
        push fs
        push gs
        mov eax,[task_curr] ;put the adress of the struct of CURRENT PROCESS in eax.(the CONTENT of pointer p)
        mov [eax],esp ;save esp in the location of esp in the CURRENT PROCESS-STRUCT.
        lea eax,[kstackend] ; switch to the kernel's own stack.
        mov esp,eax
%endmacro

%macro REG_RESTORE_MASTER 0
        mov eax,[task_curr] ;put adress of struct of current process in eax.
        mov esp,[eax] ;restore adress of esp.
        mov ebx,[eax+8];put content of the k-stack field into ebx.
        ;mov [sys_tss+4],ebx update system tss
        mov al,0x20
        out 0x20,al
        pop gs
        pop fs
        pop es
        pop ds
        popad
        iretd
%endmacro

	;and here is an example isr.
[EXTERN timer_handler]
[GLOBAL hwint00]
hwint00:
          REG_SAVE
          call timer_handler
          REG_RESTORE_MASTER
