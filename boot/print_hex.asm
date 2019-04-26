; pass the parameter to dx 
print_hex:

    pusha
    mov cx, 0 ; counter to loop 4 times 

hex_loop:

    cmp cx, 4 
    je end
    mov ax, dx ; ax is used as a helper register 
    and ax, 0x000f 
    add al, 0x30 
    cmp al, 0x39 
    jle step2
    add al, 7 

step2:
   
    mov bx, HEX_OUT + 5 
    sub bx, cx  
    mov [bx], al 
    ror dx, 4 
    add cx, 1
    jmp hex_loop

end:

    mov bx, HEX_OUT
    call print
    popa
    ret

HEX_OUT:

    db '0x0000',0 
