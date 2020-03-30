
public interface HashMap<K, V> {

    /**
     * This method take an key and then return the value of the key if it is in the map else throw exception.
     * The returned value is the value of the key that is found firstly in this map.
     * @param key the key for get the value of the key
     * @return the value of the key
     */
    V get(Object key);

    /**
     * This method add the key and value as Entry to the map.
     * @param key the key for the map
     * @param value the value for the map
     * @return the added value
     */
    V put(K key, V value);

    /**
     * This method remove the entry that has the key. The removed entry is the entry that added as last one
     * in the map with this key value.
     * @param key The key to find the entry for removing from entry
     * @return the removed value of the entry or throw exception if tke is not in the map
     */
    V remove(Object key);

    /**
     * This method return the size of the map.
     * @return size of the map
     */
    int size();

    /**
     * This method control the map is empty or not
     * @return true if the map is empty otherwise false.
     */
    boolean isEmpty();
}
