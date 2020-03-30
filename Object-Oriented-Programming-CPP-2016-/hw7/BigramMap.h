/* 
 * File:   BigramMap.h
 * Author: aktenburakk
 *
 * Created on 10 December 2016, 11:45
 */

#ifndef BIGRAMMAP_H
#define BIGRAMMAP_H
#include <vector>
#include <map>
#include <string>
#include <exception>

#include "Bigram.h"

template <class T>
class BigramMap : public Bigram<T> {
public:
    BigramMap() = default;//no-Parameter constructor
    BigramMap(int type);//this cnstructor take dataType as a int parameter
    BigramMap(const BigramMap<T>& orig) = default;//default copy-constructor
    //reads the file and throw exception when file is not exist
    //when data is irrelavant and file is empty
    void readFile(std :: string fileName) throw(Error);
    int numGrams()const;//returns total bi-grams.
    int numOfGrams(T first , T second)const;//returns number of grams for given
    std::pair<T ,T> maxGrams();//returns max bi-gram pair.
    ~BigramMap()=default;//desructor
private:
	void print()const;//helper function for stream insertion
    void fillMap();//fill the map with pairs and their occurrences.    
    void makePair(std::vector<T>& vec);//it makes all data pair
    int numberOfMaxGrams;//it's hold the number of maximum grams.
    // it's keep the each data as a pair
    std::vector<std::pair<T,T> > pairDatas; 
    //it's keep the pair datas with their occurrences.
    std::map<std::pair<T , T> ,int > numberOfDatas;
    int dataType;//of the input in the file
};

#endif /* BIGRAMMAP_H */

