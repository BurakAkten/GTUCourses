import java.util.LinkedList;
import java.util.Queue;

/**
 * Created by Burak Akten on 06/04/2017.
 * This class for representing family as Arabic Culture.
 */
public class FamilyTree<E extends Comparable<E>> extends BinaryTree<E> {

    Node<E> parent = null;
    /**
     * This method for finding the root that has the name.
     * @param localRoot The local subtree’s root
     * @param name the name of the target person
     * @return the node that its data ie equal to the name.
     */
    private  Node<E> findNode(Node<E> localRoot , E name ){
        if (localRoot == null)
            return new Node<E>(null);

        Node<E> tempRoot = localRoot;

        int compResult = name.compareTo(tempRoot.data);
        if(compResult == 0)
            return tempRoot;
        else {
            Node<E> left = findNode(tempRoot.left, name);
            Node<E> right = findNode(tempRoot.right, name);

            if(left == null && right == null)
                return null;
            compResult = name.compareTo(left.data);
            if(compResult == 0) {
                parent = tempRoot;
                return left;
            }
            compResult = name.compareTo(right.data);
            if(compResult == 0) {
                parent = tempRoot;
                return right;
            }
            return new Node<E>(null);
        }
    }


    /**
     *No parameter constructor , calls super class constructor.
     */
    public FamilyTree(){
        super();
    }

    /**
     * The constructor builds a person’s family. The person is root.
     * @param PersonName The name of the person.
     */
    public FamilyTree(String PersonName){
        super(new Node(PersonName));

    }

    /**
     * The method adds a new persont to the tree.
     * @param nameOfPerson the person that will be added.
     * @param parentName the person's parent's name
     * @param parentNickname the person's parent's nickname
     * @return true if adding is successfull , otherwise false.
     */
    public boolean add(String nameOfPerson , String parentName , String parentNickname){
        if(nameOfPerson == null || parentName == null || parentNickname == null)
            return false;
        if(super.isLeaf(super.root)){
            super.root.left = new Node<>(nameOfPerson);
            return true;
        }

        Node<E> findingNode = findNode(super.root , (E) parentName);
        if(findingNode.left == null){
            findingNode.left = new Node<>(nameOfPerson);
            return true;

        }else{
            Node temp = findingNode.left;
            while(temp.right!=null)
                temp = temp.right;
            temp.right = new Node<>(nameOfPerson);

        }

        return true;
    }


    /*Hw06*/
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
        }    }


    public void traverse(){
        traverse(super.root);
    }

}
