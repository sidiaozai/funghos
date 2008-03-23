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



[global read_cr0]
read_cr0:
	mov eax, cr0
	retn

[global write_cr0]
write_cr0:
	push ebp
	mov ebp, esp
	mov eax, [ebp+8]
	mov cr0,  eax
	pop ebp
	retn

[global read_cr3]
read_cr3:
	mov eax, cr3
	retn

[global write_cr3]
write_cr3:
	push ebp
	mov ebp, esp
	mov eax, [ebp+8]
	mov cr3, eax
	pop ebp
	retn