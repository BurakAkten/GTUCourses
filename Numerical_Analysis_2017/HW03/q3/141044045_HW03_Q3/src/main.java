import java.util.ArrayList;

/**
 * Created by Burak Akten on 15/05/2017.
 */
public class main {

    public static void main(String[] args){
        ArrayList<LeastSquaresPolynomial.Coordinate> coordinates = new ArrayList<>();

        coordinates.add(new LeastSquaresPolynomial.Coordinate(0 , 1.0));
        coordinates.add(new LeastSquaresPolynomial.Coordinate(0.25 , 1.284));
        coordinates.add(new LeastSquaresPolynomial.Coordinate(0.5 , 1.6487));
        coordinates.add(new LeastSquaresPolynomial.Coordinate(0.75 , 2.117));
        coordinates.add(new LeastSquaresPolynomial.Coordinate(1.0 , 2.7183));

        LeastSquaresPolynomial poly = new LeastSquaresPolynomial();

        System.out.println(poly .LeastSquaresPoly(coordinates , 2));


    }
}
