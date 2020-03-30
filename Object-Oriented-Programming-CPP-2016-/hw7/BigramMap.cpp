/* 
 * File:   BigramMap.cpp
 * Author: aktenburakk
 * 
 * Created on 10 December 2016, 11:45
 */

#include "BigramMap.h"
#include "Bigram.h"
#include <string>
#include <iostream>
#include <map>
#include <fstream>
using namespace std;

template <class T>
BigramMap<T>::BigramMap(int type) : Bigram<T>() , dataType(type){}

template <class T>
void BigramMap<T>::readFile(string fileName) throw(Error){

    ifstream inp;
    
    vector<T> datas;//keep all datas one by one.
    
    inp.open(fileName);//file is opening
    if(inp.fail()){//if file is not exist then throwing Error object
    	cerr << "No such a file!!"<<endl;
        throw Error();
    }

    T inpData;
    //reads the file until end of file
    while (!inp.eof()  && inp >> inpData)
        datas.push_back(inpData);
    
    if(!inp.eof()){
        cerr<<"Bad Data!"<<endl;
        inp.close();
        throw Error();
    }
    inp.close();

    //if file is empty then throw Error exception.
    if(datas.size() == 0){
        cerr<<"Empty File!!!"<<endl;
        throw Error();
    }
    
    //the data that read from file is being made pairs by this function
    makePair(datas);
    //fill the map is numberOfDatas with these pair and their occurences.
    fillMap();
}

template <class T>
void BigramMap<T>:: print()const{
    //reverse iterator for beginning form the end of the map to printo out.
    typename map<pair<T , T> , int >::const_reverse_iterator p ;
    typename map<pair<T , T> , int >::const_reverse_iterator temp ;
    //first loop begins with max. occurences and goes on until zero.
    //to print out the all occurences of all pairs.
    for(int i = numberOfMaxGrams; i > 0 ; --i)
        for(p = numberOfDatas.rbegin();p != numberOfDatas.rend() ; p++){
            if(p->second == i){         
                cout<<"("<<p->first.first<<"-"<< p->first.second<<") =>";
                cout << p->second<<endl; 
            }
        }
}

template<class T>
void BigramMap<T>:: fillMap(){

	//fill the map with pairs and their occurrences.
    for(int i = 0; i < pairDatas.size() ; ++i){
        pair<T , T> temp = pairDatas[i];
        //calculates occurence of that pair.
        int count = numOfGrams(temp.first , temp.second);

        numberOfDatas[pairDatas[i]] = count;
    }

}

template <class T>
void BigramMap<T>::makePair(std::vector<T>& vec){
    //it makes all data pair into pairDatas.
    for(int i = 0; i < vec.size() - 1 ; ++i)
        pairDatas.push_back(make_pair(vec[i] , vec[i + 1]));
}

template <class T>
int BigramMap<T>:: numGrams()const {return pairDatas.size();}

template <class T>
int BigramMap<T>::numOfGrams(T first , T second)const{

	//holds occurences
    int total = 0;
    //make the paramaters pair.
    pair<T ,T> temp = make_pair(first , second);
    
    for(int i = 0 ; i < numGrams() ; ++i){
        if(pairDatas[i] == temp)
            total++;
    }
    return total;
}

template <class T>
pair<T ,T> BigramMap<T>:: maxGrams(){

    int max = 0;
    
    typename map<pair<T , T>, int >::const_iterator p ;

    //This first loop find the maximum occurence in fale as a pair.
    for(p = numberOfDatas.begin();p != numberOfDatas.end() ; p++)
        if(p->second > max)
            max = p->second;

    pair<T ,T> temp;
    bool found = false;
    //This part firstly find out which pairs occurences equal to max and if 
    //this pair is occurence in the file as first one then it is returned.
    for (int i = 0; i < pairDatas.size() && !found; ++i)
    	for(p = numberOfDatas.begin(); p != numberOfDatas.end() && !found ; p++)
    		if (p->first == pairDatas[i] && p->second == max){
    			temp = make_pair(p->first.first , p->first.second);
    			found = true;
    		}
    
    numberOfMaxGrams = max;//initialize the value of numberOfMaxGrams with max.

    return temp;
}



