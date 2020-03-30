#****************************************************#
#						     						 #		
#     CSE 321 - Introduction to Algorithm Design     #
#			   HW04  -  Question 3					 #
#				   Burak AKTEN						 #
#					141044045						 #
#                     2017							 #
#													 #
#****************************************************#	

#In this code, there is 1 helper function.
#find_the_book : Takes 2 array and the value of the k.This function is working recursively. Firstly, control tha the value of 
#				 k is less than summation of the size of arrays and continue. Then if one of the array is empty and k is less 
#				 than the size of the other array then return the kth element of the other array (base conditions.).
#				 In the recursive part the values of the middle indexes of each array are controlled. According to the control
# 				 ignore half of the one of these array in each recursive call. Then make the recursive call.
#				 If right side f the arrays is ignored k will be same in the other call but if the ignored part is left side
# 				 then k will be changed. 	 

import sys #to control version control
if int(sys.version[0]) < 3:
	print("You need python3/later version in order to run this python3 script!")
	sys.exit(1)


def find_the_book(first,sec,k):

	size1 = len(first) 
	size2 = len(sec)
	if k < size1 + size2:  								#if k is bigger than give error message 
		if size1 == 0 and k < size2:					#One of the base condition of the recursion function
			return sec[k] 					
		elif size2 == 0 and k < size1:					#other base condition
			return first[k] 					

		middle1 = size1 // 2							#middle of the first array
		middle2 = size2 // 2							#middle of the second array

		#if this summation (middle1 + middle2) is bigger than or equal to k then control the values in the middle indexes
		# of arrays and take the half of one array each time. k will be updated and the recursive parts will be worked.
		if middle2 + middle1 >= k:						
			return find_the_book(first[ : middle1],sec,k) if first[middle1]>sec[middle2] else find_the_book(first,sec[ : middle2],k) # k is same
		else:
			return find_the_book(first,sec[middle2 + 1:],k-middle2-1 ) if first[middle1]>sec[middle2] else find_the_book(first[middle1+1:],sec,k- middle1-1) # k is changed
	else:
		return "Index(k) is out of range (size of first list + sizeof second list)."
def find_kth_book_1(list1 , list2,k):
	if k > 0:
		return find_the_book(list1 , list2 , k - 1) #becasue books begins from 1.
	else:
		return "k value is invalid!"

if __name__ == "__main__":

	m = ["algotihm", "programminglanguages", "systemsprogramming"]
	n = ["computergraphics", "cprogramming","oop"]
	book = find_kth_book_1(m,n,4)
	print(book)
	#Output: programminglanguages
	book = find_kth_book_1(m,n,6)
	print(book)

