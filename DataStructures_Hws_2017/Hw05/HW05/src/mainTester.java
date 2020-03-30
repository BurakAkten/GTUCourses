import java.io.File;
import java.util.Iterator;
import java.util.Scanner;

/**
 * Created by Burak Akten on 04/04/2017.
 */
public class mainTester {

    /**
     * This method is making traverse.
     * @param iter An iterator object.
     * @param message A message to print out.
     */
    private static void  traverseWithIter(Iterator<Integer> iter , String message){
        System.out.println(message);
        while(iter.hasNext())
            System.out.println(iter.next());
        System.out.printf("------------------------------\n");
    }
    private static void  traverseWithIter2(Iterator<String> iter , String message){
        System.out.println(message);
        while(iter.hasNext())
            System.out.println(iter.next());
        System.out.printf("------------------------------\n");
    }

    public static void main(String[] args){

        try {
            FamilyTree<String> fTree = null;
            BinaryTree<Integer> bTree = new BinaryTree<>() ;
            BinarySearchTree<Integer> bSearchtree = new BinarySearchTree<>();

            Scanner scan =new Scanner(new File("test.txt"));
            /* *************************************************************/
            Scanner scan2 = new Scanner(new File("family.txt"));

            if(scan2.hasNextLine())
                fTree = new FamilyTree<>(scan2.nextLine());

            while(scan2.hasNextLine()){
                String[] next = scan2.nextLine().split(", ");
                fTree.add(next[0],next[1] , next[2]);
            }

            Iterator<String> iter3 = fTree.iterator();
            traverseWithIter2(iter3 , "Family Tree Test!!");

            /* *************************************************************/

            while(scan.hasNextInt()){
                Integer value = scan.nextInt();
                bTree.add(value);
                bSearchtree.add(value);
            }

            Iterator<Integer> iter = bTree.iterator();
            Iterator<Integer> iter2 = bSearchtree.levelOrderIterator();

            traverseWithIter(iter , "Binary Tree Test!!");
            traverseWithIter(iter2 , "Binary Search Tree Test!!");


            /*Hw06*/
            fTree.traverse();

        } catch (Exception e) {
            System.out.printf("Exception caught : %s \n" , e.toString());
            System.exit(1);
        }


    }




}
