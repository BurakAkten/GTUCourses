import java.util.*;

/**
 * Created by syucer on 4/24/2017.
 */
public class HashTableChaining<K extends Comparable, V extends Comparable> implements HashMap<K, V> {
    /** The table */
    /**
     * This inner class implement the Map.Entry inteface
     * @param <K> for key
     * @param <V> for value
     */
    private static class MyEntry<K extends Comparable, V> implements Comparable<MyEntry<K ,V>>,Map.Entry<K , V>{

        /* Key for entry*/
        private K key ;
        /* Value for entry*/
        private V value;

        /**
         * This constructor initialize the member values with these parameters
         * @param key the key for entry
         * @param value the value for the entry
         */
        public MyEntry(K key, V value) {
            this.key = key;
            this.value = value;
        }

        /**
         * Returns the key corresponding to this entry.
         *
         * @return the key corresponding to this entry
         * @throws IllegalStateException implementations may, but are not
         *                               required to, throw this exception if the entry has been
         *                               removed from the backing map.
         */
        @Override
        public K getKey() {
            return this.key;
        }

        /**
         * Returns the value corresponding to this entry.  If the mapping
         * has been removed from the backing map (by the iterator's
         * <tt>remove</tt> operation), the results of this call are undefined.
         *
         * @return the value corresponding to this entry
         * @throws IllegalStateException implementations may, but are not
         *                               required to, throw this exception if the entry has been
         *                               removed from the backing map.
         */
        @Override
        public V getValue() {
            return this.value;
        }

        /**
         * Replaces the value corresponding to this entry with the specified
         * value (optional operation).  (Writes through to the map.)  The
         * behavior of this call is undefined if the mapping has already been
         * removed from the map (by the iterator's <tt>remove</tt> operation).
         *
         * @param value new value to be stored in this entry
         * @return old value corresponding to the entry
         * @throws UnsupportedOperationException if the <tt>put</tt> operation
         *                                       is not supported by the backing map
         * @throws ClassCastException            if the class of the specified value
         *                                       prevents it from being stored in the backing map
         * @throws NullPointerException          if the backing map does not permit
         *                                       null values, and the specified value is null
         * @throws IllegalArgumentException      if some property of this value
         *                                       prevents it from being stored in the backing map
         * @throws IllegalStateException         implementations may, but are not
         *                                       required to, throw this exception if the entry has been
         *                                       removed from the backing map.
         */
        @Override
        public V setValue(V value) {

            if(value == null)
                throw new NullPointerException();
            V returned = this.value;
            this.value = value;
            return returned;
        }
        @Override
        public String toString(){
            StringBuilder str = new StringBuilder();
            str.append(getKey());
            str.append("->");
            str.append(getValue());
            return  str.toString();
        }

        /**
         * Compares this object with the specified object for order.  Returns a
         * negative integer, zero, or a positive integer as this object is less
         * than, equal to, or greater than the specified object.
         * <p>
         * <p>The implementor must ensure <tt>sgn(x.compareTo(y)) ==
         * -sgn(y.compareTo(x))</tt> for all <tt>x</tt> and <tt>y</tt>.  (This
         * implies that <tt>x.compareTo(y)</tt> must throw an exception iff
         * <tt>y.compareTo(x)</tt> throws an exception.)
         * <p>
         * <p>The implementor must also ensure that the relation is transitive:
         * <tt>(x.compareTo(y)&gt;0 &amp;&amp; y.compareTo(z)&gt;0)</tt> implies
         * <tt>x.compareTo(z)&gt;0</tt>.
         * <p>
         * <p>Finally, the implementor must ensure that <tt>x.compareTo(y)==0</tt>
         * implies that <tt>sgn(x.compareTo(z)) == sgn(y.compareTo(z))</tt>, for
         * all <tt>z</tt>.
         * <p>
         * <p>It is strongly recommended, but <i>not</i> strictly required that
         * <tt>(x.compareTo(y)==0) == (x.equals(y))</tt>.  Generally speaking, any
         * class that implements the <tt>Comparable</tt> interface and violates
         * this condition should clearly indicate this fact.  The recommended
         * language is "Note: this class has a natural ordering that is
         * inconsistent with equals."
         * <p>
         * <p>In the foregoing description, the notation
         * <tt>sgn(</tt><i>expression</i><tt>)</tt> designates the mathematical
         * <i>signum</i> function, which is defined to return one of <tt>-1</tt>,
         * <tt>0</tt>, or <tt>1</tt> according to whether the value of
         * <i>expression</i> is negative, zero or positive.
         *
         * @param o the object to be compared.
         * @return a negative integer, zero, or a positive integer as this object
         * is less than, equal to, or greater than the specified object.
         * @throws NullPointerException if the specified object is null
         * @throws ClassCastException   if the specified object's type prevents it
         *                              from being compared to this object.
         */
        @Override
        public int compareTo(MyEntry<K, V> o) {
            if(o == null)
                throw new NullPointerException();
            return getKey().compareTo(o.getKey());
        }
    }

    /* The hash table*/
    private ArrayList<ArrayList<Map.Entry<K ,V>>> hashTable;
    /*The size of hash table*/
    private int size;
    /*The capacity of the hash table*/
    private  int cap;

    /**
     * This method calculate the hash index for the key.
     * @param key the key that the index is calculated for
     * @return the hasd index of the key.
     */
    private int calculateTheHashIndex(K key){
        int hashCode = key.hashCode() ; // calling the hashCode method
        if(hashCode < 0) // if hashcode is negatif then make it pozitif
            hashCode = hashCode * (-1);
        return hashCode % cap; //return the index
    }

    /**
     * This method makes the capacity of the arraylist bigger.
     * @param list an arraylist to increment its capacity
     */
    private ArrayList<Map.Entry<K,V>> reload(ArrayList<Map.Entry<K , V>> list){
        //Temp array with the capacity that is list.size + 10
        ArrayList<Map.Entry<K ,V>> temp = new ArrayList<>(list.size()  + 10);
        //adding all the element into the temp
        temp.addAll(list);
        //making the other places null
        for(int i = list.size() ; i < list.size() + 10 ; i++)
            temp.add( i ,null);
        list = temp;
        return list;
    }

    /**
     * No parameter constructor for initialisation of hashtable.
     */
    public HashTableChaining(){

        size  = 0 ;
        cap = 11 ; // for make the collision less
        hashTable = new ArrayList<>(cap);
        // the table is making full with null value.
        for(int i = 0; i < this.cap ; ++i){
            ArrayList<Map.Entry<K ,V >> temp = new ArrayList<>(cap);
            hashTable.add(i , temp);
            for (int j = 0; j  < cap ; ++j)
                hashTable.get(i).add( null);
        }
    }

    /**
     * This method take an key and then return the value of the key if it is in the map else throw exception.
     * The returned value is the value of the key that is found firstly in this map.
     * @param key the key for get the value of the key
     * @return the value of the key
     */
    @Override
    public V get(Object key){
        int index = calculateTheHashIndex((K) key);
        if(index > cap)
            throw new IndexOutOfBoundsException();

        int currentIndex = 0;
        /*The first value with this key in the index is being found then returned.*/
        while(currentIndex < hashTable.get(index).size()){
            if(((K) key).compareTo(hashTable.get(index).get(currentIndex).getKey()) == 0)
                return hashTable.get(index).get(currentIndex).getValue();
            currentIndex++;
        }
        throw new NoSuchElementException();
    }

    /**
     * This method add the key and value as Entry to the map.
     * @param key the key for the map
     * @param value the value for the map
     * @return the added value
     */
    @Override
    public V put(K key, V value) {
        if(key == null || value == null)
            throw new NullPointerException();
        int index  = calculateTheHashIndex(key);
        boolean flag = true;
        MyEntry<K ,V> added = new MyEntry<K, V>(key , value);
        if(hashTable.get(index).get(0) == null)
            hashTable.get(index).set(0 ,added );
        else{
            int currentIndex = 1;
            while( flag){

                if(currentIndex >= cap)
                    hashTable.set(index , reload(hashTable.get(index)));
                if(hashTable.get(index).get(currentIndex) != null)
                    currentIndex++;
                else
                    flag = false;
            }
            hashTable.get(index).set(currentIndex , added);
        }
        size++;
        return added.getValue();
    }

    /**
     * This method remove the entry that has the key. The removed entry is the entry that added as last one
     * in the map with this key value.
     * @param key The key to find the entry for removing from entry
     * @return the removed value of the entry or throw exception if tke is not in the map

     */
    @Override
    public V remove(Object key){
        int index = calculateTheHashIndex((K) key);
        if(index > cap)
            throw new IndexOutOfBoundsException();

        V deleted = null;
        boolean flag = true;

        int currentIndex = hashTable.get(index).size() - 1;
        /* When the last entry that is added with this key as last one found then removing the entry*/
        while(currentIndex >= 0  && flag){
            if(hashTable.get(index).get(currentIndex) != null &&
                    ((K) key).compareTo(hashTable.get(index).get(currentIndex).getKey()) == 0) {
                deleted = hashTable.get(index).get(currentIndex).getValue();
                hashTable.get(index).set(currentIndex , null);
                flag = false;
                size--;
            }
            currentIndex--;
        }

        if(deleted == null)
            throw new NoSuchElementException();
        return deleted;
    }
    /**
     * This method return the size of the map.
     * @return size of the map
     */
    @Override
    public int size() {
        return this.size;
    }
    /**
     * This method control the map is empty or not
     * @return true if the map is empty otherwise false.
     */
    @Override
    public boolean isEmpty() {
        return size() == 0 ? true : false;
    }

    @Override
    public String toString(){
        if(hashTable == null)
            return new StringBuilder("The hashMap is empty!\n").toString();
        StringBuilder str = new StringBuilder();
        for (int i = 0 ; i < hashTable.size() ; i++) {
            str.append(hashTable.get(i).toString());
            str.append("\n");
        }
        return str.toString();
    }
}
