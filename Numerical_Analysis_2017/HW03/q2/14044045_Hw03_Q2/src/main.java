import java.util.ArrayList;

/**
 * Created by Burak Akten on 15/05/2017.
 */
public class main {

    public static void main(String[] args){

        ArrayList<DividedDifferences.Coordinate> coordinates = new ArrayList<>();

        coordinates.add(new DividedDifferences.Coordinate(1.0 , 0.7651977));
        coordinates.add(new DividedDifferences.Coordinate(1.3 , 0.6200860));
        coordinates.add(new DividedDifferences.Coordinate(1.6 , 0.4554022));
        coordinates.add(new DividedDifferences.Coordinate(1.9 , 0.2818186));
        coordinates.add(new DividedDifferences.Coordinate(2.2 , 0.1103623));

        DividedDifferences poly = new DividedDifferences();


        System.out.println(poly .DividedDifferencesPoly(coordinates));



    }
}
