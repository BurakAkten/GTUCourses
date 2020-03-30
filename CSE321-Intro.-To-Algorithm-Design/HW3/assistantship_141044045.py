#****************************************************#
#						     						 #		
#     CSE 321 - Introduction to Algorithm Design     #
#			   HW03  -  Question 2					 #
#				Assignmet Problem					 #
#				   Burak AKTEN						 #
#					141044045						 #
#                     2017							 #
#													 #
#****************************************************#		

import sys #to control version control
if int(sys.version[0]) < 3:
	print("You need python3/later version in order to run this python3 script!")
	sys.exit(1)

#Take 2D list and return a list and integer
def findOptimalAssistantship(inputTable):

	sizeOfC = len(inputTable[0])
	sizeOfRA = len(inputTable)

	res = list() #holds the result array
	time = 9999999 # to control the time
	
	my_courses = [i for i in range(sizeOfC)] # courses : [0 1 2 ...]
	while(sizeOfC != sizeOfRA):
		my_courses.append(-1) #append -1 until make sizes equal 
		sizeOfC += 1

	#Create iterable object that includes possible results
	permutationOfRes = permutationOfResults(my_courses)

	#calculate costs for each of possible results
	for result in permutationOfRes:
		cost = 0
		for index , course in enumerate(result):
			if(result[index] == -1):
				cost += 6 # append 6 for RA that is unoccupied
			else:
				cost += inputTable[index][result[index]]
		#update result and time
		if time >= cost:
			time = cost
			res = result
	return res , time

#Take a 1D list and return generator object that includes all possible combination
#of the element in the list
def permutationOfResults(my_list):
	size=len(my_list) #size of the list

	#if size is less than 1 then yield my_list(base condition)
	if size <= 1:
		yield my_list	
	
	for i in range(size):

		first_to_create = my_list[i] #the first element of one of the possible results 

		other_part = my_list[ :i] + my_list[i + 1:]	#the list without "first_to_create"/my_list[i]
		#recursion part 
		for j in permutationOfResults(other_part):
			yield [first_to_create] + j


if __name__ == "__main__":
	
	inputTable = [
				  [1 ,  8 , 55],
				  [22 , 3 , 99],
				  [1 , 33 , 55]
				 ]

	asst, time = findOptimalAssistantship(inputTable)
	print(asst)
	print(time)