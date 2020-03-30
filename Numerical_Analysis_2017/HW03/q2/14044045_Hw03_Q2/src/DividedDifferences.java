import java.util.ArrayList;

/**
 * Created by Burak Akten on 15/05/2017.
 */
public class DividedDifferences {

    /**
     * This inner class holds the coordinates
     */
    public static class Coordinate{

        /* The x value*/
        double x;
        /* The y value*/
        double y;

        public Coordinate(double x , double y){
            this.x = x;
            this.y = y;
        }
    }

    /**
     * This method find the divide differences polynomial according to the given coordinates
     * @param coords the coordinates
     * @return the representation of polynomial
     */
    public String DividedDifferencesPoly(ArrayList<Coordinate> coords){
        /* The x and y values are initializing from coordinates*/
        ArrayList<Double> x = new ArrayList<>(coords.size());
        ArrayList<Double> y = new ArrayList<>(coords.size());
        for (int i = 0; i < coords.size() ; i++){
            x.add(coords.get(i).x);
            y.add(coords.get(i).y);
        }
        /*Then the x y array is copyint to a new array. */
        ArrayList<Double> dividedDiff = new ArrayList<>();
        dividedDiff.addAll(y);

        /*then the divide differences array is created according to the algorithm*/
        for (int i = 1 ; i < x.size() ; i++){
            for (int j = x.size() -1  ; j > 0 ; j--){
                if(j - i >= 0) {
                    double denominator = (x.get(j) - x.get(j - i));
                    dividedDiff.set(j, (dividedDiff.get(j) - dividedDiff.get(j - 1)) / denominator);
                }
            }
        }
        return findThePolynomial(dividedDiff , x);
    }

    /**
     * This method is additional method for creating polynomial method.
     * @param dividedDiffrences The array for holding dividedDiffrences acccording to x and y values
     * @param x the x coordinate
     * @return the representation of polynomial
     */
    private String  findThePolynomial(ArrayList<Double> dividedDiffrences , ArrayList<Double> x){

        /* The string that holds the polynomial.*/
        StringBuilder str = new StringBuilder();

        str.append("P(x) = ");
        str.append(dividedDiffrences.get(0));
        str.append("+");

        /*creating the polynomial.*/
        for (int i = 1 ; i < dividedDiffrences.size() ; i++){
            str.append("[");
            str.append(dividedDiffrences.get(i));
            for (int j = 0 ; j < i ; j++){
                str.append("(x-");
                str.append(x.get(j));
                str.append(")");
            }
            str.append("]");
            if(i !=dividedDiffrences.size() - 1)
                str.append("+");
        }
        return str.toString();
    }
}
