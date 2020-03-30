import java.util.ArrayList;


/**
 * Created by Burak Akten on 15/05/2017.
 */
public class LeastSquaresPolynomial {




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
    public String LeastSquaresPoly(ArrayList<Coordinate> coords , int m){
        /* The x and y values are initializing from coordinates*/
        ArrayList<Double> x = new ArrayList<>(coords.size());
        ArrayList<Double> y = new ArrayList<>(coords.size());
        for (int i = 0; i < coords.size() ; i++){
            x.add(coords.get(i).x);
            y.add(coords.get(i).y);
        }

        GaussianElimination result  = new GaussianElimination();


        /*Then the x y array is copyint to a new array. */
        ArrayList<Double> row = new ArrayList<>();
        for(int k = 0 ; k <= m ; k++) {
            for (int i = 0; i <= m; i++) {
                double sum = 0;
                for (int j = 0; j < coords.size(); j++) {
                    sum += Math.pow(x.get(j), i + k);
                }
                row.add(sum);
            }
            double sum2 = 0;
            for(int i = 0 ; i<coords.size() ; i++){
                sum2 += y.get(i) * Math.pow(x.get(i) , k);
            }
            row.add(sum2);
            result.addToMatrix(row);
            row = new ArrayList<>();
        }

        ArrayList<Double> resultArray = result.getRes();

        return getPoly(resultArray);
    }

    private String getPoly( ArrayList<Double> coeff){
        StringBuilder str  = new StringBuilder();
        str.append("P(x) = ");

        str.append(coeff.get(coeff.size() - 1));
        str.append("+");
        int j = 1;
        for (int i = coeff.size() -2  ; i >=  0; i--, j++){
            str.append("(");
            str.append(coeff.get(i));
            str.append("*x^");
            str.append(j);
            str.append(")");
        }

        return str.toString();

    }



}
