#****************************************************#
#													 #		
#     CSE 321 - Introduction to Algorithm Design     #
#			   HW03  -  Question 3					 #
#				   Burak AKTEN						 #
#					141044045						 #
#                     2017							 #
#													 #
#****************************************************#		

import sys #to control version control
if int(sys.version[0]) < 3:
	print("You need python3/later version in order to run this python3 script!")
	sys.exit(1)

def findMinimumCostToLabifyGTU(x , y , GTUMap):

	size = len(GTUMap)
	keys = GTUMap.keys()
	#if the cost of building a lab is less than repairing a road,
	#then the solution is build a lab at every department.
	if (x < y):
		return size * x

	identified = [False for i in range(size)] #To idetified the vertecis
	parentArr = [-1 for i in range(size)]     #to holds parents and childerens in graph

	#After this loop the parentArr is found.
	for key in keys:
		parentArr , identified = BFS(parentArr , identified , key , GTUMap)

	#in this part the cost is calculating.
	cost = 0
	for i in parentArr:
		cost += x if i == -1 else y

	return cost 

#this function makes BFS in given map(graph). In this Graph the vertecis are begin
#with the value of 1.
def BFS(parentArr ,identified, startVertex , GTUMap):
	
	queue = list() #to control the neigbours

	identified[startVertex - 1] = True # make identified the given vertex
	queue.insert(0 , startVertex - 1)

	while (len(queue) != 0):
		current = queue.pop() # 0,1,2,3...

		neighbors = GTUMap.get(current + 1)
		for neighbor in neighbors:
			if(identified[neighbor - 1] == False):
				#Mark it identified.
				identified[neighbor - 1] = True
				#Place it into the queue.
				queue.insert(0,neighbor - 1);
				#Insert the edge (current, neighbor) into the tree. */
				parentArr[neighbor - 1] = current;
	return parentArr , identified

if __name__ == "__main__":
	
	mapOfGTU = {
		1 : set([2,3]),
		2 : set([1,3]),
		3 : set([1,2])
	}
	
	minCost = findMinimumCostToLabifyGTU(2,1,mapOfGTU)
	print(minCost)