import java.util.Iterator;
import java.util.LinkedList;
import java.util.Queue;


/** Class for a binary tree that stores type E objects.
 *   @author Koffman , Wolfgang , BurakAkten
 * */
public class BinaryTree <E extends Comparable < E >> implements Iterable<E>{

    /** Class to encapsulate a tree node. */
    protected static class Node <E> {
        // Data Fields
        /** The information stored in this node. */
        protected E data;

        /** Reference to the left child. */
        protected Node left;

        /** Reference to the right child. */
        protected Node < E > right;

        // Constructors

        /** Construct a node with given data and no children.
         @param data The data to store in this node
         */
        public Node(E data) {
            this.data = data;
            left = null;
            right = null;
        }

        // Methods
        /** Return a string representation of the node.
         @return A string representation of the data fields
         */
        public String toString() {
            return data.toString();
        }
    }

    //Data fields
    /** The root of the binary tree */
    protected Node < E > root;
    /** Return value from the public add method. */
    protected boolean addReturn;

    /**
     * This function add the element of the tree to a queue object as pre-order.
     * @param root the reference of a root to be added.
     * @param obj a queue object that the nodes are added.
     */
    private void fillQueuePreOrder(Node<E> root , Queue<E> obj) {
        if(root == null)
            return;
        else{
            /*adding current root's data to Queue object.*/
            obj.add(root.data);
            /*recursive part.*/
            fillQueuePreOrder(root.left , obj);
            fillQueuePreOrder(root.right , obj);
        }
    }

    /**
     * This method wrapper method for traversing the tree as pre-order.
     * @param root
     */
    private void traverse(Node<E> root ){
        /*This method is doing same thing what the fillQueuePreOrder does.
         * The only difference is this method prints out the current root on the console.
         */
        if(root == null)
            return;
        else{
            /*Printing out on the console.*/
            System.out.println(root.data);
            traverse(root.left);
            traverse(root.right);
        }
    }

    /** Recursive add method.
     post: The data field addReturn is set true if the item is added to
     the tree, false if the item is already in the tree.
     @param localRoot The local root of the subtree
     @param item The object to be inserted
     @return The new local root that now contains the
     inserted item
     */
    private Node < E > add(Node < E > localRoot, E item) {
        if (localRoot == null) {
            // item is not in the tree — insert it.
            addReturn = true;
            return new Node < E > (item);
        }
        else if (item.compareTo(localRoot.data) == 0) {
            // item is equal to localRoot.data
            addReturn = false;
            return localRoot;
        }
        else if (item.compareTo(localRoot.data) < 0) {
            // item is less than localRoot.data
            localRoot.left = add(localRoot.left, item);
            return localRoot;
        }
        else {
            // item is greater than localRoot.data
            localRoot.right = add(localRoot.right, item);
            return localRoot;
        }
    }

    protected BinaryTree(Node < E > root) {
        this.root = root;
    }

    public BinaryTree() {
        root = null;
    }

    /** Determine whether this tree is a leaf.
     *@param node a node to control if it is leaf or not
     *@return true if the root has no children
     */
    public boolean isLeaf(Node<E> node) {
        return (node.left == null && node.right == null);
    }

    /** Starter method add.
     pre: The object to insert must implement the
     Comparable interface.
     @param item The object being inserted
     @return true if the object is inserted, false
     if the object already exists in the tree
     */
    public boolean add(E item) {
        root = add(root, item);
        return addReturn;
    }

    /**
     * Returns an iterator over elements of type {@code T}.
     * This iterator traverse the tree as pre-order.
     * @return an Iterator.
     */
    @Override
    public Iterator<E> iterator() {
        /*
         * Holds the elements of tree.
         */
        Queue<E> myTree = new LinkedList<>();
        /*Controlling if the root is null or not.*/
        try {
            if(this.root == null)
                throw new Exception("Null Tree!");
            fillQueuePreOrder(this.root , myTree);
        } catch (Exception e) {
            System.out.printf("Exception caught : %s \n" , e.toString());
            System.exit(1);
        }

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
    /**
     * This method for traverse the tree and print out the data for each iteration.
     * @throws Exception if root is null
     */
    public void traverse() throws Exception {
        if(root == null)
            throw new Exception("Null Tree!");
        traverse(root);
    }
}
