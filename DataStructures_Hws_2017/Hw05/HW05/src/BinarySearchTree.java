import java.util.Iterator;
import java.util.LinkedList;
import java.util.Queue;

/** A class to represent a binary search tree.
 *  @author Koffman ,  Wolfgang and BurakAkten
 */
public class BinarySearchTree<E extends Comparable<E>> extends BinaryTree {

    // Data Fields
    /** Return value from the public delete method. */
    protected E deleteReturn;

    //Methods
    /** Recursive find method.
     @param localRoot The local subtree’s root
     @param target The object being sought
     @return The object, if found, otherwise null
     */
    private E find(Node < E > localRoot, E target) {
        if (localRoot == null)
            return null;
        // Compare the target with the data field at the root.
        int compResult = target.compareTo(localRoot.data);
        if (compResult == 0)
            return localRoot.data;
        else if (compResult < 0)
            return (E) find(localRoot.left, target);
        else
            return find(localRoot.right, target);
    }

    /** Find the node that is the
     inorder predecessor and replace it
     with its left child (if any).
     post: The inorder predecessor is removed from the tree.
     @param parent The parent of possible inorder
     predecessor (ip)
     @return The data in the ip
     */
    private E findLargestChild(Node < E > parent) {
        // If the right child has no right child, it is
        // the inorder predecessor.
        if (parent.right.right == null) {
            E returnValue = parent.right.data;
            parent.right = parent.right.left;
            return returnValue;
        }
        else {
            return findLargestChild(parent.right);
        }
    }

    /** Recursive delete method.
     post: The item is not in the tree;
     deleteReturn is equal to the deleted item
     as it was stored in the tree or null
     if the item was not found.
     @param localRoot The root of the current subtree
     @param item The item to be deleted
     @return The modified local root that does not contain
     the item
     */
    private Node < E > delete(Node < E > localRoot, E item) {
        if (localRoot == null) {
            // item is not in the tree.
            deleteReturn = null;
            return localRoot;
        }

        // Search for item to delete.
        int compResult = item.compareTo(localRoot.data);
        if (compResult < 0) {
            // item is smaller than localRoot.data.
            localRoot.left = delete(localRoot.left, item);
            return localRoot;
        }
        else if (compResult > 0) {
            // item is larger than localRoot.data.
            localRoot.right = delete(localRoot.right, item);
            return localRoot;
        }
        else {
            // item is at local root.
            deleteReturn = localRoot.data;
            if (localRoot.left == null) {
                // If there is no left child, return right child
                // which can also be null.
                return localRoot.right;
            }
            else if (localRoot.right == null) {
                // If there is no right child, return left child.
                return localRoot.left;
            }
            else {
                // Node being deleted has 2 children, replace the data
                // with inorder predecessor.
                if (localRoot.left.right == null) {
                    // The left child has no right child.
                    // Replace the data with the data in the
                    // left child.
                    localRoot.data = (E) localRoot.left.data;
                    // Replace the left child with its left child.
                    localRoot.left = localRoot.left.left;
                    return localRoot;
                }
                else {
                    // Search for the inorder predecessor (ip) and
                    // replace deleted node’s data with ip.
                    localRoot.data = (E) findLargestChild(localRoot.left);
                    return localRoot;
                }
            }
        }
    }

    /**
     * This metdoh wrapper method for traverse method.
     * @param root the root of the tree.
     */
    private void traverse(Node<E> root){
        /*This method is doing same thing what the fillQueuelevelOrder does.
         * The only difference is this method prints out the current root on the console.
         */
        /*TempQueue for holds the tree entries temporary.*/
        Queue<Node<E>> tempQueue = new LinkedList<>();
        /*Temporary root.*/
        Node<E> tempRoot = root;
        /*adding first node to the tempQueue*/
        tempQueue.add(tempRoot);

        while(!tempQueue.isEmpty()){
            System.out.println(tempQueue.peek().data);
            if(tempRoot.left != null)
                tempQueue.add(tempRoot.left);
            if (tempRoot.right != null)
                tempQueue.add(tempRoot.right);
            tempQueue.poll();
            tempRoot = tempQueue.peek();
        }
    }

    /**
     * This function add the element of the tree to a queue object as level-order.
     * @param root the reference of a root to be added.
     * @param obj a queue object that the nodes are added.
     */
    private void fillQueuelevelOrder(Node<E> root , Queue<E> obj){

        if(root == null)
            return;
        /*TempQueue for holds the tree entries temporary.*/
        Queue<Node<E>> tempQueue = new LinkedList<>();
        /*Temporary root.*/
        Node<E> tempRoot = root;
        /*adding first node to the tempQueue*/
        tempQueue.add(tempRoot);

        while(!tempQueue.isEmpty()){
            /*In this loop , The entries of the tree added to the queue as level-order */
            /*Firstly , the element of the tempQueue is added to obj from top.*/
            obj.add(tempQueue.peek().data);
            /*Then the right and left of the tempRoot is added to the tempQueue.*/
            if(tempRoot.left != null)
                tempQueue.add(tempRoot.left);
            if (tempRoot.right != null)
                tempQueue.add(tempRoot.right);
            /*Lastly  , removing an element of the tempQueue is deleted*/
            tempQueue.poll();
            /*Updated the tempRoot.*/
            tempRoot = tempQueue.peek();
        }
    }
    /**
     * This method traverse the tree as level order and prints out the current root's data on the console.
     */
    public void traverse() throws Exception {
        if(super.root == null)
            throw new Exception("Null Tree!");
        traverse(super.root);
    }
    /** Starter method find.
     pre: The target object must implement
     the Comparable interface.
     @param target The Comparable object being sought
     @return The object, if found, otherwise null
     */
    public E find(E target) {
        return (E) find(root, target);
    }

    /** Starter method delete.
     post: The object is not in the tree.
     @param target The object to be deleted
     @return The object deleted from the tree
     or null if the object was not in the tree
     @throws ClassCastException if target does not implement
     Comparable
     */
    public E delete(E target) {
        root = delete(root, target);
        return deleteReturn;
    }

    /**
     * Returns an iterator over elements of type E.
     *
     * @return an Iterator.
     */
    public Iterator<E> levelOrderIterator() throws Exception {
        /*
         * Holds the elements of tree.
         */
        Queue<E> myTree = new LinkedList<>();
        /*Controlling if the root is null or not.*/
        if(super.root == null)
            throw new Exception("Null Tree!");
        /*Filling the queue.*/
        fillQueuelevelOrder(super.root , myTree);

        /*The iterator part.*/
        Iterator<E> iterator = new Iterator<E>() {
            @Override
            public boolean hasNext() {
                if(!myTree.isEmpty())
                    return true;
                else
                    return false;
            }
            @Override
            public E next() {
                if(myTree.isEmpty()) try {
                    throw new Exception("No Next element in tree!!");
                } catch (Exception e) {
                    System.out.printf("Exception caught : %s \n" , e.toString());
                    System.exit(1);
                }
                return myTree.poll();
            }
        };
        return iterator;
    }

}
