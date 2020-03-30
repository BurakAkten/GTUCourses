import java.util.EmptyStackException;

/**
 * Created by Burak Akten on 22/03/2017.
 */

public class StackC<E> implements StackInterface {

    /**
     * This is inner class that hold the next reference and data.
     * @param <E> the generic type.
     */
    private static class Node<E>{

        /**The reference to the data*/
        private E data;
        /** The reference to the next node*/
        private Node<E> next;
        //Constructor
        /**
         * Creates a new node that references another node
         * @param dataItem The data stored
         * @param nodeRef The node references by new node
         */
        private Node(E dataItem , Node<E> nodeRef){
            data = dataItem;
            next = nodeRef;
        }
    }

    /**
     * Holds the reference of head of the stack;
     */
    private Node<E> head = null;
    /**
     * Holds the size of the stack
     */
    private int size = 0;

    /**
     * This method return the node that is asked
     * @param index the index of the asked item.
     * @return the asked node reference.
     */
    private Node<E> getTheNode(int index){

        Node<E> node = head;
        for(int i = 0; i < index && node != null ; i++ )
            node = node.next;
        return node;
    }

    /**
     * This private method att an object to the end of the stack.
     * @param obj the object to be added.
     * @param newNode the node that the new node added after.
     */
    private void addToEnd(Object obj , Node<E> node){
        node.next = new Node<E>((E) obj, null);
    }

    /**
     * This method remove one node from the end of the stack.
     * @param previousNode the node that is will be last node.
     */
    private void removeTheLast(Node<E> previousNode){
        previousNode.next = null;
    }

    /**
     * @return the size of the stack
     */
    @Override
    public int size() {
        return this.size ;
    }

    /**
     * This function add an element to the top of the stack.
     *
     * @param obj the object to be added.
     * @return the object that is added.
     */
    @Override
    public Object push(Object obj) {

        if(size() == 0) {
            head = new Node<>((E) obj, null);
        } else{
            addToEnd( obj , getTheNode(size - 1));
        }
        size++;

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

        Node<E> temp = getTheNode(size() - 1);
        removeTheLast(getTheNode(size() - 2));
        size--;
        return temp;
    }
    /**
     * This function controls the stac is empty or not.
     *
     * @return true if stack is empty.
     */
    @Override
    public boolean isEmpty() {
        return size() == 0;
    }

    public String toString(){
        StringBuilder str = new StringBuilder();
        for (int i = 0 ; i < size() ; i++) {
            str.append(getTheNode(i).data);
            if (i != size() - 1)
                str.append(",");
        }
        return str.toString();
    }



}
