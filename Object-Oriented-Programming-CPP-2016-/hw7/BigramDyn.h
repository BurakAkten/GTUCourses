

/* 
 * File:   BigramDyn.h
 * Author: aktenburakk
 *
 * Created on 10 December 2016, 11:45
 */

#ifndef BIGRAMDYN_H
#define BIGRAMDYN_H
#include "Bigram.h"
#include <fstream>
#include <string>
#include <exception>

template <class T>
class BigramDyn : public Bigram<T> {
public:
    BigramDyn();//no-Parameter constructor
    BigramDyn(int type);//this cnstructor take dataType as a int parameter
    BigramDyn(const BigramDyn<T>& orig);//copy constructor
    //overload for assignment operator
    BigramDyn<T>& operator =(const BigramDyn<T>& other);
    //reads the file and throw exception when file is not exist
    //when data is irrelavant and file is empty
    void readFile(std :: string fileName) throw(Error);
    int numGrams()const;//returns total bi-grams.
    std::pair<T ,T> maxGrams();//returns max bi-gram pair.
    int numOfGrams(T first , T second)const;//returns number of grams for given
    ~BigramDyn();//desructor
private:
	/*************************Functions*************************************/
	void print()const;//helper function for stream insertion
    void addElement(T element1 , T element2);//add element to dynData
    void reload();// reload the capacity of the dynData
    void setter();//sets some private variable.
    void sort();//sorts the dynData according to pair's occurences(int param)
    /************************Variables***************************************/
    //dynData holds the pairs and their occurences.
    std::pair<int ,std::pair<T ,T> >* dynData;
    //maxPair holds the pair that has the most ocuurences.
    std::pair<T,T> maxPair;
    //holds the most occurences for one pair.
    int numberOfMaxGrams;
    int capacity;//of dynData
    int size;//of dynData
    int dataType;//of the input in the file
};

#endif /* BIGRAMDYN_H */

