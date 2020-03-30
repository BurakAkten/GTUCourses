
/**
 *
 * @author aktenburakk
 * @param <T>
 */
public interface Bigram<T> {
    
    public void readFile(String fileName) throws Exception ;
    public int numGrams();
    public int numOfGrams(T first , T second);
    public String toString();
    
}
