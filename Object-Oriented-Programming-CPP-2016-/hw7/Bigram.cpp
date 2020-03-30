/* 
 * File:   Bigram.cpp
 * Author: aktenburakk
 * 
 * Created on 10 December 2016, 11:44
 */
#include "Bigram.h"

template <class T>
ostream& operator <<(ostream& out , const Bigram<T>& obj){
	//calling helper function for obj.
	obj.print();
	return out;
}



