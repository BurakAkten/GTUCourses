

/* 
 * File:   Bigram.h
 * Author: aktenburakk
 *
 * Created on 10 December 2016, 11:44
 */

#ifndef BIGRAM_H
#define BIGRAM_H
#include <string>
#include <exception>

using std :: ostream;

//this clas for throw exeption
class Error : public std :: exception{
  virtual const char* what() const throw(){
    return "Exception Thrown!!!";
  }
};

//Absract class
//=0 : this function has no imlementation in here
//=default : whenever they is necessary , defaulrs ones are used.
template <class T>
class Bigram {
public:
    Bigram() = default;
    virtual void readFile(std :: string fileName) throw(Error) = 0;
    template <class U>
    friend ostream& operator <<(ostream& out , const Bigram<U>& obj);
    virtual void print()const = 0;
    virtual int numGrams()const = 0;
    virtual int numOfGrams(T first , T second)const = 0;
    virtual std::pair<T ,T> maxGrams() = 0;//returns max bi-gram pair.
    Bigram<T>& operator =(const Bigram& orig) = default;
    Bigram(const Bigram<T>& orig) = default;
    virtual ~Bigram() = default;
private:

};
#endif /* BIGRAM_H */

