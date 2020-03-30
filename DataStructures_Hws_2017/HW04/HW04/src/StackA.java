import java.util.ArrayList;
import java.util.EmptyStackException;

/**
 * Created by Burak Akten on 21/03/2017.
 */

public class StackA<E> extends ArrayList implements StackInterface {
    /**
     * This function removes a object from the top of the stack.
     * @return the object at the top of the stack
     * @throws EmptyStackException when stac is empty.
     */
    @Override
    public Object pop() throws EmptyStackException {

        if(size() == 0)
            throw new EmptyStackException();
        Object temp = super.get(super.size() - 1);
        super.remove(super.size() - 1);
        return temp;
    }

    /**
     * This function controls the stac is empty or not.
     * @return true if stack is empty.
     */
    @Override
    public boolean isEmpty() {
        return super.isEmpty();
    }

    /**
     * @return the size of the stack
     */
    @Override
    public int size() {
        return super.size();
    }

    /**
     * This function add an element to the top of the stack.
     * @param obj the object to be added.
     * @return the object that is added.
     */
    @Override
    public Object push(Object obj) {
        super.add((E) obj);
        return obj;
    }
    public  String toString(){
        StringBuilder str = new StringBuilder();
        for (int i = 0 ; i < size() ; i++) {
            str.append(super.get(i));
            if (i != size() - 1)
                str.append(",");
        }
        return str.toString();
    }

}

