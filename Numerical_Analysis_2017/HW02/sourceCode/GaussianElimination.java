import java.util.ArrayList;

/**
 * Created by Burak Akten on 07/04/2017.
 */
public class GaussianElimination {

    /**The system is in this member.*/
    private ArrayList<ArrayList<Double>> matrix ;
    /**Si is in this member i = 0,1,2..*/
    private ArrayList<Double> smax;
    /**Result is in this member.*/
    private ArrayList<Double> result;

    /**
     * This method find the solution from the result matrix.
     * @return false for error condition , true for no error.
     */
    private boolean findResult(){

        if(matrix.get(matrix.size() - 1).get(matrix.size() )!= 0 && matrix.get(matrix.size() - 1).get(matrix.size() - 1) == 0)
            return false; /*infinite Solution*/
        else if(matrix.get(matrix.size() - 1).get(matrix.size() )!= 0 && matrix.get(matrix.size() - 1).get(matrix.size() - 1) == 0)
            return false; /*No solution*/

        result = new ArrayList<>(matrix.size());

        result.add(matrix.get(matrix.size()- 1).get(matrix.size()) / matrix.get(matrix.size() - 1).get(matrix.size()- 1));

        for(int i = matrix.size() - 2 ; i >= 0 ; i--){
            double solution = matrix.get(i).get(matrix.size());
            int index = 0;
            for(int j = matrix.size() - 1 ; j >= i ; j--){
                if(j == i)
                    solution /= matrix.get(i).get(i);
                else
                    solution -= result.get(index++) * matrix.get(i).get(j);
            }
            result.add(solution);
        }
    return  true;
    }

    /**
     * This methot is finding the max number in an 1D array.
     * @param arr an array
     * @return the max value in array.
     */
    private double findMax(ArrayList<Double> arr){
        Double sMax = 0.0;
        for (int j = 0; j < arr.size() - 1; ++j)
            if (Math.abs(arr.get(j)) > sMax)
                sMax = Math.abs(arr.get(j));
        return sMax;
    }

    /**
     * This method swap to arrays(rows)
     * @param row1 First row
     * @param row2 Second row
     */
    private void swapRows(int row1 , int row2){
        ArrayList<Double> temp = new ArrayList<>(matrix.get(row1));
        matrix.get(row1).clear();
        matrix.get(row1).addAll(matrix.get(row2));
        matrix.get(row2).clear();
        matrix.get(row2).addAll(temp);
    }

    /**
     * This method fill the smax with the maximum numbers for each row.
     * @return
     */
    private boolean fillTheSmax(){

        for(int i = 0; i < matrix.size() ; i++) {
            if(findMax(matrix.get(i)) != 0)
                smax.add(findMax(matrix.get(i)));
            else
                return false;
        }
        return true;
    }

    /**
     * No parameter constructor. That is initializing member variables(matrix , smax).
     */
    public GaussianElimination(){
        matrix = new ArrayList<>();
        smax = new ArrayList<>();

    }

    /**
     * This method adding to the matrix the array.
     * @param strArray the array to be added the matrix.
     */
    public void addToMatrix(String [] strArray){
        ArrayList<Double> temp = new ArrayList<>();
        for(String  element : strArray)
            temp.add(Double.parseDouble(element));
        matrix.add(temp);
    }

    /**
     * This method is the main part for making GESP
     * @return true for success , false for unsuccess.
     * @throws Exception when the matrix is empty.
     */
    public boolean run()throws Exception{
        if(matrix.isEmpty())
            throw new Exception("There is no equations!");

        if(!this.fillTheSmax()){
            System.out.println("No unique solution for this system for GESP!");
            return false;
        }

        /*In tis part : the gaussian algorithm is working.*/
        for(int i = 0 ; i < this.matrix.size() - 1; i++){
            int k = i;
            Double max = Math.abs(matrix.get(i).get(i) / smax.get(i));

            for(int j = i ; j < this.matrix.size() ; j++){
                Double r = Math.abs(this.matrix.get(j).get(i) / smax.get(j));
                if(r > max) {
                    max = r;
                    k = j;
                }
            }
            if(i != k)
                swapRows(i, k);
            for (int j = i+1; j < this.matrix.size(); j++) {
                Double times = matrix.get(j).get(i) / matrix.get(i).get(i);
                ArrayList<Double> temp = new ArrayList<>();
                for (int c = i ; c < this.matrix.size() + 1; c++)
                    temp.add(matrix.get(j).get(c) - times * matrix.get(i).get(c));
                while(temp.size() < matrix.size() + 1)
                    temp.add(0 , 0.0);
                matrix.set(j, temp);
            }
        }
        /* Controlling the result.*/
        boolean result = findResult();
        if(!result) {
            System.out.println("No unique solution for this system for GESP!");
            return false;
        }
        return true;
    }

    /**
     * This method is overrided form the object class.
     * @return a string
     */
    public String toString(){
        StringBuilder str = new StringBuilder();
        str.append("Result for GESP->\n");
        str.append("[");
        for (int i = result.size() - 1 ; i >= 0 ; i--){
            str.append(result.get(i));
            if(i != 0)
                str.append(",");
        }
        str.append("]");
        return str.toString();
    }
}
