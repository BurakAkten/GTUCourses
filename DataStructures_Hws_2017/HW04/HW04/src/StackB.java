import java.util.ArrayList;
import java.util.EmptyStackException;

/**
 * Created by Burak Akten on 21/03/2017.
 */

public class StackB<E>  implements  StackInterface {

    /**
     * Holds the values.
     */
    private ArrayList<E> myStack;

    /**
     * Constructor for initializing the stack.
     */
    public StackB(){
        myStack = new ArrayList<>();
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

    /**
     * This function removes a object from the top of the stack.
     * @return the object at the top of the stack
     * @throws EmptyStackException when stac is empty.
     */
    @Override
    public Object pop() throws EmptyStackException{
        if(size() == 0)
            throw new EmptyStackException();

        E temp = myStack.get(myStack.size() - 1);

        myStack.remove(myStack.size() - 1);

        return temp;
    }

    /**
     * This function controls the stac is empty or not.
     * @return true if stack is empty.
     */
    @Override
    public boolean isEmpty() {
        return myStack.size() == 0;
    }


    public  String toString(){
        StringBuilder str = new StringBuilder();
        for (int i = 0 ; i < size() ; i++) {
            str.append(myStack.get(i));
            if (i != size() - 1)
                str.append(",");
        }
        return str.toString();
    }

}
