#****************************************************#
#						     						 #		
#     CSE 321 - Introduction to Algorithm Design     #
#			   HW05  -  Question 3					 #
#				   Burak AKTEN						 #
#					141044045						 #
#                     2017							 #
#													 #
#****************************************************#	


#In the base conditions:
##		---> control the n is bigger than 2 and the modula of the n to create the number.
##
##In the other part , I used 2 list one for 3s one for 5s.
##In every iteration, I firstly put three 5s in the first list and decreased the n.
## I controled that n modula 5 is equal to 0 or not. If yes the loop is finished then 
## I put n(current n value) times 3 in the other list.
## Lastly , I made the lists integer value and returned.
## After the loop finish , if the flag is still true , it's not possible to create such that number 
## so I returned -1.  


##In my  greedy algorithm , I never goes back and reverse my decision. I always make the choices that 
## seems to be the best solution


import sys #to control version control
if int(sys.version[0]) < 3:
	print("You need python3/later version in order to run this python3 script!")
	sys.exit(1)

def decentNumber(n):

	if n <= 2: #if n is less than or equal to 2, it's not possible to create a decent number. So return -1.
		return -1
	#if the result that come from this expression n mod 3(5) is equal to 0. The result contains only 5(3).
	elif n % 3 == 0: 
		return ''.join(['5' for i in range(n)])
	elif n % 5 == 0:
		return ''.join(['3' for i in range(n)])


	list1 = list() #List for the 5s
	list2 = list() #list for the 3s
	flag = True
	while flag and n >= 2:
		#in every iteration I put 5s in the first list
		for i in range(3):  
			list1.append('5')
		n -= 3 
		if n % 5 == 0: #control the modula
			flag = False
	if flag == False: # then puts the 5s in the second list
		list2 = ['3']*n
	else : # if not possible return -1
		return -1
	return ''.join(list1 + list2) 

		


if __name__ == "__main__":

	dn = decentNumber(1)
	print(dn)
	#Output: -1
	dn = decentNumber(3)
	print(dn)
	#Output: 555
	dn = decentNumber(5)
	print(dn)
	#Output: 33333
	dn = decentNumber(64)
	print(dn)
	#Output: 55555533333
