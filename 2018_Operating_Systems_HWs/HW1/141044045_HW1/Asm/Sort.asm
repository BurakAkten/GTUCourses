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
N:	DB 50 ; holds the number of items in array
I:	DB 00H ; beginning of the array
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

    MVI H,0 ; I=0
	LXI B,array ; load first element address to BC


sort_while1:
	LDA N ; A = 50
	DCR A ; A = A-1

	JZ exit ; if A==0 then go exit

	STA N ; save A to N

	MVI H,0 ; index = 0
	LXI B,array ; initialize the address of the array to BC


sort_while2:
	LDA N ; load N again
	SUB H ; A = A-H
	JZ sort_while1 ;if  A == 0 then go sort_while1

control:
	LDAX B ; A = array[i] address

	MOV D,A ; D = array[i]

	INX B ; ;increment array index

	LDAX B ; A = array[i + 1]

	CMP D ; a[i+1] - a[i]

	JC swap_after_control ; if a[i+1] < a[i]

	JMP go_on ; go on

swap_after_control:

	LDAX B ; a = array[i + 1]

	MOV E,A ;  E = A (temp)

	MOV A,D ; A = array[i]

	STAX B ; arr[i+1] = d

	DCX B

	MOV A,E ;A = E

	STAX B ; array[i] = A

	INX B

go_on:
	INR H
	JMP sort_while2

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

