import java.util.ArrayList;

/**
 * Created by Burak Akten on 08/04/2017.
 */
public class Jacobi {

    /**The system is in this member.*/
    private ArrayList<ArrayList<Double>> matrix ;
    /**Result is in this member.*/
    private ArrayList<Double> result;
    /**Static variable holds the tolerance value*/
    private static final double TOL = 0.001;

    /**
     * No parameter constructor. That is initializing member variables(matrix , smax).
     */
    public Jacobi(){
        matrix = new ArrayList<>();
        result = new ArrayList<>();
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
     * This method is the main part for making JCB
     * @return true for success , false for unsuccess.
     * @throws Exception when the matrix is empty.
     */
    public boolean run() throws  Exception{

        /*This is for control the loop. */
        boolean flag = true;
        /* The maximum iteration number*/
        int max_iter = 100;
        /*temporary result for each x value.*/
        double result ;
        /*Temporary arraylist for xi i = 1,2,3,4...*/
        ArrayList<Double> tempResult = new ArrayList<>(matrix.size());

        if(matrix.isEmpty())
            throw new Exception("There is no equations!");

        /*the first values of Xi are initiliazing as 0.*/
        for (int i = 0 ; i < matrix.size() ; i++)
            tempResult.add(0.0);
        int k;
        /*Main part of the JCB*/
        for(k = 0 ; k < max_iter && flag ; k++) {
            for (int i = 0; i < matrix.size(); i++) {
                result = matrix.get(i).get(matrix.size()) / matrix.get(i).get(i);
                for (int j = 0; j < matrix.size(); j++)
                    if (i != j)
                        result += (-1)*(matrix.get(i).get(j) * tempResult.get(j)) / matrix.get(i).get(i);
                this.result.add(result);
            }
            /*Controlling for tolerance.*/
            if(Math.abs(this.result.get(0) - tempResult.get(0)) / Math.abs(this.result.get(0)) < TOL ){
                flag = false;
            }else{
                tempResult.clear();
                tempResult.addAll(this.result);
                this.result.clear();
            }
        }
        if(k >= max_iter && flag) {
            System.out.printf("The number of iteration is over %d iterations(the maximum number for JCB!)\n" , max_iter);
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
        str.append("Result for JCB ->\n");
        str.append("[");
        for (int i = 0; i < result.size() ; i++){
            str.append(result.get(i));
            if(i != result.size() - 1)
                str.append(",");
        }
        str.append("]");
        return str.toString();
    }
}
