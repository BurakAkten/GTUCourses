import java.util.Random;

/**
 * Created by Burak Akten on 14/05/2017.
 */
public class Main {

    public static void main(String[] args){

        Integer[][] arr = new Integer[10][10];
        Random random = new Random();
        ImageInterpolation zoom = new ImageInterpolation();

        for(int i = 0 ; i < 10 ; i++ )
            for (int j = 0 ; j < 10 ; j++)
                arr[i][j] =random.nextInt(30) + 1;

        printArr(arr);

        try {
            System.out.printf("Zoomed matrix according to Nearest Neigbor Strategy and when z = 2!\n");
           printArr(zoom.makeZoom(arr , 2 , "NEAREST"));
        } catch (Exception e) {
            e.printStackTrace();
        }

    }

    private static void printArr(Integer[][] arr){
        System.out.println("**************************************************");
        for (int j = 0 ; j < arr.length ; j++){
            for (Integer i : arr[j]) {
                System.out.print(i);
                System.out.print("\t");
            }
            System.out.println();
        }
    }
}
