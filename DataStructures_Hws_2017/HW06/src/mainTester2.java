import java.io.File;
import java.util.ArrayList;
import java.util.Scanner;

/**
 * Created by Burak Akten on 18/04/2017.
 */
public class mainTester2 {

    static final String FILE_NAME = "freq.txt";
    public static void main(String[] args){

        HuffmanTree obj = new HuffmanTree();
        try {
            Scanner input = new Scanner(new File(FILE_NAME));
            ArrayList<String> allData = new ArrayList<>();

            while(input.hasNextLine())
                allData.add(input.nextLine());

            HuffmanTree.HuffData[] data = new HuffmanTree.HuffData[allData.size()];
            for(int i = 0  ; i < allData.size() ; i++ ){

                char character = allData.get(i).charAt(0);
                String freqStr = allData.get(i).substring(2 , allData.get(i).length());
                data[i] = new HuffmanTree.HuffData(Double.parseDouble(freqStr) , character);
            }

            obj.buildTree(data);
            System.out.println("1=>");
            System.out.println(obj.encode("easy boy easy"));
            System.out.println(obj.decode("01010100011100011111100000100110001111101010100011100011"));
            System.out.println("2=>");
            System.out.println(obj.encode("burak"));
            System.out.println(obj.decode("100000000010010101011000011"));
            System.out.println("3=>");
            System.out.println(obj.encode("selamunaleykum "));
            System.out.println(obj.decode("00110101011010101100100000101111010101100101000111100001100001110010111"));

        }catch (Exception e){
            System.err.printf("Exception caught => %s \n",e.toString());
            System.exit(1);
        }
    }
}
