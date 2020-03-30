import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.util.Vector;
import java.util.InputMismatchException;
import java.lang.Exception;
/**
 *
 * @author aktenburakk
 */
@SuppressWarnings("unchecked")
public class BigramDyn<T> implements Bigram<T> {

    private int dataType;//thpe of the data in file.
    private int size = 0;//the size of the array.
    private Scanner input ;
    private int max = 0;//holds maximum occurences
    private myPair<Integer ,myPair<T ,T> >[] dynMap;//holds pairs ant their occurences.

    private void addNewElement(T element1 , T element2){
    	//this function make the givin two parameter pair then add the pair to array.

        //temporary pair to be added to array
        myPair<T ,T> temp = new myPair<T , T>(element1 , element2);
        if(size >= dynMap.length)
            reload();
        
        dynMap[size].second = temp;
        dynMap[size].first=new Integer(0);
        
        size++;//update the size
    }
    
    private void reload(){
    	//this function make the capacity of the array greater .
    	//+50
        myPair<Integer ,myPair<T ,T> >[] temp = new myPair[dynMap.length + 50];
        
        for (int i = 0; i < size; i++) 
            temp[i] = dynMap[i];
        
        dynMap = temp;
    }
    private void sort(){//this function sort the array according to ther Integer part.

        for (int i = 0 ; i < size; ++i) {
            for (int j = 0; j < size ; ++j) {
                if(dynMap[j].first < dynMap[i].first ){
                    myPair<Integer ,myPair<T ,T> > temp = dynMap[j];
                    dynMap[j] = dynMap[i];
                    dynMap[i] = temp;
                }
            }
        }    
    }
    
    private void setter(){
    	//this function set the occurences and max occurences
    	//then call tje sort function.

        for(int i = 0 ; i < size ; ++i){
            int count=numOfGrams(dynMap[i].second.first,dynMap[i].second.second);
            dynMap[i].first=count;
            if(count > max)
				max = count;         
        }
        sort();
    }

    public BigramDyn(int data){
    	//this function set dataType and take place from memory for dynMap.
        dataType = data;
        dynMap = new myPair[10];
        for(int i  = 0 ; i < dynMap.length ; ++i)
            dynMap[i] = new myPair<Integer ,myPair<T ,T>>(null , null); 
    }
    
    public void readFile(String fileName) throws Exception {
        //This function reads file and fill the map.
    	//if any problem happend then throw exception.
    	// for example , empty file , bad data ...

        Vector<T> data = new Vector<T> ();//holds the data one by one.

        //dataType is undefined if throw exception here.
        if(dataType <= 0 || dataType > 3){
        	System.err.println("Undefined data thype!!");
        	throw new Exception();
        }

        //reading File/////
        try {
            input = new Scanner(new File(fileName));

             //if file doesn't contain anything.
            if (!input.hasNext()){
        		System.err.println("The file is empty!");
            	throw new Exception();
        	}

        	T next = null ;

        	//this loop read data from the file according to dataType.
        	//the add the data to vector that name is data.
        	while(input.hasNext()){
	        	
		        if(dataType == 1)     
		            (next) = (T)(Object)(input.nextInt());
		        else if (dataType == 2)
	                (next) =  (T)input.next();
		        else if(dataType == 3)
	                (next) = (T)(Object)(input.nextDouble());
	    		
	            data.addElement(next);
			}
			    for(int i = 0 ; i < data.size() - 1 ; ++i)
            		addNewElement(data.get(i) , data.get(i + 1));
        		setter();
        }
        catch (FileNotFoundException ex) {
        	System.err.println("The file is not exist!");
            throw new Exception();
        }
        catch(InputMismatchException e){
	    	System.err.println("Bad Data!!");
	    	throw new Exception();
        }finally{
        	input.close();
        }   
    }

    public int numGrams() {//return size of dynMap.
        return size;
    }

    public int numOfGrams(T first, T second) {//returns the occurences of the given pair.
        int total = 0; //holds occurences

        for(int i = 0 ; i < size ; ++i)
            if(dynMap[i].second.first.equals(first) && dynMap[i].second.second.equals(second))
                total++;
        return total;      
    }
    public String toString(){

    	StringBuilder result = new StringBuilder();//holds the output to print out.
    	Vector<myPair<T ,T>> keys = new Vector<myPair<T ,T>>();//holds the keys

    	for(int i = max ; i >= 0 ; --i){
    		for(int j = 0 ; j < numGrams(); ++j){
    			if(dynMap[j].first == i && !keys.contains(dynMap[j].second)){
    				result.append(dynMap[j].second + "->" + dynMap[j].first + "\n");
    				keys.addElement(dynMap[j].second);
    			}
    		}
    	}
        return result.toString();	
    }
    
}
