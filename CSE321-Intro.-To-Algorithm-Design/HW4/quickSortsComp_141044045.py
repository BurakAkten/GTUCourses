#****************************************************#
#						     						 #		
#     CSE 321 - Introduction to Algorithm Design     #
#			   HW04  -  Question 5					 #
#				   Burak AKTEN						 #
#					141044045						 #
#                     2017							 #
#													 #
#****************************************************#	


#What are Lumoto and Hoare partitions advantages and disadvantages?
#Answer :Hoare partition is scan the subarray from both ends (low to pivot and 
#		  high to pivot). But the Lumoto partition scans the sub array from beginnig to pivot.
#		Because of the diffrence of the scans the array makes easier to imlement the lumoto partition
# 		but at the same time this situation makes lumoto partition slower(not for large size arrays)



import sys #to control version control
if int(sys.version[0]) < 3:
	print("You need python3/later version in order to run this python3 script!")
	sys.exit(1)


#swap function take 2 indeces and an array then swaps these indeces and return the swapped array.
def swap(array , i1 ,i2):
	temp = array[i1]
	array[i1] = array[i2]
	array[i2] = temp
	return array
#from psuedocode in class
def LumotoPartition(array , l , r):  

	pivot = array[l]
	s = l 

	i = l + 1
	while i < len(array):
		if array[i] < pivot:
			s = s + 1
			array = swap(array , s , i)
		i += 1
	array = swap(array , l , s)

	return s , array

def HoarePartition(array , l , r):   
	pivot = array[l]
	i = l 
	j = r 

	while i < j:
		while(array[i] < pivot):
			i += 1
		while(array[j] > pivot):
			j -= 1
		if i < j:
			array = swap(array , i , j)

	return j , array

#this function takes an array , integer low and high values anf boolean LorH
#LorH is to decide which partition is ganno be used.
def quick_sort(array , low, high, LorH):
	
	if low < high :
		pivot , array = LumotoPartition(array , low , high) if LorH else HoarePartition(array , low , high)
		array = quick_sort(array , low , pivot - 1  , LorH)
		array = quick_sort(array , pivot + 1 , high , LorH)
	return array


def quickSortLomuto(array):
	return quick_sort(array , 0 , len(array) - 1 , True) #true for lumoto partition

def quickSortHoare(array):
	return quick_sort(array , 0 , len(array) - 1 , False) #false for hoare partition

if __name__ == "__main__":

	arr = [15,4,68,24,-75,16,-1]
	qsh = quickSortHoare(arr)
	print(qsh)
	#Output: [4, 15, 16, 24, 42, 68, 75]
	qsl = quickSortLomuto(arr)
	print(qsl)
	#Output: [4, 15, 16, 24, 42, 68, 75]





