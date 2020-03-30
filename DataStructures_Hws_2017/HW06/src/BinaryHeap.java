import java.util.ArrayList;
import java.util.LinkedList;
import java.util.NoSuchElementException;
import java.util.Queue;

/**
 * Created by Burak Akten on 18/04/2017.
 */
public class BinaryHeap<E extends Comparable> extends BinaryTree<E> implements Queue<E> {

    /**
     * Return value from the public remove and poll method.
     */
    private boolean deletedReturn;

    /**
     * This method for sorting the heap after removing.
     */
    private void sortHeap(){

        boolean rightChild;
        Node<E> smallChild = null;
        Node<E> localRoot = root;
        E tempData = null;
        boolean flag = true;
        while(flag){
            if(localRoot.left != null && localRoot.right != null ) {
                rightChild = localRoot.left.data.compareTo(localRoot.right.data) < 0 ? false : true;
                smallChild = rightChild == true ? localRoot.right : localRoot.left;
            }
            else if(localRoot.left == null && localRoot.right != null ) {
                rightChild = true;
                smallChild = localRoot.right;
            }
            else if(localRoot.left != null && localRoot.right == null){
                rightChild = false;
                smallChild = localRoot.left;
            }else{
                flag = false;
                rightChild = false;
            }
            tempData = localRoot.data;

            if(rightChild && flag){
                localRoot.data = smallChild.data;
                smallChild.data = tempData;
                localRoot = localRoot.right;
            }
            else if (flag){
                localRoot.data = smallChild.data;
                smallChild.data = tempData;
                localRoot = localRoot.left;
            }
        }
    }

    /**
     * overrided form binary tree
     * @param localRoot the tree that be added
     * @param item this is the item to be added to the tree
     * @return Node reference
     */
    private Node<E> add(Node<E> localRoot , E item){

        if(localRoot == null){
            localRoot = new Node<E>(item , null);
            addReturn = true;
            return localRoot;
        }

        boolean flag = true;
        Node<E> tempRoot = localRoot;
        Node<E> addedNode = null;

        ArrayList<Node<E>> tempList = new ArrayList<>();
        /*adding first node to the tempQueue*/
        tempList.add(tempRoot);

        while(flag && !tempList.isEmpty()){

            if(tempRoot.left != null)
                tempList.add(tempRoot.left);
            else{
                addedNode = new Node<E>(item , tempRoot);
                tempRoot.left = addedNode ;
                addReturn = true;
                flag = false;
            }
            if(tempRoot.right != null && flag){
                tempList.add(tempRoot.right);
            }
            else if(flag && tempRoot.right == null){
                addedNode =  new Node<E>(item , tempRoot);
                tempRoot.right = addedNode;
                addReturn = true;
                flag = false;
            }
            if(flag){
                tempList.remove(0);
                tempRoot = tempList.get(0);
            }
        }
        /* Controlling for the right place for the added node*/
        while(!flag && addedNode.parent != null && item.compareTo(addedNode.parent.data) < 0){
            E temp = addedNode.parent.data ;
            addedNode.parent.data = item ;
            addedNode.data = temp;
            addedNode = addedNode.parent;
        }
        return localRoot;
    }

    /**
     * This method is a helper method for remove() and poll() methods
     * @param localRoot A Node reference
     * @return The data that returned
     */
    private E remove(Node<E> localRoot){

        if(localRoot == null){
            deletedReturn = false;
            return null;
        }

        /*The data that is removed*/
        E returnedData = localRoot.data;

        boolean flag = true;
        Node<E> tempRoot = localRoot;
        Node<E> newRoot = null;

        ArrayList<Node<E>> tempList = new ArrayList<>();
        /*adding first node to the tempQueue*/
        tempList.add(tempRoot);

        while(flag){
            if(tempRoot.right != null)
                tempList.add(tempRoot.right);
            else{
                if(tempRoot.left == null)
                    newRoot = tempList.get(tempList.size() - 1);
                else
                    newRoot = tempRoot.left;
                newRoot.parent.left = null;
                flag = false;
            }
            if(tempRoot.left != null && flag)
                tempList.add(tempRoot.left);
            else if (flag) {
                if(tempRoot.right == null)
                    newRoot = tempList.get(tempList.size() - 1);
                else
                    newRoot = tempRoot.right;
                newRoot.parent.right = null;
                flag = false;
            }
            tempList.remove(0);
            tempRoot = tempList.get(0);
        }

        localRoot.data = newRoot.data;

        deletedReturn = true;
        return returnedData;
    }

    /**
     * No parameter constructor.
     */
    public BinaryHeap(){super();}

    /**
     * This constructor initialize the root with the parameter
     * @param root to initialize the member root.
     */
    public BinaryHeap(Node<E> root ){super(root);}

    /**
     * Inserts the specified element into this queue if it is possible to do
     * so immediately without violating capacity restrictions.
     * When using a capacity-restricted queue, this method is generally
     * preferable to {@link #add}, which can fail to insert an element only
     * by throwing an exception.
     *
     * @param o the element to add
     * @return {@code true} if the element was added to this queue, else
     * {@code false}
     * @throws ClassCastException       if the class of the specified element
     *                                  prevents it from being added to this queue
     * @throws NullPointerException     if the specified element is null and
     *                                  this queue does not permit null elements
     * @throws IllegalArgumentException if some property of this element
     *                                  prevents it from being added to this queue
     */
    @Override
    public boolean offer(E o) {
        super.root = add(super.root , o);
        size = addReturn == true ? ++size : size ;
        return addReturn;
    }

    /**
     * Inserts the specified element into this queue if it is possible
     * @param o the element to add
     * @return {@code true} if the element was added to this queue, else {@code false}
     * @throws IllegalArgumentException if some property of this element prevents it from being added to this queue
     */
    @Override
    public boolean add(E o){
        if(offer(o))
            return true;
        else
            throw new IllegalArgumentException("Error on adding!");
    }

    /**
     * Retrieves and removes the head of this queue.  This method differs
     * from {@link #poll poll} only in that it throws an exception if this
     * queue is empty.
     *
     * @return the head of this queue
     * @throws NoSuchElementException if this queue is empty
     */
    @Override
    public E remove() {
        E deleted = poll();
        if (deleted == null)
            throw new NoSuchElementException();
        return deleted;
    }

    /**
     * Retrieves and removes the head of this queue,
     * or returns {@code null} if this queue is empty.
     *
     * @return the head of this queue, or {@code null} if this queue is empty
     */
    @Override
    public E poll() {
        E head = remove(super.root);
        size = deletedReturn == true ? --size : size ;
        sortHeap();
        return head;
    }

    /**
     * Retrieves, but does not remove, the head of this queue.  This method
     * differs from {@link #peek peek} only in that it throws an exception
     * if this queue is empty.
     *
     * @return the head of this queue
     //* @throws NoSuchElementException if this queue is empty
     */
    @Override
    public E element() {
        E returned = this.peek();
        if(returned == null)
            throw new NoSuchElementException();
        return returned;

    }

    /**
     * Retrieves, but does not remove, the head of this queue,
     * or returns {@code null} if this queue is empty.
     *
     * @return the head of this queue, or {@code null} if this queue is empty
     */
    @Override
    public E peek() {

        if(super.root == null)
            return null;
        return super.root.data;
    }


    /* **********This part of the code is written by Burak Akten for Question 3 ************* */
    /* **********                  Traversing level order                       ************* */

    /**
     * This metdoh wrapper method for traverse method. For each traversed is printed out on screen.
     * @param root the root of the tree.
     */
    private void traverse(Node<E> root){
        /*This method is doing same thing what the fillQueuelevelOrder does.
         * The only difference is this method prints out the current root on the console.
         */
        /*TempQueue for holds the tree entries temporary.*/
        LinkedList<Node<E>> tempArray = new LinkedList<>();
        /*Temporary root.*/
        Node<E> tempRoot = root;
        /*adding first node to the tempQueue*/
        tempArray.add(tempRoot);

        System.out.printf("Level order traversing!\n");

        while(!tempArray.isEmpty()){
            System.out.println(tempArray.get(0).data);
            if(tempRoot.left != null)
                tempArray.add(tempRoot.left);
            if (tempRoot.right != null)
                tempArray.add(tempRoot.right);
            tempArray.removeFirst();
            tempRoot = tempArray.peekFirst();
        }
    }
    /**
     * This method traverse the tree as level order and prints out the current root's data on the console.
      * @throws Exception When the tree is null then throw an exception.
     */
    public void traverse() throws Exception {
        if(super.root == null)
            throw new Exception("Null Tree!");
        traverse(super.root);
    }

    /* ***************************************************************************** */



}
