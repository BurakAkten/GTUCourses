#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <string>


#define STOPPING_CRI1 "DISTANCE_TO_ROOT"
#define STOPPING_CRI2 "ABSOLUTE_ERROR"
#define STOPPING_CRI3 "RELATIVE_ERROR"

/*Defining pi if not defined in cmath library*/
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

using namespace std;

/*defining any function.*/
double function(double x);
/*Return false when failure.*/
bool bisection(double a , double b , string stoppingCriterion ,double epsilon);

int main(int argc, char* argv[]) {
    
    if(argc !=  5){
        cerr<<"Usage : "+(string)argv[0]+"a b stoppingCrietion epsilon!"<<endl;
    }
   
    double a1 = atof(argv[1]) , b1 = atof(argv[2]) , epsilon = atof(argv[4]);
    string criterion = argv[3];
    if(!bisection(a1 , b1 ,criterion,epsilon)){
        cout<<"Error on bisection!\n";
        return -1;
    }
    return 0;
}

double function(double x){
		
    //Hw questions in 2.1 exercise.
    
    #ifdef A
   	return (3*x - exp(x));//a
   	#endif
   	#ifdef B 
    return ( 2*x + 3*cos(x*(M_PI/180.0)) - exp(x));//b
    #endif
    #ifdef C 
    return ( pow(x , 2) - (4*x) + 4 -(log(x)));//c
    #endif 
    #ifdef D
    return ( x + 1 - 2*sin((M_PI * x)*(M_PI/180.0)));//d
    #endif


    return pow(x , 3) + 4*pow(x , 2) - 10 ; // example function for testing
}

bool bisection(double a , double b , string stoppingCriterion , double epsilon){
    
    bool found = false;
    double fA = function(a) , fB = function(b);

    if(fA*fB > 0){
    	cout << "You may not find any root , because f(a)*f(b) > 0 !"<<endl;
    }

    double x1 = a , x2 = b;
    int i = 1;/*counter*/

    double p1;/*holds pn values.*/
    double  root;/*Root*/
    double funcReturn;/*the return value of the function that imlemented above.*/
    double preP = x1;//previous p value.
    double relativeError , absoluteError , distanceToRoot;/*stopping criteries*/
    
    transform(stoppingCriterion.begin(), stoppingCriterion.end(), stoppingCriterion.begin(),(int (*)(int))toupper);


    cout.precision(10);
    cout << "Iter\t|\tThe Absolute Error\t|\tThe Relative Error"<<endl; 
    
    /*This part is the real part of bisection algorithm*/
    for(;found==false && i <= 100 ; i++){
        double fA = function(x1) , fB = function(x2);
        p1 = (x1 + x2) / 2;
        funcReturn = function(p1);
        
        /*calculation of the stopping criteries values*/
        relativeError = fabs(p1 -preP) / p1 ;
        absoluteError = fabs(p1 -preP);      
        distanceToRoot = fabs(funcReturn);
        
        preP = p1;

        cout<<setw(3)<<fixed << ""<<i<<"\t|\t"<<absoluteError;
        cout<<"\t\t|\t"<<relativeError<<endl;
        
        /*controlling the stopping criteries and the formulas results*/
        if(stoppingCriterion == STOPPING_CRI1 &&  distanceToRoot< epsilon ){
            root = p1;
            found = true;
        }
        else if(stoppingCriterion == STOPPING_CRI2 &&  absoluteError< epsilon){
            root = p1;
            found = true;
        }
        else if(stoppingCriterion == STOPPING_CRI3 &&  relativeError< epsilon){
            root = p1;
            found = true;
        }
        else{
        	/*swapping the values of x1 and x2 if one of these condition is true*/
            if(funcReturn * fA > 0)
                x1 = p1;
            else if(funcReturn * fB > 0)
                x2 = p1;           
        }       
    }
    /*İf the number of the iterations is greater than 100. The program quit.*/
    if(i  > 100 && found == false){
    	cout << "The number of iterations is over 100."<<endl;
    	return found;
    }
    cout << "Approximate root  : "<<root<<endl;
    cout <<"The number of iterations that have been executed : "<<--i<<endl;  
    cout<<"The theoretically required number of iterations : ";
    cout<<int(ceil(((-1)*log10(epsilon/(b-a)))/log10(2)))<<endl;
    
    return found;
}