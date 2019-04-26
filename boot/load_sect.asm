; load 'dh' sectors from drive 'dl' into ES:BX
disk_load:
    pusha
    ; save registers values in stack untill we finish reading from disk 
    push dx

    mov ah, 0x02 ; ah <- int 0x13 function. 0x02 = 'read'
    mov al, dh   ; number of sectors to read provided as a parameter in main the code 
    mov cl, 0x02 ; sector number     
    mov ch, 0x00 ; cylinder number
    mov dh, 0x00 ; head number 

    int 0x13      ; BIOS interrupt
    jc disk_error ; if error 
    pop dx
    cmp al, dh    ; BIOS also sets 'al' to the # of sectors read. Compare it.
    jne sectors_error
    popa
    ret


disk_error:
    mov bx, DISK_ERROR
    call print
    call print_nl
    mov dh, ah     
    call print_hex  
    jmp disk_loop

sectors_error:
    mov bx, SECTORS_ERROR
    call print

disk_loop:
    jmp $

DISK_ERROR: db "Disk read error", 0
SECTORS_ERROR: db "Incorrect number of sectors read", 0
