import java.util.Queue;

/**
 * Created by Burak Akten on 23/03/2017.
 */

/**
 *
 * @param <E> generic type
 */
public class myQueue<E> extends  KWLinkedList {

    /**
     * This method wrapper function for reverseQueue
     * @param obj the object that will be reversed
     * @param tempArr an array that holds object elements
     * @param size the size of the object
     * @return reversed object or null if size == 0
     */
    private Queue<E> reverseQueue(Queue<E> obj , E[] tempArr,  int size){

        if(size == 0)
            return null;
        else if(size == 1){
            obj.add(tempArr[0]);
            return obj;
        }
        else{
            obj.add(tempArr[size - 1]);
            return reverseQueue(obj , tempArr , size -1);
        }
    }

    /**
     * This method reverses a queue.
     * @param obj the queue object that will be reversed.
     * @return the reversed object or null if size == 0;
     */
    public Queue<E> reverseQueue(Queue<E> obj){
        E[] tempArr = (E[]) obj.toArray();
        obj.clear();
        return reverseQueue(obj , tempArr , tempArr.length);
    }
}
