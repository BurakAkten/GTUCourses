     ; 8080 assembler code
        .hexfile BinarySearch.hex
        .binfile BinarySearch.com
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
	; this file create a random array and sort it. Then make linear search after take number from user.
	;The program make linear search becasue I did not finished the binary search properly then  I make the linear search.

	ORG 8000H
array ds 50 ; will keep the array
	
	ORG 0700H
N:	DB 50 ; holds the number of items in array
I:	DB 00H ; beginning of the array

error:  DW 'Number is not in the array!!',00AH,00H ; null terminated string
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
    MVI A, READ_B
    call GTU_OS 	

    MOV E,B ; store the target number into reg E

    LXI B,array ; 
    
search:
    LDAX B ; take the number from array
    SUB E ; make A - E
    JZ item_found ; if A - E == 0 then print the index
    INX B ; increment the address

    LDA I ; A = I (index)
    INR A ; A++
    STA I ; index incremented
    SUI 50 ; 
    JNZ search ; I - 50 != 0

no_item:
    LXI B, error ; Load the message into the reg B to print on the screen
    MVI A, PRINT_STR ; 
    call GTU_OS ; 
    
    JMP exit2 ;

item_found:
    LDA I ;  A = I (index)
    MOV B,A ; B  = A
    MVI A,PRINT_B ; 
    call GTU_OS ; 
    HLT

exit2:
  HLT    ; end program




