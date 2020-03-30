import java.io.*;
import java.util.AbstractCollection;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.Queue;

/** Class for a binary tree that stores type E objects.
 *   @author Koffman and Wolfgang
 * */

public class BinaryTree < E extends Comparable > extends AbstractCollection<E>
        implements Serializable {

    /** Class to encapsulate a tree node. */
    protected static class Node < E >
            implements Serializable {
        // Data Fields
        /** The information stored in this node. */
        protected E data;

        /**Reference to the left child.*/
        protected Node<E> parent;

        /** Reference to the left child. */
        protected Node <E> left;

        /** Reference to the right child. */
        protected Node <E> right;


        // Constructors
        /** Construct a node with given data and no children.
         @param data The data to store in this node
         */
        public Node(E data) {
            this.data = data;
            left = null;
            right = null;
            parent = null;
        }
        public Node(E data , Node<E> prev){
            this.data = data;
            this.parent = prev;
            right = null;
            left = null;
        }
        public Node (Node<E> localroot){
            this.data = localroot.data;
            this.parent = localroot.parent;
            this.right = localroot.right;
            this.left = localroot.left;
        }

        // Methods
        /** Return a string representation of the node.
         @return A string representation of the data fields
         */
        public String toString() {
            return data.toString();
        }
    }

    // Data Field
    /** The root of the binary tree */
    protected Node < E > root;
    /** Return value from the public add method. */
    protected boolean addReturn;
    /**size of the Binary tree*/
    protected  int size;

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

    /** Perform a preorder traversal.
     @param node The local root
     @param depth The depth
     @param sb The string buffer to save the output
     */
    private void preOrderTraverse(Node < E > node, int depth,
                                  StringBuilder sb) {
        for (int i = 1; i < depth; i++) {
            sb.append("  ");
        }
        if (node == null) {
            sb.append("null\n");
        }
        else {
            sb.append(node.toString());
            sb.append("\n");
            preOrderTraverse(node.left, depth + 1, sb);
            preOrderTraverse(node.right, depth + 1, sb);
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

    public BinaryTree() {
        root = null;
    }


    @Override
    public int size() {
        return size;
    }

    protected BinaryTree(Node < E > root) {
        this.root = root;
    }

    /** Constructs a new binary tree with data in its root,leftTree
     as its left subtree and rightTree as its right subtree.
     */
    public BinaryTree(E data, BinaryTree < E > leftTree,
                      BinaryTree < E > rightTree) {
        root = new Node < E > (data);
        if (leftTree != null) {
            root.left = leftTree.root;
        }
        else {
            root.left = null;
        }
        if (rightTree != null) {
            root.right = rightTree.root;
        }
        else {
            root.right = null;
        }
    }

    /** Return the left subtree.
     @return The left subtree or null if either the root or
     the left subtree is null
     */
    public BinaryTree < E > getLeftSubtree() {
        if (root != null && root.left != null) {
            return new BinaryTree < E > (new Node<E>(root.left));
        }
        else {
            return null;
        }
    }

    /** Return the right sub-tree
     @return the right sub-tree or
     null if either the root or the
     right subtree is null.
     */
    public BinaryTree<E> getRightSubtree() {
        if (root != null && root.right != null) {
            return new BinaryTree<E>(new Node<E>(root.right));
        } else {
            return null;
        }
    }

    /**** BEGIN EXERCISE ****/
    /** Return the data field of the root
     @return the data field of the root
     or null if the root is null
     */
    public E getData() {
        if (root != null) {
            return root.data;
        } else {
            return null;
        }
    }
    /**** END EXERCISE ****/

    /** Determine whether this tree is a leaf.
     @return true if the root has no children
     */
    public boolean isLeaf() {
        return (root.left == null && root.right == null);
    }

    public String toString() {
        StringBuilder sb = new StringBuilder();
        preOrderTraverse(root, 1, sb);
        return sb.toString();
    }



    /** Method to read a binary tree.
     pre: The input consists of a preorder traversal
     of the binary tree. The line "null" indicates a null tree.
     @param bR The input file
     @return The binary tree
     @throws IOException If there is an input error
     */
    public static BinaryTree < String >
    readBinaryTree(BufferedReader bR) throws IOException {
        // Read a line and trim leading and trailing spaces.
        String data = bR.readLine().trim();
        if (data.equals("null")) {
            return null;
        }
        else {
            BinaryTree < String > leftTree = readBinaryTree(bR);
            BinaryTree < String > rightTree = readBinaryTree(bR);
            return new BinaryTree < String > (data, leftTree, rightTree);
        }
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
        size = addReturn == true ? ++size : size ;
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

}
