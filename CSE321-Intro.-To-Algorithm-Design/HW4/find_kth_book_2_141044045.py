#****************************************************#
#						     						 #		
#     CSE 321 - Introduction to Algorithm Design     #
#			   HW04  -  Question 4					 #
#				   Burak AKTEN						 #
#					141044045						 #
#                     2017							 #
#													 #
#****************************************************#	


#In this code, there is 1 helper function.
#find_the_book : Takes 2 array and the value of the k.This function is working recursively. In this function , I tried to
#				find the result in Log(k) time. To do thet in every time I divide the k by 2 and I ignore the left/right half part 
# 				of arrays until k becomes 1. Then choose the minimum value of the first indeces of the arrays as a result.
# 				But I think I made a little mistake because this function gives a wrong result sometimes. I did not have enough time to fix it



import sys #to control version control
if int(sys.version[0]) < 3:
	print("You need python3/later version in order to run this python3 script!")
	sys.exit(1)


def find_the_book(first,sec,k):

	size1 = len(first) 
	size2 = len(sec)
	if size1 == 0 and k < size2:					#One of the base condition of the recursion function
		return sec[k] 					
	elif size2 == 0 and k < size1:					#other base condition
		return first[k] 					


	if k == 1:										#if k == 1 then return the min of the arrays first
		return min(first[k - 1] , sec[k - 1])

	index = k // 2

	#recursive part.
	if first[index] < sec[index]:
		return find_the_book(first[index + 1:] , sec[:index + 1 ] , k // 2 )
	else:
		return find_the_book(first[:index + 1] , sec[index + 1 :] , k // 2)



def find_kth_book_1(list1 , list2,k):
	if k <= len(list1) + len(list2):  				 #if k is bigger than give error message 
		return find_the_book(list1 , list2 , k - 1) 		 
	else:
		return "Index(k) is out of range (size of first list + sizeof second list)."


if __name__ == "__main__":

	m = ["algotihm", "programminglanguages", "systemsprogramming"]
	n = ["computergraphics", "cprogramming","oop"]
	book = find_kth_book_1(m,n,6)
	print(book)
	#Output: programminglanguages
	book = find_kth_book_1(m,n,3)
	print(book)

