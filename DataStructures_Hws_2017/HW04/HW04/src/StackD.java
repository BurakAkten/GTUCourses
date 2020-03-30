import java.util.EmptyStackException;
import java.util.LinkedList;
import java.util.Queue;

/**
 * Created by Burak Akten on 21/03/2017.
 */

public class StackD<E>  implements StackInterface {

    private Queue<E> myStack;

    /**
     * Constructor for initializing the myStack.
     */
    public StackD(){
        /*I initialized the queue object as linkedList object , because the queue class is an interface. Because of that
         * we can not initialize it as queue object. */
        myStack = new LinkedList<E>();
    }

    /**
     * This function removes a object from the top of the stack.
     * @throws EmptyStackException if stack is empty
     * @return the object at the top of the stack
     */
    @Override
    public Object pop() throws EmptyStackException{
        if (size() == 0)
            throw new EmptyStackException();
        E[] tempArr = (E[]) myStack.toArray();
        myStack.clear();

        for (int i = 0; i < tempArr.length - 1 ; i++)
            myStack.add(tempArr[i]);
        return  tempArr[tempArr.length - 1];
    }

    /**
     * This function controls the stac is empty or not.
     * @return true if stack is empty.
     */
    @Override
    public boolean isEmpty() {
        return myStack.isEmpty();

    }

    /**
     * @return the size of the stack
     */
    @Override
    public int size() {
        return myStack.size();
    }

    /**
     * This function add an element to the top of the stack.
     * @param obj the object to be added.
     * @return the object that is added.
     */
    @Override
    public Object push(Object obj) {
        myStack.add((E)obj);
        return obj;
    }

    public  String toString(){
        StringBuilder str = new StringBuilder();
        E[] tempArr = (E[]) myStack.toArray();
        for (int i = 0 ; i < size() ; i++) {
            str.append(tempArr[i]);
            if (i != size() - 1)
                str.append(",");
        }
        return str.toString();
    }
}
