import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Scanner;

import static java.lang.Double.parseDouble;
import static java.lang.Integer.parseInt;

/**
 * Created by Burak Akten on 23/03/2017.
 */
public class maintester2 {
    /**
     * Name of the output file
     */
    private static final String OUTPUT_FILE2 = "testResult_2.csv";
    /**
     * Name of the input file
     */
    private static final String INPUT_FILE = "test.csv";


    public static  void main (String[] args){
        /*This queues for holding values that are Integer , String ,...*/
        Queue<Integer> intQueue = new LinkedList<>();
        Queue<Double> doubleQueue = new LinkedList<>();
        Queue<String> stringQueue = new LinkedList<>();
        Queue<Character> charQueue = new LinkedList<>();

        /*This myQueues for reversing the Queues.*/
        myQueue<Integer> myObj1 = new myQueue<>();
        myQueue<Double> myObj2 = new myQueue<>();
        myQueue<String> myObj3 = new myQueue<>();
        myQueue<Character> myObj4 = new myQueue<>();

        /*Opening the input file. */
        try (Scanner input = new Scanner(new File(INPUT_FILE))) {

            /*file is being read till end of the file.*/
            while (input.hasNextLine()) {
                String line = input.nextLine();
                /*Splitting the lines by ',' */
                String[] arr1 = line.split(",");

                /*Controlling the types and adding to the Queues*/
                Scanner controlType = new Scanner(arr1[0]);
                if(controlType.hasNextInt()) {
                    for (int i = 0; i < arr1.length; i++)
                        intQueue.add(parseInt(arr1[i]));
                    if(myObj1.reverseQueue(intQueue) == null){
                        System.err.printf("No element in the Integer queue! Reverse Faild!!");
                        System.exit(0);
                    }
                }
                else if(controlType.hasNextDouble()) {
                    for (int i = 0; i < arr1.length; i++)
                        doubleQueue.add(parseDouble(arr1[i]));
                    if(myObj2.reverseQueue(doubleQueue) == null){
                        System.err.printf("No element in the Double queue! Reverse Faild!!");
                        System.exit(0);
                    }
                }
                else if(controlType.hasNext() && arr1[0].length() > 1) {
                    for (int i = 0; i < arr1.length; i++)
                        stringQueue.add(arr1[i]);
                    if(myObj3.reverseQueue(stringQueue) == null){
                        System.err.printf("No element in the String queue! Reverse Faild!!");
                        System.exit(0);
                    }
                }
                else{
                    for (int i = 0; i < arr1.length; i++)
                        charQueue.add(arr1[i].charAt(0));
                    if(myObj4.reverseQueue(charQueue) == null){
                        System.err.printf("No element in the Character queue! Reverse Faild!!");
                        System.exit(0);
                    }
                }
            }

            /*Opening the output file*/
            FileWriter output = new FileWriter(OUTPUT_FILE2);
            /*Cllaing the method thet writes the file.*/
            writeToFile(stringQueue, output);
            writeToFile(charQueue, output);
            writeToFile(doubleQueue , output);
            writeToFile(intQueue , output);

            output.close();

        } catch (Exception e) {
            System.err.printf("Exception caught ! : %s \n" , e.toString());
            System.exit(1);
        }
    }
    /**
     * This static method write the stack into a file.
     * @param queue the stack to be written to file.
     * @param output The output file object.
     * @throws IOException for any error when writing to the file.
     */
    public static void writeToFile(Queue queue , FileWriter output) throws IOException {

        StringBuilder outputStr = new StringBuilder();

        Iterator iter = queue.iterator();

        int i = 0;
        while(iter.hasNext()) {
            outputStr.append(iter.next());
            if(i != queue.size() - 1)
                outputStr.append(",");
            i++;
        }
        outputStr.append("\n");

        output.write(outputStr.toString());

    }
}
