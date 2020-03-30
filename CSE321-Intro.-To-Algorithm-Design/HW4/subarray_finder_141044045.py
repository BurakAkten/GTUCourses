#****************************************************#
#						     						 #		
#     CSE 321 - Introduction to Algorithm Design     #
#			   HW04  -  Question 1					 #
#				   Burak AKTEN						 #
#					141044045						 #
#                     2017							 #
#													 #
#****************************************************#	


#In this algorithm I used 1 helper function for min_subarray_finder.
#find_min_subArr : Takes 3 argument that are array , first index and last index. this function is
#				  working as recursively to find the minimum subarray. As a base condition I controlled the first
#				  and last values. If they are is equal then I return arr[first] and [arr[first]]. Then
# 				  recursive parts are working for left and right side of the array. After recursive part , I 
# 				  found a different subarray that includes element between first and last index.
#				  When I have 3 different sub array , I choose the mnimum one.
#
#Worst Case :  For the worst case, 2 recursion part is working and additinaly 2 while loop is working.
# 				Lets assume that size of the input array is n. Then the  ->> T(n) = 2T(n/2) + Θ(n)
# 				After apply the Master theorem on this equation then the worst case is ->> W(n) = Θ(n) 
#																		

import sys #to control version control
if int(sys.version[0]) < 3:
	print("You need python3/later version in order to run this python3 script!")
	sys.exit(1)



def min_subarray_finder(inpArr):

	size = len(inpArr)

	if(size == 0): #if the size of the inpArr is zero then return empty list
		return []

	sum1 = sum(inpArr) #calculate the sum of the inpArr

	sum_ , sub_arr = find_min_subArr(inpArr , 0 , size - 1) #Then call the helper recursive function

	#if sum of the inpArr is less than the summation of the found subarray then insert the first 
	#element in the inpArr into the 0. index in found subarray
	if sum1 < sum_:
		sub_arr.insert(0 , inpArr[0])

	return sub_arr

#This function is working recursively to find the minimum subarray
def find_min_subArr( arr , first , last):

	if first == last:		#base condition 
		return arr[first] , [arr[first]]


	middle = (first + last) // 2

	sum_of_left  ,left_sub = find_min_subArr(arr , first , middle)		#firstly search the left side
	sum_of_right ,right_sub = find_min_subArr(arr , middle + 1 , last)	#then searc the right side recursively

	max_left = 9999999	#max values
	max_right = 9999999

	##############################     ###########################   ##################################
	#In this part found two array then I make them one array. This array represent the array that holds 
	#elements from left side and right side together
	i = first
	sum_ = 0
	sub_arr1 = list()
	while (i < middle):
		sum_ += arr[i]
		if(sum_ < max_left):
			max_left = sum_
			sub_arr1 = arr[first+1:i + 1] 

		i += 1

	i = middle
	sum_ = 0 
	sub_arr2 = list()
	while (i <= last):
		sum_ += arr[i]
		if(sum_ < max_right):
			max_right = sum_
			sub_arr2 = arr[middle:i + 1]
		i += 1

	middle_part = sub_arr1 + sub_arr2

	##############################     ###########################   ##################################

	#in this part of the code , I control these 3 array to find minimum sub array then return it.
	result_arr = left_sub if sum_of_left < sum_of_right else right_sub

	result_arr = result_arr if sum(result_arr) < sum(middle_part) else middle_part

	return sum(result_arr) , result_arr


if __name__ == "__main__":
	inpArr = [1, -4, -7, 5, -13, 9, 23, -1]
	#inpArr = [-1 , -2 , 3 , -4]
	
	#inpArr = [-2,-3,-4,-5]
	#inpArr = [-1,-2,-5 , 9 , -10]

	msa = min_subarray_finder(inpArr)
	print(msa)
	#Output: [-4, -7, 5, -13]
	print(sum(msa))
	#Output: -19

