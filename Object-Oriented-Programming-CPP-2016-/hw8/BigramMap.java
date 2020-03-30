import java.io.File;
import java.io.FileNotFoundException;
import java.util.Map;
import java.util.HashMap;
import java.util.Scanner;
import java.util.Vector;
import java.lang.Exception;
import java.util.InputMismatchException;
import java.util.Set;
/**
 *
 * @author aktenburakk
 */
@SuppressWarnings("unchecked")
public class BigramMap<T> implements Bigram<T> {
    
    private Map<myPair <T , T> , Integer > pairDatas;//holds pairs ant their occurences.
    private int dataType;//thpe of the data in file.
    private Scanner input ;
    private int max = 0;//holds maximum occurences
    private Vector<myPair<T ,T> > dataPair;//holds data as pair.
     
    private void makePair(Vector<T> data){
    	//this function make all data in vector pair. 
        dataPair = new Vector<myPair<T , T > >();

        for(int i = 0 ; i < data.size() - 1; i++){
            myPair<T,T> temp = new myPair<T , T >(data.get(i),data.get(i + 1));
            dataPair.add(temp);
		}
    }

    private void fillMap(){

    	//this function fill the map with pairs and their occurences.
        myPair<T,T> temp = new myPair<T,T>(dataPair.get(0));
        pairDatas.put(temp , 1);
        max = 1;

        for (int i = 1 ; i < numGrams() ; ++i){
    		int count=1	;
    		temp =(dataPair.get(i));

    		if(pairDatas.containsKey(temp)){
    			count = pairDatas.get(temp);
    			pairDatas.put(temp , count + 1);
    			count++;
    			if(count > max)
    				max = count;
    		}
    		else
    			pairDatas.put(temp , 1);   			
    	}
    }
    
    public BigramMap(int type){//constructor.
        dataType = type;
    }
    
    public void readFile(String fileName)throws Exception {
    	//This function reads file and fill the map.
    	//if any problem happend then throw exception.
    	// for example , empty file , bad data ...
        
        Vector<T> data = new Vector<T> ();//holds the data one by one.
        
        pairDatas =new HashMap<myPair<T ,T> , Integer>();
        
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
	                (next) =  (T)(input.next());
		        else if(dataType == 3)
	                (next) = (T)(Object)(input.nextDouble());
	    		
	            data.addElement(next);
			}
      		makePair(data);//make the data pair.
      		fillMap();//then fill the map. 
        }
        catch (FileNotFoundException ex) {
        	System.err.println("The file is not exist!");
            throw new Exception();
        }
        catch(InputMismatchException e){
	    	System.err.println("Bad Data!!");
	    	throw new Exception();
	    }	
        finally{
        	input.close();
        }
	}
    
    public int numGrams() {//return size of map.
        return dataPair.size();
    }

    public int numOfGrams(T first, T second) {//returns the occurences of the given pair.
        
        int count = 0;
        for(int i = 0 ;i < dataPair.size(); ++i){
        
            if(dataPair.get(i).first.equals(first) && dataPair.get(i).second.equals(second))
                count++;
        }
        
        return count;
    }
   
    public String toString(){
        
    	StringBuilder result = new StringBuilder();//holds the output to print out.
    	Set<myPair<T ,T>> keys = pairDatas.keySet();//holds the keys

    	for(int i = max ; i >= 0 ; --i){
    		for(myPair<T ,T> key : keys){
    			if(pairDatas.get(key) == i)
    				result.append(key + "->" + pairDatas.get(key) + "\n");
    		}
    	}
        return result.toString();
    }
}

