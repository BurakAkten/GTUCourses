
def TowersOfHanoi(n):

	times_for_all_disk = [0 for i in range(n)] 	#This hold the Elapsed time for n disks
	Src = "Src"
	Dest = "Dst"
	Aux = "Aux"
	my_dict = {Src : 1 , Aux : 2 , Dest : 3}	#This dictionary for help to calculate the time for all disks

	print("Input size is {}".format(n))

	#calling the helper function for TowersOfHanoi
	times_for_all_disk = TowersOfHanoi_helper(Src , Aux , Dest , n , times_for_all_disk , my_dict)

	#printing  out calculated times
	for i , time in enumerate(times_for_all_disk):
		print ("Elapsed time for disk {} : {} ".format(i + 1 , time))


#This function return the times array that holds the elapsed times
def TowersOfHanoi_helper(Src , Aux , Dest , n , times ,time_helper):

	if n == 1:
		print ("Disk {} : {} to {}.".format(n , Src , Dest))
		
		#For each iteration the time is updated
		times[n - 1] = times[n - 1] + abs(time_helper[Dest] - time_helper[Src]) * n

		return times 	#return the times list that holds the elapsed times
	else:

		times = TowersOfHanoi_helper(Src , Dest , Aux , n - 1 , times ,time_helper)

		print ("Disk {} : {} to {}.".format(n , Src , Dest))
		#For each iteration the time is updated
		times[n - 1] = times[n - 1] + abs(time_helper[Dest] - time_helper[Src]) * n	
		
		times = TowersOfHanoi_helper(Aux , Src , Dest , n - 1 ,times ,time_helper)

		return times 	#return the times list that holds the elapsed times

TowersOfHanoi(5) #write the number of the disks as parameter. Here the function is calling with 5.