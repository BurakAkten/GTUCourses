
.data
	userInput: .space 40
	operands:  .byte '+','-','*','/'
	space:     .byte ' '
	dot:       .byte '.'
	msg1:      .asciiz "Please enter the question: "
	msg2:	   .asciiz "\nThe result is : "
	firstN:    .space 20 
	first_1:   .space 10
	first_2:   .space 10
	second_1:  .space 10
	second_2:  .space 10
	secondN:   .space 20
	operand:   .space 3
.text
	main:
		jal takeInput 			#take the expression from user
		
		#initialize
		la $t0, userInput   	#t0 = userInput
		la $t4, operands		#t4 = operands
		la $s1, firstN			#s1 = firstN
		la $s2, secondN			#s2 = secondN
		la $s3, operand 		#s3 = operand
		
		#finding first space's index
		lb $a0 , space 			#$a0 = space
		li $t1, 0				#i = 0
		jal findIndex			#find space index
		la $t0, userInput   	#t0 = userInput
		
		add $a0 , $v0 , $zero 	#$a0 = foundindex + 0
		
		#take first number from string
		li $t1, 0				#i = 0
		jal firstPart			#first number is being copied into firstN
		la $t0, userInput   	#t0 = userInput
		
		#take operand from string
		addi  $a0, $a0 , 1		#$a0 = foundindex + 1 : operand index
		li $t1, 0				#i = 0
		jal takeOperand			#first number is being copied into operand
		la $t0, userInput   	#t0 = userInput
		
		#take second number from string
		addi  $a0, $a0 , 2		#$a0 = foundindex + 1 : operand index
		li $t1, 0				#i = 0
		jal secondPart			#first number is being copied into secondN
		
		####################################################
		
		#initialize
		la $s1, first_1			#s1 = first_1
		la $s2, first_2			#s2 = first_2
		
		#find the index of '.' in first floating point number
		lb $a0 , dot 			#$a0 = space
		li $t1, 0				#i = 0
		la $t0, firstN   		#t0 = firstN
		jal findIndex			#find space index
		la $t0, firstN   		#t0 = firstN
		
		add $a0 , $v0 , $zero 	#$a0 = foundindex + 0
		
		#take first number before first dot.
		li $t1, 0				#i = 0
		jal firstPart			#first number is being copied into first_1
		la $t0, firstN   		#t0 = firstN
		
		#take second number before first dot
		addi  $a0, $a0 , 1		#$a0 = foundindex + 1 : after dot
		li $t1, 0				#i = 0
		jal secondPart			#first number is being copied into first_2
		
		
		####################################################
		
		#initialize
		la $s1, second_1		#s1 = second_1
		la $s2, second_2		#s2 = second_2
		
		#find the index of '.' in second floating point number
		lb $a0 , dot 			#$a0 = space
		li $t1, 0				#i = 0
		la $t0, secondN   		#t0 = secondN
		jal findIndex			#find space index
		la $t0, secondN   		#t0 = secondN
		
		add $a0 , $v0 , $zero 	#$a0 = foundindex + 0
		
		#take first number before second dot.
		li $t1, 0				#i = 0
		jal firstPart			#first number is being copied into second_1
		la $t0, secondN   		#t0 = secondN
		
		#take second number before second dot
		addi  $a0, $a0 , 1		#$a0 = foundindex + 1 : after dot
		li $t1, 0				#i = 0
		jal secondPart			#first number is being copied into second_2
		
		
		##################################################	

		#make numbers digit by using above formula for each number
		
				########first integer########
		la $t0 , first_1		#t0 = first_1
		li $t1 , 1				#i = 1
		jal findDigitValue		#calculates the digit value of high digit
		la $t0 , first_1		#t0 = first_1
		
		div $a0 , $v0 , 10		#for 3 digit = 1000 / 10 = 100
		
		lb $t7, ($t0)  			#getting character at address
		lb $t6 , 1($t4)			#load '-' into $t6
		beq $t7 , $t6 , handleMinus		#if(t0[0] == '-') 
	
	minus1:
		li $a1 , 0				#first_int = 0
		jal makeInteger			
		
		add $s1 , $a1 , $zero	#$s1 = first_int
		
		
				########second integer########
		la $t0 , first_2		#t0 = first_2
		li $t1 , 1				#i = 1
		jal findDigitValue		#calculates the digit value of high digit
		la $t0 , first_2		#t0 = first_2
		
		div $a0 , $v0 , 10		#for 3 digit = 1000 / 10 : 100
		addi $t5 , $a0 , 0		#$t5 = $a0  : first floating point size
		
		li $a1 , 0				#second_int = 0
		jal makeInteger	
		
		add $s2 , $a1 , $zero	#$s2 = second_int

				########third integer########
		la $t0 , second_1		#t0 = second_1
		li $t1 , 1				#i = 1
		jal findDigitValue		#calculates the digit value of high digit
		la $t0 , second_1		#t0 = second_1
		
		div $a0 , $v0 , 10		#for 3 digit = 1000 / 10 : 100
		
		li $a1 , 0				#third_int = 0
		jal makeInteger			
		
		add $s4 , $a1 , $zero	#$s4 = third_int
		
				########forth integer########
		la $t0 , second_2		#t0 = second_2
		li $t1 , 1				#i = 1
		jal findDigitValue		#calculates the digit value of high digit
		la $t0 , second_2		#t0 = second_2
		
		div $a0 , $v0 , 10		#for 3 digit = 1000 / 10 : 100
		addi $t6 , $a0 , 0		#$t6 = $a0  : second floating point size
		
		li $a1 , 0				#forth_int = 0
		jal makeInteger	

		add $s5 , $a1 , $zero	#$s5 = forth_int
		
		####################################################
		
		beq $t5 , $t6 , makeDecision
		blt $t5 , $t6 , x
		blt $t6 , $t5 , y
		
	x:
		li $t0 , 10				#t0 = 10 : for update number
		mul $t5, $t5 , $t0		#$t5 *= 10
		mul $s2, $s2 , $t0		#$s2 *= 10
		blt $t5 , $t6 , x
		beq $t5 , $t6 , makeDecision
	
	y:
		li $t0 , 10				#t0 = 10 : for update number
		mul $t6, $t6 , $t0		#$t6 *= 10
		mul $s5, $s5 , $t0		#$s5 *= 10
		blt $t6 , $t5 , y
		beq $t6 , $t5 , makeDecision
	
	makeDecision:
		lb $t2 , 0($s3)			#$t2 is the operand
		lb $t3 , 0($t4)			#for control '+' $t3 = '+'
		beq $t2 , $t3 , myadd	# if $t2 == '+' goto myadd
		lb $t3 , 1($t4)			#for control '-' $t3 = '-'
		beq $t2 , $t3 , mysub	# if $t2 == '-' goto mysub
		lb $t3 , 2($t4)			#for control '*' $t3 = '*'
		beq $t2 , $t3 , mymul	# if $t2 == '-' goto mymul
		
		####################################################
	
	printResult:
		addi $a1 , $a0 , 0		#$a1 = fix size (after '.')
		
		lb $t1 , 3($t4)			#for control result $t3 = '/' 
		beq $t7 , $t1 , controlMinus
		
		li $v0 , 1
		addi $a0 , $s6 , 0
		syscall
		li $v0 , 11
		lb $a0 , dot
		syscall
		
		addi $a0 , $s7 , 0
		li $t1 , 1				#i = 1
		jal findDigitValue4int
		addi $a3 , $v0 , 0
		
		j comeback
	
	comeback:
		blt $a3 , $a1 , makeEq	#if fix size(after '.') aren't equal
		li $v0 , 1
		addi $a0 , $s7 , 0		
		syscall
		
		#exit
		li $v0, 10 				#to exit program $v0 = 10
		syscall
	
	makeEq:							#to control this kind of output : 25.002  this part 
									#print out the zeros until float part size will equal to fix size
		li $a2 , 10						
		mul $a3 , $a3 , $a2
		li $v0 , 1
		li $a0 , 0
		syscall
		j comeback
	
	controlMinus:
		sub $s6 , $zero , $s6	#$s6 = 0 - $s6 :make $s6 negative
		lb $t7 , 2($t4)			#make $t7 = '*' to ignore first conrol in printResult
		j printResult
	
	handleMinus:
		div $a0 , $a0 , 10		#for 3 digit = 1000 / 10 = 100
		addi $t0 , $t0 , 1		#t0 = t0 + 1
		j minus1
	
	handleMinus4add:
		li $a1 , 0					#temp = 0
		add $a1 , $s1 , $zero		#temp = $s1
		add $s1 , $s4 , $zero		#$s1 = $s4
		add $s4 , $a1 , $zero 		# $s4 = temp	
		
		add $a1 , $s2 , $zero		#temp = $s2
		add $s2 , $s5 , $zero		#$s2 = $s5
		add $s5 , $a1 , $zero 		# $s5 = temp
		
		lb $t7 , 2($t4)			#for control '*' $t3 = '*'
		j mysub
	
	handleMinus4add2:
		sub $s6 , $zero , $s6
		j printResult
	
	handleMinus4sub:
		
		lb $t7 , 3($t4)			#for control result $t3 = '/' 
		j myadd
	
	handleMinus4mul:
		sub $s6 , $zero , $s6
		j printResult
	
	mymul:
		#Ex 12.4 * 11.25  => 1240*1125
		li $a1 , 10
		#addi $a0 , $t6 , 0		#make the size fix(after '.')
		mul $t6 , $t6 , $a1
		mul $t1 , $s1 , $t6		#$t1= $s1*$t6 :make first integer bigger
		mul $t2 , $s4 , $t6		#$t2= $s4*$t6 :make second integer bigger
		add $t1 , $t1 , $s2		#$t1=$t1 + $s2:represent together first number
		add $t2 , $t2 , $s5		#$t2=$t2 + $s5:represent together second number
		mul $t3 , $t1 , $t2		#make mul with big numbers = big result
		mul $t1 , $t6 , $t6 	#calculate a value to div the big result
		div $t3 , $t1 			# $t3 / $t1 
		mflo $s6				#integer part of Result
		mfhi $s7				#remainder
		#div $s7 , $s7 , $t6
		
		lb $a1 , 1($t4)			#for control '-' $t3 = '-'
		beq  $t7 , $a1 , handleMinus4mul
		
		j printResult
	
	mysub:
		lb $t3 , 1($t4)			#for control '-' $t3 = '-'
		beq  $t7 , $t3 , handleMinus4sub
		addi $a0 , $t6 , 0		#make the size fix(after '.')
		sub $s6 , $s1 , $s4		#$s6 = $s1 - $s4
		sub $s7 , $s2 , $s5		#$s7 = $s1 - $s5
		blt $s7,$zero,findResSub
		j printResult
		
	findResSub:
		li $a2 , 10
		mul $a2 , $t6 , $a2
		add $s2 , $s2 , $a2
		sub $s7 , $s2 , $s5		#$s7 = $s2 - $s5
		addi $s1 , $s1 , -1
		sub $s6 , $s1 , $s4		#$s6 = $s1 - $s4
		j printResult
	
	myadd:
		lb $t3 , 1($t4)			#for control '-' $t3 = '-'
		beq  $t7 , $t3 , handleMinus4add
		addi $a0 , $t6 , 0		#make the size fix(after '.')
		li $t6 , 10				#$t5 = 10
		add $s6 , $s1 , $s4		#$s7 = $s2 + $s5
		add $s7 , $s2 , $s5		#$s7 = $s2 + $s5
		mul $t6 , $t6 , $a0		#$t6 = $t6 * $a0 : a0:size
		beq	$t6,$s7,findResAdd 
		blt $t6,$s7,findResAdd
		j printResult
	
	findResAdd:
		addi $s6 , $s6 , 1		#elde
		sub $s7 , $s7 , $t6 
		
		lb $t3 , 2($t4)			#for control '*' $t3 = '*'
		beq  $t7 , $t3 , handleMinus4add2
		
		j printResult
	
	makeInteger:
		lb $t2, ($t0)  			#getting character at address
		addi $t2 , $t2 ,-48		#calculate digit decimal value
		mul $t2 , $t2 , $a0		#$t2 = $t2 * $a0
		add $a1 , $a1 , $t2		#$a1 = $a1 + $t2
		beq $a0 , 1 , end		#if($a0 == 1) then go to end label
		div $a0 , $a0 , 10		# else $a0 = $a0 / 10
		addi $t0, $t0, 1		# increment the address
		j makeInteger
	
	end:
		jal $ra
	
	findDigitValue4int:
		addi $t3 ,$zero, 10		#to calculate place(digit) value
		div $a0 , $t3			
		mflo $a0
		beq $a0 , $zero , goback
		mul $t1 , $t1 ,$t3
		j findDigitValue4int
	
	goback:
		addi $v0 , $t1,0
		j $ra
	
	findDigitValue:
		addi $t3 ,$zero, 10		#to calculate place(digit) value
		lb $t2, 0($t0)  		#getting character at address
		beq $t2 ,0,goto			#if(adress of i == null) go to goto label.
		beq $t2 , '\n', goto	#or if(address of i == newline) go to goto label.
		mul $t1, $t1, $t3		#else increment counter : like $t1*=$t3
		addi $t0, $t0, 1		# increment the address
		j findDigitValue
		
	takeInput:
		li $v0 , 4
		la $a0 , msg1
		syscall
		#take the input
		li $v0, 8				#To take string. $v0 = 8
		la $a0, userInput		#buffer
		li $a1, 20				
		syscall
		li $v0 , 4
		la $a0 , msg2
		syscall
		jal $ra					#go back
	
	takeOperand:
		beq $t1 , $a0, goto2	#if(i == $a0) go to goto2 label.
		addi $t1, $t1, 1		#else increment counter : i++
		addi $t0, $t0, 1		#else increment the adress
		j takeOperand
	
	goto2:						#for take operand
		lb $t2, 0($t0)			#getting character at address
		sb $t2 , ($s3)			#store the operand into operand
		jal $ra					#go back
	
	firstPart:
		lb $t2, 0($t0)  		#getting character at address
		beq $t1 , $a0, goto		#if(i == foundindex) go to goto label.
		addi $t1, $t1, 1		#else increment counter : i++
		sb $t2 , ($s1)			#store the character into the firstN buffer
		addi $t0, $t0, 1		# increment the address
		addi $s1, $s1, 1 		#same for here
		j firstPart
		
	secondPart:
		beq $t1 , $a0, goto3	#if(i == $a0) go to goto3 label.
		addi $t1, $t1, 1		#else increment counter : i++
		addi $t0, $t0, 1		#else increment the adress
		j secondPart
	
	goto3:						#for second part of the number
		lb $t2, 0($t0)  		#getting character at address
		beq $t2 ,0,goto			#if(adress of i == null) go to goto label.
		addi $t1, $t1, 1		#else increment counter : i++
		sb $t2 , ($s2)			#store the character into the secondN buffer
		addi $t0, $t0, 1		# increment the address
		addi $s2, $s2, 1 		#same for here
		j goto3
		
	findIndex:					#counts the bytes until the byte in $a0	
		lb $t2, 0($t0)			#load first byte from adress in t0
		beq $t2, $a0 , goto		#if $t2 == $a0 ($a0 is control byte)then go to goto label
		addi $t0, $t0, 1		#else increment the adress
		addi $t1, $t1, 1		#increment counter : i++
		j findIndex
		
	goto:
		addi $v0, $t1 , 0   	#$vo = $t1 to return the value of counted
		jal $ra					#go back