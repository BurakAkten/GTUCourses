#****************************************************#
#						     						 #		
#     CSE 321 - Introduction to Algorithm Design     #
#			   HW05  -  Question 1					 #
#				   Burak AKTEN						 #
#					141044045						 #
#                     2017							 #
#													 #
#****************************************************#	

##As a base condition, I controled the len of the Y. 
#then I fill The X.  Then calculate the cost.

# Worst case complexity is : f(n) = θ(n) + 2 * ( θ(n) + θ(n) ) = θ(n) 

import sys #to control version control
if int(sys.version[0]) < 3:
	print("You need python3/later version in order to run this python3 script!")
	sys.exit(1)


def find_maximum_cost(Y):

	if len(Y) <= 1:
		return sum(Y)

	size = len(Y)
	
	max_cost = 0
	X = [i for i in Y] # create X list by using Y list


	for i in range(2):
		cost = [0]*size
		X = [i for i in Y]
		for j in range(size):
			if i == 0 and j % 2 == 0:
				X[j] = 1
			elif i == 1 and j % 2 == 1:
				X[j] = 1
		for j in range(1 , size):
			cost[j] = cost[j - 1] + abs(X[j] - X[j - 1])

		if cost[-1] > max_cost:
			max_cost = cost[-1]

	return max_cost


		


if __name__ == "__main__":

	Y = [14,1,14,1,14]
	cost = find_maximum_cost(Y)
	print(cost)
	#Output: 52
	Y = [1,9,11,7,3]
	cost = find_maximum_cost(Y)
	print(cost)
	#Output: 28
	Y = [50,28,1,1,13,7]
	cost = find_maximum_cost(Y)
	print(cost)
	#Output: 78