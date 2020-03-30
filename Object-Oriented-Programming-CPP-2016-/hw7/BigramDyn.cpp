/* 
 * File:   BigramDyn.cpp
 * Author: aktenburakk
 * 
 * Created on 10 December 2016, 11:45
 */

#include "BigramDyn.h"
#include "Bigram.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

template <class T>
BigramDyn<T>::BigramDyn() : Bigram<T>() , size(0) , capacity(10) ,dataType(2){
    //no parameter constructor sets size to 0 and capacity to 10.
    //then take place from memory for dynData;
    //and sets the dataType to 2 for string
    dynData = new pair<int ,pair<T ,T> >[capacity];
}

template <class T>
BigramDyn<T>::BigramDyn(int type) :
					Bigram<T>(),size(0),capacity(10),dataType(type){
 	//This constructor does same thing like no parameter const.
	//and sets the variable dataType.
    dynData = new pair<int ,pair<T ,T> >[capacity];
}

template <class T>
BigramDyn<T>::BigramDyn(const BigramDyn<T>& other) 
           :size(other.size),capacity(other.capacity),dataType(other.dataType){
    
    //copy constructor
    dynData = new pair<int ,pair<T ,T> >[capacity];
    for(int i = 0 ; i < size ; i++)
        dynData[i] = other.dynData[i];   
}

template <class T>
BigramDyn<T>& BigramDyn<T>:: operator =(const BigramDyn<T>& other){
    
    //overloading assignment operator.
    if(size != other.size && capacity != other.capacity){
        delete [] dynData;
		capacity = other.capacity;
		size = other.size;
		dynData = new pair<int ,pair<T ,T> >[capacity];
    }
    for(int i = 0; i < size ; ++i)
		dynData[i] = other.dynData[i];
			
    return *this;
}

template <class T>
void BigramDyn<T>::readFile(string fileName) throw(Error){

    ifstream inp;
    
    vector<T> datas; //keep all datas one by one.

    inp.open(fileName);//file is opening
    if(inp.fail()){//if file is not exist then throwing Error object
    	cerr<<"No such a file!!"<<endl;
        throw Error();
    }
    
    T data;

    //reads the file until end of file
    while (!inp.eof() && inp >> data)
        datas.push_back(data);
    
    if(!inp.eof()){
        cerr<<"Bad Data!"<<endl;
        inp.close();
        throw Error();
    }
    inp.close();

    if(datas.size() == 0){
        cerr<<"Empty File!!!"<<endl;
        throw Error();
    }

    //adding elements to the dynamic data.
    for(int i = 0 ; i < datas.size() - 1 ; ++i)
    	addElement(datas[i] , datas[i + 1]);

    //this function sets some private variables.
    // more information is in the function implemantation.
    setter();
}

template <class T>
void BigramDyn<T>:: addElement(T element1 , T element2){

	//this function firstly control the capacity if capacity isn't enough
	//then take more place from memory.
    if(size >= capacity)
        reload();
    //then here adds the element.
    (dynData[size]).second.first = element1;
    (dynData[size]).second.second = element2;
    (dynData[size]).first = 0;

    //update size.
    size++;
}
template <class T>
void BigramDyn<T> :: reload(){

	//when capcity of the dynData isn't enough , this function is works.
    capacity += 50;
    pair<int ,pair<T, T> >* newArray = new pair<int ,pair<T, T> >[capacity];
    
    for (int i = 0; i < size; i++) 
        newArray[i] = dynData[i];

    delete [] dynData;
    
    dynData = newArray;
}

template <class T>
void BigramDyn<T>::setter(){

	pair<T,T> temp=dynData[0].second;//holds the pair that has most occurence.
	int max = 0 , count = 1;

	for (int i = 0; i < size; ++i){

		count = numOfGrams(dynData[i].second.first , dynData[i].second.second);
		//sets the ith first value of dynData with its occurence.
		(dynData[i]).first = count;

		if (count > max){
			max = count;
			temp = dynData[i].second;		
		}
		count = 1;
	}
	maxPair = temp;
	numberOfMaxGrams = max;//the number of maximum bigrams in dynData.

	sort();//then sorts the dynData according to pair's occurences.
}

template <class T>
void BigramDyn<T>:: sort(){
	

	//this function sorts the dynData according to
	// pair's occurences from greater to smaller.
    for (int i = 0 ; i < size; ++i) {
        for (int j = 0; j < size ; ++j) {
            if(dynData[j].first < dynData[i].first ){
                pair<int ,pair<T ,T> > temp = dynData[j];
                dynData[j] = dynData[i];
                dynData[i] = temp;
            }
        }
    }
}

template <class T>
void BigramDyn<T>:: print()const{

	vector<pair<T,T> > vec;
	bool flag;

	for (int i = 0; i < size ; ++i)
	{
		flag = false;
		//this loop is for not printing out same value on the screen
		for(pair<T,T> x : vec)
			if(x == dynData[i].second)
				flag = true;				
		//then printing out on the screen the values
		if(flag == false){
			cout <<"("<<dynData[i].second.first<<"-";
			cout <<dynData[i].second.second<<") =>"<<dynData[i].first;
			if(i != size - 1)
				cout << endl;
			vec.push_back(dynData[i].second);
		}
	}
}

template <class T>
pair<T ,T> BigramDyn<T>:: maxGrams(){ return maxPair; }

template <class T>
int BigramDyn<T>:: numGrams()const{ return size;}

template <class T>
int BigramDyn<T>:: numOfGrams(T first , T second)const {
    
    int total = 0; //holds occurences
    
    for(int i = 0 ; i < size ; ++i)
        if(dynData[i].second.first==first && dynData[i].second.second==second)
            total++;
    
    return total; 
}

template <class T>
BigramDyn<T>::~BigramDyn() { //free the memory.
    delete [] dynData;
}

