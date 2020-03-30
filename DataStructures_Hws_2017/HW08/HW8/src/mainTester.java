/**
 * Created by Burak Akten on 10/05/2017.
 */
public class mainTester {

    public static void main(String args[] ){
        /*String object is created*/
        //test2();

        /*Integer object is created*/
        test1();

    }

    /**
     * This method test the AVLTree with Integer type
     */
    public static void test1(){
        AVLTree<Integer> avl = new AVLTree<>();
        int x1 = 0  ;
        for (int i = 0; i < 26 ; i++) {
            Integer x = (int) ((Math.random() * 100) % 30);
            //System.out.printf("%d\n",x );
            avl.add(x);
            if(i == 3)
                x1 = x.intValue();
        }
        try {
            System.out.println("Traversing created random Avl tree as level-orderly! ");
            avl.traverse();
        } catch (Exception e) {
            e.printStackTrace();
        }

        //System.out.println("ssss : " +avl.delete(new Integer(x1)));
        System.out.println("/****************************************************************************/");
        try {
            System.out.println("Traversing random Avl tree after deleting a number as level-orderly! ");
            avl.traverse();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    /**
     * This method test the AVLTree with String type
     */
    public static void test2(){
        AVLTree<String> avl = new AVLTree<>();

        avl.add("Nush");
        avl.add("ile");
        avl.add("uslanmayani");
        avl.add("etmeli");
        avl.add("tekdir");
        avl.add("tekdir");
        avl.add("ile");
        avl.add("uslanmayanin");
        avl.add("hakki");
        avl.add("kötektir");


        try {
            System.out.println("Traversing created random Avl tree as level-orderly! ");
            avl.traverse();
        } catch (Exception e) {
            e.printStackTrace();
        }


    }


}
