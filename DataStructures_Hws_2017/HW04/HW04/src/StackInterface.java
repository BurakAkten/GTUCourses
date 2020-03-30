import java.util.EmptyStackException;

/**
 * Created by Burak Akten on 21/03/2017.
 */
public interface StackInterface<E> {
    /**
     * @return the size of the stack
     */
    public int size();
    /**
     * This function add an element to the top of the stack.
     * @param obj the object to be added.
     * @return the object that is added.
     */
    public E push(E obj);
    /**
     * This function removes a object from the top of the stack.
     * @return the object at the top of the stack
     * @throws EmptyStackException when stac is empty.
     */
    public E pop()  throws EmptyStackException;
    /**
     * This function controls the stac is empty or not.
     * @return true if stack is empty.
     */
    public boolean isEmpty();
}
