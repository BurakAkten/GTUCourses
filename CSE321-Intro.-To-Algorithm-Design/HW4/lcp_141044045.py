#****************************************************#
#						     						 #		
#     CSE 321 - Introduction to Algorithm Design     #
#			   HW04  -  Question 2					 #
#				   Burak AKTEN						 #
#					141044045						 #
#                     2017							 #
#													 #
#****************************************************#	


#In this code , there are 2 different helper functions. 
#find_postfix : Takes a string array as parameter and working recursively to find the beginnig index of the
#				postfix then return this index. Also this function call the other function in
#				the base conditions
#find_postfix_index : Takes two string as parameter and working iteratively. Begins end of the strings 
#					 and make letter comparasion until two letters are diffrent then return the index.

#Worst Case of the algorithm: Assume that the size of the strings array is m and the longest string  size in
#							  this array is n. Then for the worst case lets assume that the postfix is the 
#							  longest string. So the worst case is 
#																	 θ(mlogn).




import sys #to control version control
if int(sys.version[0]) < 3:
	print("You need python3/later version in order to run this python3 script!")
	sys.exit(1)


def longest_common_postfix(inpStrings):


	if len(inpStrings) == 0 :  #if the input is empty then return empty string
		return ""
	elif len(inpStrings) == 1: #if the input array size is 1 then return this string
		return inpStrings[0]

	postfix_beginning_index = find_postfix(inpStrings) #call the recursive helper function

	size = len(inpStrings[0])

	return inpStrings[0][size - postfix_beginning_index : ]



#this function is working recursively to find the beginnig index of the
#postfix then return this index. 
def find_postfix(inpStrings):

	if(len(inpStrings) == 2): #first base condition controls 2 strings
		return find_postfix_index(inpStrings[0] , inpStrings[1])
	elif(len(inpStrings) == 3):#second base condition controls 3 strings
		index1 = find_postfix_index(inpStrings[0] , inpStrings[1])
		index2 = find_postfix_index(inpStrings[1] , inpStrings[2])
		index3 = find_postfix_index(inpStrings[0] , inpStrings[2])
		return min([index3 , index2 , index1]) #return minimum one
	else: #recursive part
		size = len(inpStrings) #find the string array size
		left =  find_postfix(inpStrings[:size // 2]) #find the index from left side of the array recursively.
		right = find_postfix(inpStrings[(size // 2):]) #find the index from right side of the array recursively.
		return min([left , right]) #return minimum one
			

#this function compae two string and find the index of postfix
def find_postfix_index(str1 , str2):
	size1 = len(str1)
	size2 = len(str2)
	i = size1 - 1 # to start from end of the strings
	j = size2 - 1
	index = 0
	while (i >= 0 and j >= 0): #until the diffrent letter in string
		if(str1[i] == str2[j]):
			index += 1
		else:
			break
		i -= 1
		j -= 1
	
	return index 

if __name__ == "__main__":

	inpStrings = ["absorptivity", "circularity","electricity", "importunity" , "humanity"]
	lcp = longest_common_postfix(inpStrings)
	print(lcp)

	inpStrings = ["bash", "trash", "backslash","flash"]
	lcp = longest_common_postfix(inpStrings)
	print(lcp)

