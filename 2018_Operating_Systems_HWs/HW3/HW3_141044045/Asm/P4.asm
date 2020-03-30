; 8080 assembler code
.hexfile P1.hex
.binfile P1.com
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
GET_RND		equ 7
TCreate		equ 11
TExit		equ 8
TJoin		equ 9
TYield		equ 10
FileCreate		equ 12
FileClose		equ 13
FileOpen		equ 14
FileRead		equ 15
FileWrite		equ 16
FileSeek		equ 17
DirRead		equ 18



; Position for stack pointer
stack   equ 0F000h

org 000H
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

;This program tests each of the system calls one by one.

num ds 2 ;
name ds 100 ; 


begin:
	

	LXI b, name  ;

	;;take  a string and display it on the screen
	MVI A, READ_STR	; store the OS call code to A
	call GTU_OS	; call the OS

	MVI A, FileOpen	; store the OS call code to A
	call GTU_OS	; call the OS

	MVI C, 0
	

read:
	
	MOV A, C ; A = C
	STA NUM ; num = A

	LXI B, NUM ;bc = num

	MVI E, 0  ;fileıd
	MVI D, 2  ;byte number


	MVI A, FileRead	; store the OS call code to A
  	call GTU_OS	; call the OS



  	MVI C, 10



write:
	MOV A, C ; A = C
	
	STA NUM  ; NUM = A

	LXI B, NUM ;bc = num
	MVI E, 0  ;fileıd
	MVI D, 2  ;byte number

	MVI A, FileWrite	; store the OS call code to A
  	call GTU_OS	; call the OS

  	MOV A, C ; A = C
  	DCR C    ; C--
  	DCR C    ; C--


  	JNZ write

  	MOV B, E

  	MVI A, FileClose	; store the OS call code to A
  	call GTU_OS	; call the GTU_OS
	

 	HLT