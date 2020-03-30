     ; 8080 assembler code
        .hexfile Sort.hex
        .binfile Sort.com
        ; try "hex" for downloading in hex format
        .download bin
        .objcopy gobjcopy
        .postbuild echo "OK!"
        ;.nodump

	; OS call list
PRINT_B		equ 1
PRINT_MEM	equ 2
READ_B		equ 3
READ_MEM	equ 4
PRINT_STR	equ 5
READ_STR	equ 6
GET_RND     equ 7

	; Position for stack pointer
stack   equ 0F000H

	org 0000H
	jmp begin

	; Start of our Operating System
GTU_OS:	PUSH D
	push D
	push H
	push psw
	nop	; This is where we run our OS in C++, see the CPU8080::isSystemCall()
		; function for the detail.
	pop psw
	pop h
	pop d
	pop D
	ret
	; ---------------------------------------------------------------
	; YOU SHOULD NOT CHANGE ANYTHING ABOVE THIS LINE
	; this file sorts numbers with bubble sort

	ORG 8000H
array ds 50 ; will keep the array
	
	ORG 0700H
N:	DB 50 ; number of items to compare
I:	DB 00B ; index for print array
	ORG 000DH
begin:
    LXI SP,stack 	; always initialize the stack pointer

    MVI C,50 ; C = 50
    LXI H, array ; initialize the address of the array to HL


fill_array:
    MVI A, GET_RND ; store the system call on reg A 
    call GTU_OS ; call the siytem call
   

    MOV M,B ; array[i] = B

    INR L ; HL += 1

    DCR C ; C -= 1

    JNZ fill_array ; if c!= 0

    MVI B , 0
    LXI H, array ; initialize the address of the array to HL


sort_while:
	LDA N ; N = 50	
	DCR A; size = size - 1

	JZ exit ; if size == 0

	STA N ; save A to N

	MVI B , 0
    LXI H, array ; initialize the address of the array to HL

sort_for:
	
	LDA N; load N again
	
	SUB B; N - H into A

	JZ sort_while  ;

control:
	MOV A , M ;A = array[i] address

	MOV D , A ; D = array[i]

	INX H     ;increment array index

	;INX H

	MOV A , M 		; B = array[i + 1]

	CMP D ; compere (i)th and (i + 1)th element

	JC swap_after_cont ; if array[i + 1] < array[i]

	JMP go_on


swap_after_cont:
	
	MOV A ,M ; a = array[i + 1]

	MOV E , A ; E = A (temp)

	MOV A , D ; A = array[i]

	MOV M ,A ; array[i + 1] = A

	DCX H  ; decrement array index

	;DCX H

	MOV A , E ; A = E

	MOV M , A ; array[i] = A

	INX H   ; increment array index

	;INX H


go_on:
	
	INR B ; increment H
	JMP sort_for


exit:
	MVI C,50 ; C = 50
    LXI H, array ; initialize the address of the array to HL

print:
	
	MOV B , M ; b = array[i]

	MVI A, PRINT_B ; store the system call on reg A 
    call GTU_OS ; call the siytem call
   
	
	INR L ; HL += 1

    DCR C ; C -= 1

    JNZ print ; if c!= 0

	HLT ;












	

	


