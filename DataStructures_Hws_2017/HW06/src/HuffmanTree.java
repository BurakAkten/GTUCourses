import java.util.*;
import java.io.*;

/** Class to represent and build a Huffman tree.
 *   @author Koffman and Wolfgang and Burak AKTEN
 * */

public class HuffmanTree
        implements Serializable {

    // Nested Classes
    /** A datum in the Huffman tree. */
    public static class HuffData
            implements Serializable, Comparable {
        // Data Fields
        /** The weight or probability assigned to this HuffData. */
        private double weight;

        /** The alphabet symbol if this is a leaf. */
        private Character symbol;

        public HuffData(double weight, Character symbol) {
            this.weight = weight;
            this.symbol = symbol;
        }

        /**
         * Compares this object with the specified object for order.  Returns a
         * negative integer, zero, or a positive integer as this object is less
         * than, equal to, or greater than the specified object.
         * <p>
         * <p>The implementor must ensure <tt>sgn(x.compareTo(y)) ==
         * -sgn(y.compareTo(x))</tt> for all <tt>x</tt> and <tt>y</tt>.  (This
         * implies that <tt>x.compareTo(y)</tt> must throw an exception iff
         * <tt>y.compareTo(x)</tt> throws an exception.)
         * <p>
         * <p>The implementor must also ensure that the relation is transitive:
         * <tt>(x.compareTo(y)&gt;0 &amp;&amp; y.compareTo(z)&gt;0)</tt> implies
         * <tt>x.compareTo(z)&gt;0</tt>.
         * <p>
         * <p>Finally, the implementor must ensure that <tt>x.compareTo(y)==0</tt>
         * implies that <tt>sgn(x.compareTo(z)) == sgn(y.compareTo(z))</tt>, for
         * all <tt>z</tt>.
         * <p>
         * <p>It is strongly recommended, but <i>not</i> strictly required that
         * <tt>(x.compareTo(y)==0) == (x.equals(y))</tt>.  Generally speaking, any
         * class that implements the <tt>Comparable</tt> interface and violates
         * this condition should clearly indicate this fact.  The recommended
         * language is "Note: this class has a natural ordering that is
         * inconsistent with equals."
         * <p>
         * <p>In the foregoing description, the notation
         * <tt>sgn(</tt><i>expression</i><tt>)</tt> designates the mathematical
         * <i>signum</i> function, which is defined to return one of <tt>-1</tt>,
         * <tt>0</tt>, or <tt>1</tt> according to whether the value of
         * <i>expression</i> is negative, zero or positive.
         *
         * @param o the object to be compared.
         * @return a negative integer, zero, or a positive integer as this object
         * is less than, equal to, or greater than the specified object.
         * @throws NullPointerException if the specified object is null
         * @throws ClassCastException   if the specified object's type prevents it
         *                              from being compared to this object.
         */
        @Override
        public int compareTo(Object o) {
            return 0;
        }
    }

    // Data Fields
    /** A reference to the completed Huffman tree. */
    private BinaryTree < HuffData > huffTree;

    /** A Comparator for Huffman trees; nested class. */
    private static class CompareHuffmanTrees
            implements Comparator < BinaryTree < HuffData >> {
        /** Compare two objects.
         @param treeLeft The left-hand object
         @param treeRight The right-hand object
         @return -1 if left less than right,
         0 if left equals right,
         and +1 if left greater than right
         */
        public int compare(BinaryTree < HuffData > treeLeft,
                           BinaryTree < HuffData > treeRight) {
            double wLeft = treeLeft.getData().weight;
            double wRight = treeRight.getData().weight;
            return Double.compare(wLeft, wRight);
        }
    }

    /** Builds the Huffman tree using the given alphabet and weights.
     post:  huffTree contains a reference to the Huffman tree.
     @param symbols An array of HuffData objects
     */
    public void buildTree(HuffData[] symbols) {
        Queue < BinaryTree < HuffData >> theQueue = new PriorityQueue < BinaryTree < HuffData >>
                (symbols.length, new CompareHuffmanTrees());
        // Load the queue with the leaves.
        for (HuffData nextSymbol : symbols) {
            BinaryTree < HuffData > aBinaryTree =
                    new BinaryTree < HuffData > (nextSymbol, null, null);
            theQueue.offer(aBinaryTree);
        }

        // Build the tree.
        while (theQueue.size() > 1) {
            BinaryTree < HuffData > left = theQueue.poll();
            BinaryTree < HuffData > right = theQueue.poll();
            double wl = left.getData().weight;
            double wr = right.getData().weight;
            HuffData sum = new HuffData(wl + wr, null);
            BinaryTree < HuffData > newTree =
                    new BinaryTree < HuffData > (sum, left, right);
            theQueue.offer(newTree);
        }

        // The queue should now contain only one item.
        huffTree = theQueue.poll();
    }

    /** Outputs the resulting code.
     @param out A PrintStream to write the output to
     @param code The code up to this node
     @param tree The current node in the tree
     */
    private void printCode(PrintStream out, String code,
                           BinaryTree < HuffData > tree) {
        HuffData theData = tree.getData();
        if (theData.symbol != null) {
            if (theData.symbol.equals(" ")) {
                out.println("space: " + code);
            }
            else {
                out.println(theData.symbol + ": " + code);
            }
        }
        else {
            printCode(out, code + "0", tree.getLeftSubtree());
            printCode(out, code + "1", tree.getRightSubtree());
        }
    }

    /** Method to decode a message that is input as a string of
     digit characters '0' and '1'.
     @param codedMessage The input message as a String of
     zeros and ones.
     @return The decoded message as a String
     */
    public String decode(String codedMessage) {
        StringBuilder result = new StringBuilder();
        BinaryTree < HuffData > currentTree = huffTree;
        for (int i = 0; i < codedMessage.length(); i++) {
            if (codedMessage.charAt(i) == '1') {
                currentTree = currentTree.getRightSubtree();
            }
            else {
                currentTree = currentTree.getLeftSubtree();
            }
            if (currentTree.isLeaf()) {
                HuffData theData = currentTree.getData();
                result.append(theData.symbol);
                currentTree = huffTree;
            }
        }
        return result.toString();
    }

    /* **********This part of the code is written by Burak Akten************* */
    /**
     * This method encodes the message with 1s and 0s.
     * @param message the message that is encoded
     * @return the encoded as string
     * @throws Exception when tree is null and the message cannot be encoded.
     */
    public String encode(String message) throws Exception {
        /*The output as encoded.*/
        StringBuilder code = new StringBuilder();
        if(this.huffTree == null)
            throw new Exception("This message can't be encoded. Because the tree wasn't initialized!");
        for(int i = 0; i < message.length() ; i++){
           Boolean returnValue = encode(message.charAt(i) , this.huffTree , code);
           if(!returnValue)
               throw new Exception("This message is not suitable for encoding!");
        }
        return code.toString();
    }

    /**
     * This method helper method for the other encode method.
     * @param character A character to be encoded.
     * @param tree the binary tree that has the character.
     * @param code the output parameter that includes the code.
     * @return true when the encoding is successful.
     */
    private Boolean encode(Character character , BinaryTree<HuffData> tree , StringBuilder code){

        /*Controlling the tree is leaf or not*/
        if(tree.isLeaf()){
            if(tree.getData().symbol.equals(character))
                return true;
            else{
                //code.deleteCharAt(code.length() - 1);
                return false;
            }
        }
        /*return value for controlling the coding*/
        boolean returned;
        returned = encode(character, tree.getLeftSubtree() , code.append("0"));
        if(!returned) {
            code.deleteCharAt(code.length() - 1);
            returned = encode(character, tree.getRightSubtree(), code.append("1"));
            if(!returned)
                code.deleteCharAt(code.length() - 1);
        }
        return returned;
    }
    /* ************************************************************************ */
}
