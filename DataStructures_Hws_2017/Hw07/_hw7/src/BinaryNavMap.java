/**
 * Created by syucer on 4/24/2017.
 */
import java.util.*;

public class BinaryNavMap<K extends Comparable,V extends Comparable> extends AbstractMap<K,V>
        implements NavigableMap<K,V>, Cloneable, java.io.Serializable
{

    /**
     * This inner class implement the Map.Entry inteface
     * @param <K> for key
     * @param <V> for value
     */
    private static class MyEntry<K extends Comparable, V> implements Comparable<MyEntry<K ,V>>,Map.Entry<K , V>{

        private K key ;
        private V value;

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
            str.append("[");
            str.append(getKey());
            str.append("->");
            str.append(getValue());
            str.append("]");
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

    /**
     * This Node class for holding the key - value and left reference and right reference
     * @param <K> key
     * @param <V> value
     */
    private static class Node<K , V>{
        /**The key */
        private K key;
        /** The value of the key*/
        private V value;
        /** Reference to the left child. */
        private Node<K , V> left;
        /** Reference to the right child. */
        private Node<K , V> right;

        public Node() {
            key = null;
            value = null;
            left = null;
            right = null;
        }
        /**
         * Constructor with a key and a value.
         * @param myKey the value of key variable
         * @param myValue the value of value variable
         */
        public Node(K myKey , V myValue) {
            key = myKey;
            value = myValue;
            left = null;
            right = null;
        }
        /** Return a string representation of the node.
         * @return A string representation of key and value fields.
         */
        public String toString(){
            StringBuilder str = new StringBuilder();
            str.append("Key : ");
            str.append(this.key.toString());
            str.append("-> Value : ");
            str.append(this.value.toString());
            str.append("\n");
            return str.toString();
        }
    }

    /* reference for the root of the tree*/
    private Node<K ,V> root;
    /* for the put method*/
    private V returnedValue;
    /* deleted entry */
    private Entry<K , V> deletedEntry;

    /** Recursive findLower method.
     @param localRoot The local subtree’s root
     @param target The object being sought
     @param entry The entry object to control previous entry
     @return The object, if found, otherwise null
     */
    private  Entry<K , V> findLower(Node < K , V > localRoot, K target , Entry<K ,V> entry) {
        if (localRoot == null)
            return entry;
        // Compare the target with the data field at the root.
        int compResult = target.compareTo(localRoot.key);
        if (compResult == 0 && localRoot.left == null)
            return entry;
        else if(compResult == 0 && localRoot.left != null)
            return new MyEntry<K, V>(localRoot.left.key , localRoot.left.value);
        else if (compResult < 0)
            return  findLower(localRoot.left, target , entry);
        else{
            return findLower(localRoot.right, target , new MyEntry<K, V>(localRoot.key , localRoot.value));

        }
    }
    /** Recursive findFloor method.
     @param localRoot The local subtree’s root
     @param target The object being sought
     @param entry The entry object to control previous entry
     @return The object, if found, otherwise null
     */
    private  Entry<K , V> findFloor(Node < K , V > localRoot, K target , Entry<K ,V> entry) {
        if (localRoot == null)
            return entry;
        // Compare the target with the data field at the root.
        int compResult = target.compareTo(localRoot.key);

        if(compResult == 0)
            return new MyEntry<K, V>(localRoot.key , localRoot.value);
        else if (compResult < 0)
            return  findFloor(localRoot.left, target , entry);
        else{
            return findFloor(localRoot.right, target , new MyEntry<K, V>(localRoot.key , localRoot.value));

        }
    }
    /** Recursive findCeiling method.
     @param localRoot The local subtree’s root
     @param target The object being sought
     @param entry The entry object to control previous entry
     @return The object, if found, otherwise null
     */
    private  Entry<K , V> findCeiling(Node < K , V > localRoot, K target , Entry<K ,V> entry) {
        if (localRoot == null)
            return entry;
        // Compare the target with the data field at the root.
        int compResult = target.compareTo(localRoot.key);

        if(compResult == 0)
            return new MyEntry<K, V>(localRoot.key , localRoot.value);
        else if (compResult > 0)
            return  findFloor(localRoot.right, target , entry);
        else{
            return findFloor(localRoot.left, target , new MyEntry<K, V>(localRoot.key , localRoot.value));
        }
    }

    /** Recursive findHigher method.
     @param localRoot The local subtree’s root
     @param target The object being sought
     @param entry The entry object to control previous entry
     @return The object, if found, otherwise null
     */
    private  Entry<K , V> findHigher(Node < K , V > localRoot, K target , Entry<K ,V> entry) {
        if (localRoot == null)
            return entry;
        // Compare the target with the data field at the root.
        int compResult = target.compareTo(localRoot.key);
        if (compResult == 0 && localRoot.right == null)
            return entry;
        else if(compResult == 0 && localRoot.right != null)
            return new MyEntry<K, V>(localRoot.right.key , localRoot.right.value);
        else if (compResult > 0)
            return  findLower(localRoot.right, target , entry);
        else{
            return findLower(localRoot.left, target , new MyEntry<K, V>(localRoot.key , localRoot.value));

        }
    }

    /**
     * This method find the first entry recursively.
     * @param localRoot the root to control.
     * @return  An entry.
     */
    private Entry<K , V> firstEntry(Node<K , V> localRoot){
        if(localRoot.left == null)
            return new MyEntry<K, V>(localRoot.key,localRoot.value);
        else
            return firstEntry(localRoot.left);
    }
    /**
     * This method find the last entry recursively.
     * @param localRoot the root to control.
     * @return  An entry.
     */
    private Entry<K , V> lastEntry(Node<K , V> localRoot){
        if(localRoot.right == null)
            return new MyEntry<K, V>(localRoot.key,localRoot.value);
        else
            return firstEntry(localRoot.right);
    }

    /**
     * This method poll the first entry.
     * @param localRoot a root for traversing the map.
     * @return the removed entry
     */
    private Node<K , V> pollFirst(Node<K , V> localRoot){
        if(localRoot.left == null ){
            deletedEntry = new MyEntry<K, V>(localRoot.key , localRoot.value);
            return localRoot.right;
        }
        else {
            localRoot.left = pollFirst(localRoot.left);
            return localRoot;
        }
    }
    /**
     * This method poll the last entry.
     * @param localRoot a root for traversing the map.
     * @return the removed entry
     */
    private Node<K , V> pollLast(Node<K , V> localRoot){
        if(localRoot.right == null ){
            deletedEntry = new MyEntry<K, V>(localRoot.key , localRoot.value);
            return localRoot.left;
        }
        else {
            localRoot.right = pollLast(localRoot.right);
            return localRoot;
        }
    }

    /**
     * This method fill the set as level-orderly
     * @param set the set to be filled
     * @param localroot the root to be traversed
     */
    private void levelOrder(Set<Entry<K , V>> set ,  Node<K ,V> localroot){

        /*TempQueue for holds the tree entries temporary.*/
        Queue<Node<K , V>> tempQueue = new LinkedList<>();
        /*Temporary root.*/
        Node<K , V> tempRoot = this.root;
        /*adding first node to the tempQueue*/
        tempQueue.add(tempRoot);
        while(!tempQueue.isEmpty()){
            set.add(new MyEntry<>(tempQueue.peek().key , tempQueue.peek().value));
            if(tempRoot.left != null)
                tempQueue.add(tempRoot.left);
            if (tempRoot.right != null)
                tempQueue.add(tempRoot.right);
            tempQueue.poll();
            tempRoot = tempQueue.peek();
        }
    }

    /** Recursive add method.
     *
     *@param localRoot The local root of the subtree
     *@param key The object key  to be inserted
     *@param value The object value to be inserted
     *@return The new local root that now contains the inserted item
     */
    private Node < K ,V >  add(Node < K ,V > localRoot, K key , V value) {
        if (localRoot == null) {
            // key is not in the tree — insert it.
            returnedValue = null;
            return new Node<> (key , value);
        }
        else if (key.compareTo(localRoot.key) == 0) {
            // key is equal to localRoot.key
            returnedValue   = localRoot.value ;
            localRoot.value = value;
            return localRoot;
        }
        else if (key.compareTo(localRoot.key) < 0) {
            // key is less than localRoot.key
            localRoot.left =  add(localRoot.left, key , value);
            return localRoot;
        }
        else {
            // key is greater than localRoot.key
            localRoot.right = add(localRoot.right, key , value );
            return localRoot;
        }
    }

    /**
     * This method wrapper function for reverse the map
     * @param localroot the reference of the root
     */
    private void reverseTheMap(Node<K ,V> localroot){

        if(localroot != null){
            Node<K ,V> tempRoot = localroot.left; // temp root for the left reference of the localroot

            localroot.left = localroot.right;
            localroot.right = tempRoot;

            /* Recursive part for both part of the tree to reverse*/
            reverseTheMap(localroot.left);
            reverseTheMap(localroot.right);
        }
    }

    /**
     * No parameter constructor.
     */
    public BinaryNavMap(){}

    /**
     * This construvtor take a node reference to assignt to this.
     */
    public BinaryNavMap(Node<K ,V> newNode){
        this.root = newNode;
    }

    @Override
    public Set<Entry<K, V>> entrySet() {
        /* The set is created to be filled with the entries*/
        Set<Entry<K , V>> entrySet = new HashSet<Entry<K , V>>();

        if(root != null){
            Node<K , V> tempRoot = root;
            levelOrder(entrySet , tempRoot );
        }
        return  entrySet;
    }

    /**
     * Returns a key-value mapping associated with the greatest key
     * strictly less than the given key, or {@code null} if there is
     * no such key.
     *
     * @param key the key
     * @return an entry with the greatest key less than {@code key},
     * or {@code null} if there is no such key
     * @throws ClassCastException   if the specified key cannot be compared
     *                              with the keys currently in the map
     * @throws NullPointerException if the specified key is null
     *                              and this map does not permit null keys
     */
    @Override
    public Entry<K, V> lowerEntry(K key) {
        if(key == null)
            throw new NullPointerException();
        return findLower(this.root , key , null);

    }

    /**
     * Returns the greatest key strictly less than the given key, or
     * {@code null} if there is no such key.
     *
     * @param key the key
     * @return the greatest key less than {@code key},
     * or {@code null} if there is no such key
     * @throws ClassCastException   if the specified key cannot be compared
     *                              with the keys currently in the map
     * @throws NullPointerException if the specified key is null
     *                              and this map does not permit null keys
     */
    @Override
    public K lowerKey(K key) {
        Entry<K , V> entry = lowerEntry(key);
        if(entry == null)
            return null;

        return entry.getKey();

    }

    /**
     * Returns a key-value mapping associated with the greatest key
     * less than or equal to the given key, or {@code null} if there
     * is no such key.
     *
     * @param key the key
     * @return an entry with the greatest key less than or equal to
     * {@code key}, or {@code null} if there is no such key
     * @throws ClassCastException   if the specified key cannot be compared
     *                              with the keys currently in the map
     * @throws NullPointerException if the specified key is null
     *                              and this map does not permit null keys
     */
    @Override
    public Entry<K, V> floorEntry(K key) {
        if(key == null)
            throw new NullPointerException();
        return findFloor(this.root , key , null);
    }

    /**
     * Returns the greatest key less than or equal to the given key,
     * or {@code null} if there is no such key.
     *
     * @param key the key
     * @return the greatest key less than or equal to {@code key},
     * or {@code null} if there is no such key
     * @throws ClassCastException   if the specified key cannot be compared
     *                              with the keys currently in the map
     * @throws NullPointerException if the specified key is null
     *                              and this map does not permit null keys
     */
    @Override
    public K floorKey(K key) {
        Entry<K , V> entry = floorEntry(key);
        if(entry == null)
            return null;
        return entry.getKey();
    }

    /**
     * Returns a key-value mapping associated with the least key
     * greater than or equal to the given key, or {@code null} if
     * there is no such key.
     *
     * @param key the key
     * @return an entry with the least key greater than or equal to
     * {@code key}, or {@code null} if there is no such key
     * @throws ClassCastException   if the specified key cannot be compared
     *                              with the keys currently in the map
     * @throws NullPointerException if the specified key is null
     *                              and this map does not permit null keys
     */
    @Override
    public Entry<K, V> ceilingEntry(K key) {
        if(key == null)
            throw new NullPointerException();
        return findCeiling(this.root , key , null);
    }

    /**
     * Returns the least key greater than or equal to the given key,
     * or {@code null} if there is no such key.
     *
     * @param key the key
     * @return the least key greater than or equal to {@code key},
     * or {@code null} if there is no such key
     * @throws ClassCastException   if the specified key cannot be compared
     *                              with the keys currently in the map
     * @throws NullPointerException if the specified key is null
     *                              and this map does not permit null keys
     */
    @Override
    public K ceilingKey(K key) {
        Entry<K , V> entry = ceilingEntry(key);
        if(entry == null)
            return null;
        return entry.getKey();
    }

    /**
     * Returns a key-value mapping associated with the least key
     * strictly greater than the given key, or {@code null} if there
     * is no such key.
     *
     * @param key the key
     * @return an entry with the least key greater than {@code key},
     * or {@code null} if there is no such key
     * @throws ClassCastException   if the specified key cannot be compared
     *                              with the keys currently in the map
     * @throws NullPointerException if the specified key is null
     *                              and this map does not permit null keys
     */
    @Override
    public Entry<K, V> higherEntry(K key) {
        if(key == null)
            throw new NullPointerException();
        return findHigher(this.root , key , null);
    }

    /**
     * Returns the least key strictly greater than the given key, or
     * {@code null} if there is no such key.
     *
     * @param key the key
     * @return the least key greater than {@code key},
     * or {@code null} if there is no such key
     * @throws ClassCastException   if the specified key cannot be compared
     *                              with the keys currently in the map
     * @throws NullPointerException if the specified key is null
     *                              and this map does not permit null keys
     */
    @Override
    public K higherKey(K key) {
        Entry<K , V> entry = higherEntry(key);
        if(entry == null)
            return null;
        return entry.getKey();
    }

    /**
     * Returns a key-value mapping associated with the least
     * key in this map, or {@code null} if the map is empty.
     *
     * @return an entry with the least key,
     * or {@code null} if this map is empty
     */
    @Override
    public Entry<K, V> firstEntry() {
        if(this.root == null)
            return null;
        return firstEntry(this.root);
    }

    /**
     * Returns a key-value mapping associated with the greatest
     * key in this map, or {@code null} if the map is empty.
     *
     * @return an entry with the greatest key,
     * or {@code null} if this map is empty
     */
    @Override
    public Entry<K, V> lastEntry() {
        if(this.root == null)
            return null;
        return lastEntry(this.root);
    }

    /**
     * Removes and returns a key-value mapping associated with
     * the least key in this map, or {@code null} if the map is empty.
     *
     * @return the removed first entry of this map,
     * or {@code null} if this map is empty
     */
    @Override
    public Entry<K, V> pollFirstEntry() {
        if(this.root == null)
            return null;
        this.root = pollFirst(this.root);
        return deletedEntry;
    }

    /**
     * Removes and returns a key-value mapping associated with
     * the greatest key in this map, or {@code null} if the map is empty.
     *
     * @return the removed last entry of this map,
     * or {@code null} if this map is empty
     */
    @Override
    public Entry<K, V> pollLastEntry() {
        if(this.root == null)
            return null;
        this.root = pollLast(this.root);
        return deletedEntry;
    }

    /**
     * Returns a reverse order view of the mappings contained in this map.
     * The descending map is backed by this map, so changes to the map are
     * reflected in the descending map, and vice-versa.  If either map is
     * modified while an iteration over a collection view of either map
     * is in progress (except through the iterator's own {@code remove}
     * operation), the results of the iteration are undefined.
     * <p>
     * <p>The returned map has an ordering equivalent to
     * <tt>{@link Collections#reverseOrder(Comparator) Collections.reverseOrder}(comparator())</tt>.
     * The expression {@code m.descendingMap().descendingMap()} returns a
     * view of {@code m} essentially equivalent to {@code m}.
     *
     * @return a reverse order view of this map
     */
    @Override
    public NavigableMap<K, V> descendingMap() {
        reverseTheMap(this.root); /* reverse the map */
        BinaryNavMap<K , V> newMap = new BinaryNavMap<K, V>(this.root);
        reverseTheMap(this.root); /* than reverse again to be old one*/
        return newMap;
    }

    /**
     * Returns a {@link NavigableSet} view of the keys contained in this map.
     * The set's iterator returns the keys in ascending order.
     * The set is backed by the map, so changes to the map are reflected in
     * the set, and vice-versa.  If the map is modified while an iteration
     * over the set is in progress (except through the iterator's own {@code
     * remove} operation), the results of the iteration are undefined.  The
     * set supports element removal, which removes the corresponding mapping
     * from the map, via the {@code Iterator.remove}, {@code Set.remove},
     * {@code removeAll}, {@code retainAll}, and {@code clear} operations.
     * It does not support the {@code add} or {@code addAll} operations.
     *
     * @return a navigable set view of the keys in this map
     */
    @Override
    public NavigableSet<K> navigableKeySet() {
        NavigableSet<K> keyset = new TreeSet<K>();

        Iterator<Entry<K, V>> iter = this.entrySet().iterator();
        while(iter.hasNext())
            keyset.add(iter.next().getKey());

        return keyset;
    }

    /**
     * Returns a reverse order {@link NavigableSet} view of the keys contained in this map.
     * The set's iterator returns the keys in descending order.
     * The set is backed by the map, so changes to the map are reflected in
     * the set, and vice-versa.  If the map is modified while an iteration
     * over the set is in progress (except through the iterator's own {@code
     * remove} operation), the results of the iteration are undefined.  The
     * set supports element removal, which removes the corresponding mapping
     * from the map, via the {@code Iterator.remove}, {@code Set.remove},
     * {@code removeAll}, {@code retainAll}, and {@code clear} operations.
     * It does not support the {@code add} or {@code addAll} operations.
     *
     * @return a reverse order navigable set view of the keys in this map
     */
    @Override
    public NavigableSet<K> descendingKeySet()   {
        NavigableSet<K> keyset =  new TreeSet<K>();

        Iterator<Entry<K, V>> iter = this.descendingMap().entrySet().iterator();
        while(iter.hasNext())
            keyset.add(iter.next().getKey());

        return keyset;
    }

    /**
     * Returns a view of the portion of this map whose keys range from
     * {@code fromKey} to {@code toKey}.  If {@code fromKey} and
     * {@code toKey} are equal, the returned map is empty unless
     * {@code fromInclusive} and {@code toInclusive} are both true.  The
     * returned map is backed by this map, so changes in the returned map are
     * reflected in this map, and vice-versa.  The returned map supports all
     * optional map operations that this map supports.
     * <p>
     * <p>The returned map will throw an {@code IllegalArgumentException}
     * on an attempt to insert a key outside of its range, or to construct a
     * submap either of whose endpoints lie outside its range.
     *
     * @param fromKey       low endpoint of the keys in the returned map
     * @param fromInclusive {@code true} if the low endpoint
     *                      is to be included in the returned view
     * @param toKey         high endpoint of the keys in the returned map
     * @param toInclusive   {@code true} if the high endpoint
     *                      is to be included in the returned view
     * @return a view of the portion of this map whose keys range from
     * {@code fromKey} to {@code toKey}
     * @throws ClassCastException       if {@code fromKey} and {@code toKey}
     *                                  cannot be compared to one another using this map's comparator
     *                                  (or, if the map has no comparator, using natural ordering).
     *                                  Implementations may, but are not required to, throw this
     *                                  exception if {@code fromKey} or {@code toKey}
     *                                  cannot be compared to keys currently in the map.
     * @throws NullPointerException     if {@code fromKey} or {@code toKey}
     *                                  is null and this map does not permit null keys
     * @throws IllegalArgumentException if {@code fromKey} is greater than
     *                                  {@code toKey}; or if this map itself has a restricted
     *                                  range, and {@code fromKey} or {@code toKey} lies
     *                                  outside the bounds of the range
     */
    @Override
        public NavigableMap<K, V> subMap(K fromKey, boolean fromInclusive, K toKey, boolean toInclusive) {

        if(fromKey == null || toKey == null)
            throw new NullPointerException();
        if(fromKey.compareTo(toKey) < 0 )// Because the map tree from bigger to smaller
            throw new IllegalArgumentException();

        if(fromKey.equals(toKey) && !(fromInclusive && toInclusive))
            return new BinaryNavMap<K , V >();

        NavigableMap<K ,V> subMap = new BinaryNavMap<>();
        Iterator<Entry<K ,V>> iter = this.entrySet().iterator();
        /* By using the iterator of the set interface , the map is traversed and than the new submap is created*/
        while(iter.hasNext()){
            K nextKey = iter.next().getKey();
            int result1 = nextKey.compareTo(fromKey);
            int result2 = nextKey.compareTo(toKey);
            if(( result1 <= 0 && result2 >= 0)) {
                if((result1 == 0 && !fromInclusive) ||( result2 == 0 && !toInclusive)){}
                else
                    subMap.put(nextKey, get(nextKey));
            }
        }
        return subMap;
    }

    /**
     * Returns a view of the portion of this map whose keys are less than (or
     * equal to, if {@code inclusive} is true) {@code toKey}.  The returned
     * map is backed by this map, so changes in the returned map are reflected
     * in this map, and vice-versa.  The returned map supports all optional
     * map operations that this map supports.
     * <p>
     * <p>The returned map will throw an {@code IllegalArgumentException}
     * on an attempt to insert a key outside its range.
     *
     * @param toKey     high endpoint of the keys in the returned map
     * @param inclusive {@code true} if the high endpoint
     *                  is to be included in the returned view
     * @return a view of the portion of this map whose keys are less than
     * (or equal to, if {@code inclusive} is true) {@code toKey}
     * @throws ClassCastException       if {@code toKey} is not compatible
     *                                  with this map's comparator (or, if the map has no comparator,
     *                                  if {@code toKey} does not implement {@link Comparable}).
     *                                  Implementations may, but are not required to, throw this
     *                                  exception if {@code toKey} cannot be compared to keys
     *                                  currently in the map.
     * @throws NullPointerException     if {@code toKey} is null
     *                                  and this map does not permit null keys
     * @throws IllegalArgumentException if this map itself has a
     *                                  restricted range, and {@code toKey} lies outside the
     *                                  bounds of the range
     */
    @Override
    public NavigableMap<K, V> headMap(K toKey, boolean inclusive) {
        return subMap(this.firstKey() , true , toKey , inclusive);
    }

    /**
     * Returns a view of the portion of this map whose keys are greater than (or
     * equal to, if {@code inclusive} is true) {@code fromKey}.  The returned
     * map is backed by this map, so changes in the returned map are reflected
     * in this map, and vice-versa.  The returned map supports all optional
     * map operations that this map supports.
     * <p>
     * <p>The returned map will throw an {@code IllegalArgumentException}
     * on an attempt to insert a key outside its range.
     *
     * @param fromKey   low endpoint of the keys in the returned map
     * @param inclusive {@code true} if the low endpoint
     *                  is to be included in the returned view
     * @return a view of the portion of this map whose keys are greater than
     * (or equal to, if {@code inclusive} is true) {@code fromKey}
     * @throws ClassCastException       if {@code fromKey} is not compatible
     *                                  with this map's comparator (or, if the map has no comparator,
     *                                  if {@code fromKey} does not implement {@link Comparable}).
     *                                  Implementations may, but are not required to, throw this
     *                                  exception if {@code fromKey} cannot be compared to keys
     *                                  currently in the map.
     * @throws NullPointerException     if {@code fromKey} is null
     *                                  and this map does not permit null keys
     * @throws IllegalArgumentException if this map itself has a
     *                                  restricted range, and {@code fromKey} lies outside the
     *                                  bounds of the range
     */
    @Override
    public NavigableMap<K, V> tailMap(K fromKey, boolean inclusive) {
        return subMap(fromKey , inclusive , this.lastKey() , true);
    }

    /**
     * Returns the comparator used to order the keys in this map, or
     * {@code null} if this map uses the {@linkplain Comparable
     * natural ordering} of its keys.
     *
     * @return the comparator used to order the keys in this map,
     * or {@code null} if this map uses the natural ordering
     * of its keys
     */
    @Override
    public Comparator<? super K> comparator() {
        return null;
    }

    /**
     * {@inheritDoc}
     * <p>
     * <p>Equivalent to {@code subMap(fromKey, true, toKey, false)}.
     *
     * @param fromKey
     * @param toKey
     * @throws ClassCastException       {@inheritDoc}
     * @throws NullPointerException     {@inheritDoc}
     * @throws IllegalArgumentException {@inheritDoc}
     */
    @Override
    public SortedMap<K, V> subMap(K fromKey, K toKey) {

        return subMap(fromKey , true , toKey ,false);
    }

    /**
     * {@inheritDoc}
     * <p>
     * <p>Equivalent to {@code headMap(toKey, false)}.
     *
     * @param toKey
     * @throws ClassCastException       {@inheritDoc}
     * @throws NullPointerException     {@inheritDoc}
     * @throws IllegalArgumentException {@inheritDoc}
     */
    @Override
    public SortedMap<K, V> headMap(K toKey) {

       return headMap(toKey , false);
    }

    /**
     * {@inheritDoc}
     * <p>
     * <p>Equivalent to {@code tailMap(fromKey, true)}.
     *
     * @param fromKey
     * @throws ClassCastException       {@inheritDoc}
     * @throws NullPointerException     {@inheritDoc}
     * @throws IllegalArgumentException {@inheritDoc}
     */
    @Override
    public SortedMap<K, V> tailMap(K fromKey) {

        return tailMap(fromKey , true);
    }

    /**
     * Returns the first (lowest) key currently in this map.
     *
     * @return the first (lowest) key currently in this map
     * @throws NoSuchElementException if this map is empty
     */
    @Override
    public K firstKey() {
        Entry<K , V> entry = firstEntry();
        if(entry == null)
            throw new NoSuchElementException();
        return entry.getKey();
    }

    /**
     * Returns the last (highest) key currently in this map.
     *
     * @return the last (highest) key currently in this map
     * @throws NoSuchElementException if this map is empty
     */
    @Override
    public K lastKey() {
        Entry<K , V> entry = lastEntry();
        if(entry == null)
            throw new NoSuchElementException();
        return entry.getKey();
    }
    /**
     * {@inheritDoc}
     *
     *
     * This implementation always throws an
     * <tt>UnsupportedOperationException</tt>.
     *
     * @throws UnsupportedOperationException {@inheritDoc}
     * @throws ClassCastException            {@inheritDoc}
     * @throws NullPointerException          {@inheritDoc}
     * @throws IllegalArgumentException      {@inheritDoc}
     * @return the previous value associated with key, or null if there was no mapping for key.
     */
    @Override
    public V put(K key, V value){

        if(key == null || value == null)
            throw new NullPointerException();
        returnedValue = null;
        root = add(root , key , value);
        return returnedValue;
    }

    public String toString(){
        if(this.root == null)
            return new StringBuilder("Null Tree!!\n").toString();

        StringBuilder str = new StringBuilder();
        Iterator<Entry<K , V>> entry = this.entrySet().iterator();
        while(entry.hasNext()){
            str.append(entry.next().toString());
        }
        return str.toString();
    }
}