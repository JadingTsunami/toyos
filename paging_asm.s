global enable_paging
global enable_paging_identity

enable_paging:
; load page directory (eax has the address of the page directory) 
   mov eax, [esp+4]
   mov cr3, eax
   mov ebx, cr0
   or  ebx, 0x80000000 ; set PG
   mov cr0, ebx        ; update cr0
   ret                 ; now paging is enabled


enable_paging_identity:
; load page directory (eax has the address of the page directory) 
   mov eax, [esp+4]
   mov cr3, eax
   ; set PSE
   mov eax, cr4
   or eax, 0x00000010
   mov cr4, eax
   mov ebx, cr0
   or  ebx, 0x80000000 ; set PG
   mov cr0, ebx        ; update cr0
   ret                 ; now paging is enabled

