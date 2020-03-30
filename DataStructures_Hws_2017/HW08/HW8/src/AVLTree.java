import java.util.LinkedList;
import java.util.Queue;

/**
 * Self-balancing binary search tree using the algorithm defined
 * by Adelson-Velskii and Landis.
 * @author Koffman and Wolfgang and Burak Akten
 */
public class AVLTree<E extends Comparable<E>>
        extends BinarySearchTreeWithRotate<E> {

    /** Class to represent an AVL Node. It extends the
     * BinaryTree.Node by adding the balance field.
     */
    private static class AVLNode<E> extends Node<E> {

        /** Constant to indicate left-heavy */
        public static final int LEFT_HEAVY = -1;
        /** Constant to indicate balanced */
        public static final int BALANCED = 0;
        /** Constant to indicate right-heavy */
        public static final int RIGHT_HEAVY = 1;
        /** balance is right subtree height - left subtree height */
        private int balance;

        // Methods
        /**
         * Construct a node with the given item as the data field.
         * @param item The data field
         */
        public AVLNode(E item) {
            super(item);
            balance = BALANCED;
        }

        /**
         * Return a string representation of this object.
         * The balance value is appended to the contents.
         * @return String representation of this object
         */
        @Override
        public String toString() {
            return balance + ": " + super.toString();
        }
    }
    // Data Fields
    /** Flag to indicate that height of tree has increased. */
    private boolean increase;
    /** Flag to indicate that height of tree has decreased. */
    private boolean decrease;

// Insert solution to programming project 5, chapter -1 here

    // Methods

    /** Starter method add.
     pre: The object to insert must implement the
     Comparable interface.
     @param item The object being inserted
     @return true if the object is inserted, false
     if the object already exists in the tree
     */
    @Override
    public boolean add(E item) {
        increase = false;
        root = add((AVLNode<E>) root, item);
        return addReturn;
    }
    /**
     * Recursive add method. Inserts the given object into the tree.
     * @post addReturn is set true if the item is inserted,
     *       false if the item is already in the tree.
     * @param localRoot The local root of the subtree
     * @param item The object to be inserted
     * @return The new local root of the subtree with the item
     *         inserted
     */
    private AVLNode<E> add(AVLNode<E> localRoot, E item) {
        if (localRoot == null) {
            addReturn = true;
            increase = true;
            return new AVLNode<E>(item);
        }
        if (item.compareTo(localRoot.data) == 0) {
            // Item is already in the tree.
            increase = false;
            addReturn = false;
            return localRoot;
        } else if (item.compareTo(localRoot.data) < 0) {
            // item < data
            localRoot.left = add((AVLNode<E>) localRoot.left, item);

            if (increase) {
                decrementBalance(localRoot);
                if (localRoot.balance < AVLNode.LEFT_HEAVY) {
                    increase = false;
                    return rebalanceLeft(localRoot);
                }
            }
            return localRoot; // Rebalance not needed.
        } else { // item > data
        // Insert solution to programming exercise 2, section 2, chapter 9 here
            localRoot.right = add((AVLNode<E>) localRoot.right, item);
            if(increase){
                incrementBalance(localRoot);
                if(localRoot.balance > AVLNode.RIGHT_HEAVY)
                    return rebalanceRight(localRoot);
                else
                    return localRoot;
            }
            return  localRoot;
        }
    }

    /*<listing chapter="9" number="3">*/
    /**
     * Method to rebalance left.
     * @pre localRoot is the root of an AVL subtree that is
     *      critically left-heavy.
     * @post Balance is restored.
     * @param localRoot Root of the AVL subtree
     *        that needs rebalancing
     * @return a new localRoot
     */
    private AVLNode<E> rebalanceLeft(AVLNode<E> localRoot) {
        // Obtain reference to left child.
        AVLNode<E> leftChild = (AVLNode<E>) localRoot.left;
        // See whether left-right heavy.
        if (leftChild.balance > AVLNode.BALANCED) {
            // Obtain reference to left-right child.
            AVLNode<E> leftRightChild = (AVLNode<E>) leftChild.right;
            // Adjust the balances to be their new values after
            // the rotations are performed.
            if (leftRightChild.balance < AVLNode.BALANCED) {
                leftChild.balance = AVLNode.LEFT_HEAVY;
                leftRightChild.balance = AVLNode.BALANCED;
                localRoot.balance = AVLNode.BALANCED;
            } else if (leftRightChild.balance > AVLNode.BALANCED) {
                leftChild.balance = AVLNode.BALANCED;
                leftRightChild.balance = AVLNode.BALANCED;
                localRoot.balance = AVLNode.RIGHT_HEAVY;
            } else {
                leftChild.balance = AVLNode.BALANCED;
                localRoot.balance = AVLNode.BALANCED;
            }
            // Perform left rotation.
            localRoot.left = rotateLeft(leftChild);
        } else { //Left-Left case
            // In this case the leftChild (the new root)
            // and the root (new right child) will both be balanced
            // after the rotation.
            leftChild.balance = AVLNode.BALANCED;
            localRoot.balance = AVLNode.BALANCED;
        }
        // Now rotate the local root right.
        return (AVLNode<E>) rotateRight(localRoot);
    }
    /**
     * Method to rebalance right.
     * @pre localRoot is the root of an AVL subtree that is
     *      critically right-heavy.
     * @post Balance is restored.
     * @param localRoot Root of the AVL subtree
     *        that needs rebalancing
     * @return a new localRoot
     */
    private AVLNode < E > rebalanceRight(AVLNode < E > localRoot){
        //Reference of the right child of the localRoot
        AVLNode<E> rightCh = (AVLNode<E>) localRoot.right;
        //before the rotation sets te balance of the references
        if(rightCh.balance < AVLNode.BALANCED){
            //Reference of the left child of right child of the localRoot
            AVLNode<E> rightLeftCh = (AVLNode<E>) rightCh.left;

            if(rightLeftCh.balance == AVLNode.BALANCED){
                rightLeftCh.balance = AVLNode.BALANCED;
                localRoot.balance = AVLNode.BALANCED;
                rightCh.balance = AVLNode.BALANCED;
            }
            else if (rightLeftCh.balance < AVLNode.BALANCED){
                rightLeftCh.balance = AVLNode.BALANCED;
                localRoot.balance = AVLNode.BALANCED;
                rightCh.balance = AVLNode.RIGHT_HEAVY;
            }
            else if (rightLeftCh.balance > AVLNode.BALANCED){
                rightLeftCh.balance = AVLNode.BALANCED;
                localRoot.balance = AVLNode.LEFT_HEAVY;
                rightCh.balance = AVLNode.BALANCED;
            }
            localRoot.right = rotateRight(rightCh);
            return (AVLNode < E > ) rotateLeft(localRoot);
        }
        else{
            rightCh.balance = AVLNode.BALANCED;
            localRoot.balance = AVLNode.BALANCED;

            return (AVLNode < E > ) rotateLeft(localRoot);
        }
    }

// Insert solution to programming exercise 1, section 2, chapter 9 here

    /**
     * Method to decrement the balance field and to reset the value of
     * increase.
     * @pre The balance field was correct prior to an insertion [or
     *      removal,] and an item is either been added to the left[
     *      or removed from the right].
     * @post The balance is decremented and the increase flags is set
     *       to false if the overall height of this subtree has not
     *       changed.
     * @param node The AVL node whose balance is to be decremented
     */
    private void decrementBalance(AVLNode<E> node) {
        // Decrement the balance.
        node.balance--;
        if (node.balance == AVLNode.BALANCED) {
            // If now balanced, overall height has not increased.
            increase = false;
            decrease = true;
        }
        else{
            decrease = false;
        }
    }
    /**
     * Method to increment the balance field and to reset the value of
     * increase and decrease.
     * @param node The AVL node whose balance is to be incremented
     */
    private void incrementBalance(AVLNode<E> node){
        //increment balance
        node.balance++;
        if (node.balance <= AVLNode.BALANCED){
            increase = false;
            decrease = true;
        }
        else{
            increase = true;
            decrease = false;
        }
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
        decrease = false;
        root = delete((AVLNode<E>)root, target);
        return deleteReturn;
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
    private AVLNode < E > delete(AVLNode < E > localRoot, E item) {
        if (localRoot == null) {
            // item is not in the tree.
            deleteReturn = null;
            return localRoot;
        }

        // Search for item to delete.
        int compResult = item.compareTo(localRoot.data);
        if (compResult < 0) {
            // item is smaller than localRoot.data.
            localRoot.left = delete((AVLNode < E >)localRoot.left, item);

            if(decrease){
                incrementBalance(localRoot);
                if((localRoot).balance > AVLNode.RIGHT_HEAVY)
                    return rebalanceRight(localRoot);
                else
                    return localRoot;
            }
            return localRoot;
        }
        else if (compResult > 0) {
            // item is larger than localRoot.data.
            localRoot.right = delete((AVLNode < E >)localRoot.right, item);
            if(decrease){
                decrementBalance(localRoot);
                if((localRoot).balance < AVLNode.LEFT_HEAVY)
                    return rebalanceLeft(localRoot);
                else
                    return localRoot;
            }
            return localRoot;
        }
        else {
            // item is at local root.
            deleteReturn = localRoot.data;
            if (localRoot.left == null) {
                // If there is no left child, return right child
                // which can also be null.
                return (AVLNode < E >) localRoot.right;
            }
            else if (localRoot.right == null) {
                // If there is no right child, return left child.
                return (AVLNode < E >) localRoot.left;
            }
            else {
                // Node being deleted has 2 children, replace the data
                // with inorder predecessor.
                if (localRoot.left.right == null) {
                    // The left child has no right child.
                    // Replace the data with the data in the
                    // left child.
                    localRoot.data = localRoot.left.data;
                    // Replace the left child with its left child.
                    localRoot.left = localRoot.left.left;
                    return localRoot;
                }
                else {
                    // Search for the inorder predecessor (ip) and
                    // replace deleted node’s data with ip.
                    localRoot.data = findLargestChild((AVLNode < E >)localRoot.left);
                    return localRoot;
                }
            }
        }
    }
    /** Find the node that is the
     inorder predecessor and replace it
     with its left child (if any).
     post: The inorder predecessor is removed from the tree.
     @param parent The parent of possible inorder
     predecessor (ip)
     @return The data in the ip
     */
    private E findLargestChild(AVLNode < E > parent) {
        // If the right child has no right child, it is
        // the inorder predecessor.
        if (parent.right.right == null) {
            E returnValue = parent.right.data;
            parent.right = parent.right.left;
            // We removed the node from the right side so we have to decrement the balance of parent.
            decrementBalance(parent);
            return returnValue;
        }
        else {
            E largestData = findLargestChild(((AVLNode<E>)parent.right));
            //After finding and removing the node with largest data , we have to control the new balance of it.
            if(((AVLNode<E>)parent.right).balance < AVLNode.LEFT_HEAVY )
                parent.right = rebalanceLeft(((AVLNode<E>)parent.right));
            //Then it is still decrease , then decrement the balance
            if(decrease)
                decrementBalance(parent);
            return largestData;
        }
    }
    /**
     * This method traverse the tree as level order and prints out the current root's data on the console.
     * @throws Exception when the root is null
     */
    public void traverse() throws Exception {
        if(super.root == null)
            throw new Exception("Null Tree!");
        traverse(super.root);
    }

    /**
     * This method wrapper method for traverse method.
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
}
