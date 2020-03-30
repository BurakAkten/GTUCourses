import java.io.File;
import java.util.Scanner;

/**
 * Created by Burak Akten on 07/04/2017.
 */
public class solver {

    public static void main(String[] args) {

        if(args.length != 4){
            System.out.printf("Usage : java solver -i <input file name> -m <method>\n");
            System.exit(1);
        }
        try{
            Scanner input = new Scanner(new File(args[1]));

            if(args[3].equals("GESP")){
                GaussianElimination obj = new GaussianElimination();
                while(input.hasNextLine()){
                    String line = input.nextLine();
                    obj.addToMatrix(line.split(","));
                }
                if(obj.run())
                    System.out.println(obj.toString());
                else
                    System.exit(1);
            }
            else {
                Jacobi obj2 = new Jacobi();
                while (input.hasNextLine()) {
                    String line = input.nextLine();
                    obj2.addToMatrix(line.split(","));
                }
                if (obj2.run())
                    System.out.println(obj2.toString());
                else {
                    System.exit(1);
                }
            }
        }catch (Exception e){
            e.printStackTrace();
        }
    }
}
