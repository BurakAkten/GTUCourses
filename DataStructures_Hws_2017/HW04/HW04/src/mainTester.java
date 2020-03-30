import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;
import static java.lang.Double.parseDouble;
import static java.lang.Integer.parseInt;


/**
 * Created by Burak Akten on 21/03/2017.
 */
public class mainTester {

    /**
     * The file name of the input file.
     */
    private static final String FILE_NAME = "test.csv";
    /**
     * The file name of the output file.
     */
    private static final String OUTPUT_FILE = "testResult_1.csv";

    public static void main(String[] args) {

        StackA<Integer> intStack = new StackA<>();
        StackA<Double> doubleStack = new StackA<>();
        StackA<String> stringStack = new StackA<>();
        StackA<Character> charStack = new StackA<>();
        StackB<Integer> intStack2 = new StackB<>();
        StackB<Double> doubleStack2 = new StackB<>();
        StackB<String> stringStack2 = new StackB<>();
        StackB<Character> charStack2 = new StackB<>();
        StackC<Integer> intStack3 = new StackC<>();
        StackC<Double> doubleStack3 = new StackC<>();
        StackC<String> stringStack3 = new StackC<>();
        StackC<Character> charStack3 = new StackC<>();
        StackD<Integer> intStack4 = new StackD<>();
        StackD<Double> doubleStack4 = new StackD<>();
        StackD<String> stringStack4 = new StackD<>();
        StackD<Character> charStack4 = new StackD<>();


        try (Scanner input = new Scanner(new File(FILE_NAME))) {


            while (input.hasNextLine()) {
                String line = input.nextLine();
                String[] arr1 = line.split(",");

                Scanner controlType = new Scanner(arr1[0]);
                if(controlType.hasNextInt()){
                    for (int i = 0; i < arr1.length; i++) {
                        intStack.push(parseInt(arr1[i]));
                        intStack2.push(parseInt(arr1[i]));
                        intStack3.push(parseInt(arr1[i]));
                        intStack4.push(parseInt(arr1[i]));
                    }
                }
                else if(controlType.hasNextDouble()){
                    for (int i = 0; i < arr1.length; i++) {
                        doubleStack.push(parseDouble(arr1[i]));
                        doubleStack2.push(parseDouble(arr1[i]));
                        doubleStack3.push(parseDouble(arr1[i]));
                        doubleStack4.push(parseDouble(arr1[i]));
                    }
                }
                else if(controlType.hasNext() && arr1[0].length() > 1){
                    for (int i = 0; i < arr1.length; i++) {
                        stringStack.push(arr1[i]);
                        stringStack2.push(arr1[i]);
                        stringStack3.push(arr1[i]);
                        stringStack4.push(arr1[i]);
                    }
                }
                else{
                    for (int i = 0; i < arr1.length; i++) {
                        charStack.push(arr1[i]);
                        charStack2.push(arr1[i]);
                        charStack3.push(arr1[i]);
                        charStack4.push(arr1[i]);
                    }
                }
            }

            FileWriter output = new FileWriter(OUTPUT_FILE );

            writeToFile(intStack , output);
            writeToFile(intStack2 , output);
            writeToFile(intStack3 , output);
            writeToFile(intStack4 , output);
            writeToFile(doubleStack , output);
            writeToFile(doubleStack2 ,output);
            writeToFile(doubleStack3 , output);
            writeToFile(doubleStack4 , output);
            writeToFile(charStack , output);
            writeToFile(charStack2 , output);
            writeToFile(charStack3 , output);
            writeToFile(charStack4 , output);
            writeToFile(stringStack ,output);
            writeToFile(stringStack2 , output);
            writeToFile(stringStack3 , output);
            writeToFile(stringStack4  ,output);

            output.close();

        } catch (Exception e) {
            System.err.printf("Exception caught ! : %s \n" , e.toString());
            System.exit(1);
        }
    }

    /**
     * This static method write the stack into a file.
     * @param stack the stack to be written to file.
     * @param output The output file object.
     * @throws IOException for any error when writing to the file.
     */
    public static void writeToFile(StackInterface stack , FileWriter output) throws IOException {

        StringBuilder outputStr = new StringBuilder();

        outputStr.append(stack.size());
        outputStr.append(",");
        outputStr.append(stack.toString());
        outputStr.append("\n");

        output.write(outputStr.toString());

    }

}
