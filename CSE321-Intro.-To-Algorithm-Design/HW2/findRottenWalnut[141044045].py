def compareScales (leftScaleList, rightScaleList):
	result = sum(leftScaleList) - sum(rightScaleList)
	if result < 0:
		return 1
	elif result > 0:
		return -1 
	else:
		return 0

#walnuts is a list that include pozitive numbers
def findRottenWalnut(walnuts): 
	
	size = len(walnuts)

	index = recursive_helper(walnuts , size , 0)

	print("The index of rotten one is {}".format(index))

#walnuts is a list that include pozitive numbers
#size is the size of the list
#index is the index of rotten
def recursive_helper(walnuts , size , index):


	if(size == 1): #base condition
		return index

	middle = size//2	#middle index

	if(size % 2 == 0):	#for the list that its size is even
		
		#controlling if it is in the middle
		if(walnuts[middle] != walnuts[0] and walnuts[middle] != walnuts[-1]):
			return index + middle

		flag = compareScales(walnuts[0:middle] , walnuts[middle :])
		if(flag < 0):
			return recursive_helper(walnuts[middle :] , len(walnuts[middle :]) , index + middle)
		elif(flag > 0):
			return recursive_helper(walnuts[0:middle] , len(walnuts[0:middle]) , index)
		else:
			return -1
	else:			#for the list that its size is odd
		flag = compareScales(walnuts[0:middle] , walnuts[middle + 1 :])
		if(flag < 0):
			return recursive_helper(walnuts[middle + 1 :] , len(walnuts[middle + 1:]) , index + middle + 1)
		elif(flag > 0):
			return recursive_helper(walnuts[0:middle] , len(walnuts[0:middle]) , index)
		elif(walnuts[middle] != walnuts[0]):
			return index + middle;
		else:
			return -1

findRottenWalnut([1, 1 , 0.5,1, 1 , 1])

