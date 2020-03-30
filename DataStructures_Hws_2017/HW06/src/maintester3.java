
/**
 * Created by Burak Akten on 21/04/2017. For testing level order traverse.
 */
public class maintester3 {

    /**
     * Main method.
     * @param args Command line parameter.
        */
public static void main(String[] args){

        BinaryHeap<Integer> heap  = new BinaryHeap<>();
        heap.offer(6);
        heap.offer(18);
        heap.offer(29);
        heap.offer(20);
        heap.offer(28);
        heap.offer(39);
        heap.offer(66);
        heap.offer(37);
        heap.offer(26);
        heap.offer(76);
        heap.offer(32);
        heap.offer(74);
        heap.offer(89);
        heap.offer(8);
        heap.remove();

        System.out.println("*********************************************");
        System.out.println("BinaryHeap is filled with these [6,18,29,20,28,339,66,37,26,76,32,74,89,8]");
        System.out.println("The traverse method is working  level-orderly...");
        try {
            heap.traverse();
        } catch (Exception e) {
            e.printStackTrace();
        }

    }
}
