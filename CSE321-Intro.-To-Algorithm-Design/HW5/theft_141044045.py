#****************************************************#
#						     						 #		
#     CSE 321 - Introduction to Algorithm Design     #
#			   HW05  -  Question 2					 #
#				   Burak AKTEN						 #
#					141044045						 #
#                     2017							 #
#													 #
#****************************************************#	


#First Step :  2D array is created(same size with input array).
#Second Step:  The theif can move only right , right-up and right-dow and the beginnnig place 
#			  can be any cell on first col. Because of that, the first col of other 2D array
#		      must be initialized by using input array first col. So it's done.
#Third Step :  The other left cells(not initialized) in second array are filled.
# 		      To fill these cells , considered the possible cell(mith max money) that comes from and
# 			  the current cell in input array and the possible cell are added then the current cell in 
# 			  second array is found until the last cell calculated in second array.
#Forth Step:   The maximum value in last col from second array is returned.


#Complexity of this algorithm : Assume that the input array has n rows and m cols.
#For 1st step  =>  θ(m*n)
#For 2nd step  =>  θ(m)
#For 3rd step  =>  θ((m-1)*n)
#For 4th step  =>  θ(m)
# So the complexity is =>   f(n) = θ(m*n) + 2 * θ(m) + θ((m-1)*n) = θ(m*n)


import sys #to control version control
if int(sys.version[0]) < 3:
	print("You need python3/later version in order to run this python3 script!")
	sys.exit(1)

def theft(maze):

	rows = len(maze)
	cols = len(maze[0])  # for create an array.

	#create cost array for every visited cell
	max_money = [[0 for j in range(cols)] for i in range(rows)]   	

	#The theif can move only right , right-up and right-dow and the beginnnig place 
	#can be any cell on first col. Because of that, the first col must be initialized 
	#by using input array first col.
	for i in range(cols):
		max_money[i][0] = maze[i][0]

	#In this part, each cell in the max_money array is calculated by calculated possible
	#path. Every cell in first and last row have juts two different path and the others have three
	#different path. This difference is considered while the cells costs are calculated. 
	for col in range(1 , cols):
		for row in range(rows):
			if row == 0:
				max_money[row][col] = max(max_money[row][col - 1] , max_money[row + 1][col -1]) + maze[row][col]
			elif row == rows - 1:
				max_money[row][col] = max(max_money[row][col - 1] , max_money[row - 1][col -1]) + maze[row][col]
			else:
 				max_money[row][col] = max(max_money[row][col-1] , max_money[row-1][col-1] , max_money[row+1][col-1]) + maze[row][col]



	return max([max_money[i][-1] for i in range(rows)]) # return result.


if __name__ == "__main__":

	amountOfMoneyInLand= [[1,3,1,5], [2,2,4,1], [5,0,2,3], [0,6,1,2]]
	res = theft(amountOfMoneyInLand)
	print(res)
	#Output: 16
	amountOfMoneyInLand= [[10,33,13,15], [22,21,4,1], [5,0,2,3], [0,6,14,2]]
	res = theft(amountOfMoneyInLand)
	print(res)
	#Output: 83
