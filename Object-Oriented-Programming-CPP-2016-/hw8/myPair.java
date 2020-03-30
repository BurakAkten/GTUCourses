/**
 *
 * @author aktenburakk
 */
@SuppressWarnings("unchecked")
public class myPair<T , E> {

	//this class represents pair. 
	//this class has two different generic types(T,E).
    public T first;
    public E second;
    
    
    public myPair(){
	
    }
    public myPair(T fir , E sec){//constructor for setting first and second
 		first = fir;
 		second = sec;		
    }
    public myPair(myPair<T,E> other){//constructor for assignment one pair to another.
        first = other.first;
        second = other.second;
    }
    
 	//getters.
    public T getFirst(){return first;}
    public E getSecond(){return second;}
 
    public String toString(){
 
        return String.format("%s - %s " ,getFirst(), getSecond() );
    }
    
    //equals and hashcode.
    public boolean equals(Object obj) {

        if (obj == this) 
        	return true;
        if (!(obj instanceof myPair)) {
            return false;
        }

        myPair<T,E> pair = (myPair<T ,E>) obj;

        return pair.first.equals(first) && pair.second.equals(second); 
    }
    
    public int hashCode() {
    	//make a code for every object with two random prime random(17 , 31).
        int result = 17;
        result = 31 * result + first.hashCode();
        result = 31 * result + second.hashCode();
        return result;
    }
}
