; hw11translate2Ascii.asm
; Natalie Buchoff
; CMSC 313 Spring 25 MW 10-11:15am
; to assemble: nasm -f elf32 -g -F dwarf -o hw11translate2Ascii.o hw11translate2Ascii.asm
; to link and load: ld -m elf_i386 -o hw11translate2Ascii hw11translate2Ascii.o
; Desc: this program takes the number of bytes of data and prints that data to the screen

SECTION .data ; data section
    inputBuf:
        db  0x83,0x6A,0x88,0xDE,0x9A,0xC3,0x54,0x9A 

SECTION .bss ; variable data goes here
    outputBuf:
        resb 80 ; allocate 80 bytes for ASCII values

SECTION .text
global _start

_start:
    mov esi, inputBuf   ; point to inputbuf with esi (source pointer in memory)
    mov edi, outputBuf  ; point to outputBuf with edi (destination pointer in memory)
    mov ecx, 8          ; 8 bytes we want to convert
the_loop:
    mov al, [esi]; load data from inputBuf into lower byte of ax
    mov ah, al          ; copy the loaded data into high byte too
    shr al, 4; shift values right by 4 to isolate first 4 bits
    call translateChar; convert to ASCII with subroutine
    mov [edi], al; store output
    inc edi             ; move the edi pointer forward 1 byte to the next place to put in an ascii char
    
    ; do the other 4 bits
    mov al, ah          ; put the original data back in al
    and al, 0x0F        ; use masking to isolate the other 4 bits. 0x0F == 00001111 in binary, "and" makes the bits where the 0s are go away
    call translateChar
    mov [edi], al       ; store output char
    inc edi             ; move the edi pointer forward 1 byte

    mov al, 0x20        ; load ascii space char into al
    mov [edi], al       ; add ascii value for a space to the outputBuf
    inc edi
    
    inc esi             ; increment esi to go to the next byte in the inputBuf

    sub ecx, 1          ; subtract 1 from ecx
    cmp ecx, 0          ; compare ecx with 0
    jne the_loop        ; loop if 8 bytes have not been done yet

    mov ebx, 1      ; write the STDOUT file
    mov eax, 4      ; invoke SYS_WWRITE (kernal opcode 4)
    mov ecx, outputBuf
    mov edx, 24     ; 24 bytes in outputBuf
    int 80h
exit:
    mov     ebx, 0      ; return 0 status on exit - 'No Errors'
    mov     eax, 1      ; invoke SYS_EXIT (kernal opcode 1)
    int 80h

translateChar:
    cmp al, 9;
    jle number ; jump to number if al is less than or equal to 9
    add al, 0x7 ; hex 7 is how far past ascii 9 the uppercase letters start, skipped if al is 9 or less
number:
    add al, 0x30 ;add this to the hex value since numbers are between 0x30 and 0x39
    ret     ; return/exit the subroutine
