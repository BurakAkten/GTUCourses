/**
 * Created by Burak Akten on 14/05/2017.
 */
public class ImageInterpolation {

    private static String BICUBIC = "BICUBIC";
    private static String NEARESTNEIG = "NEAREST";
    private static String BILINEAR = "BILINEAR";

    private static int WEIGHT = 10;
    private static int HEIGHT = 10;


    /**
     * This method control the matrix is positive or not.
     * @param image the image matrix
     * @return true if the matrix is positive
     * @throws Exception when matrix size is not 10.
     */
    private boolean pozitiveMat(Integer image[][]) throws Exception {
        if(image.length != HEIGHT)
            throw new Exception("The size of the matrix is not 10!");

        for(int i = 0 ; i < HEIGHT ; i++ )
            for (int j = 0 ; j < WEIGHT ; j++)
                if(image[i][j] <= 0)
                    return false;

        return true;
    }

    private Integer[][] bicubicZoom(Integer image[][], int zoom){
        return null;
    }

    /**
     * This method making zoom according to the NearestNeigbor strategy
     * @param image the matrix
     * @param zoom the zoom value
     * @return the zoomed matrix
     */
    private Integer[][] nearestNeigborZoom(Integer image[][], int zoom ){
        /* creating the matrix to be returned*/
        Integer returnedMat[][] = new Integer[HEIGHT * zoom][WEIGHT * zoom];
        /*The new weight*/
        int newW = WEIGHT * zoom ;
        /*The new HEIGHT*/
        int newH = HEIGHT * zoom;

        /*The index of the new matrix*/
        double indexX , indexY;
        /* the ratio of weight and height*/
        double rate_x = (double)HEIGHT / (double)newW;
        double rate_y = (double)WEIGHT / (double)newH;

        /*Then the algorithm is applied then the zoomed matrix calculated*/
        for(int i = 0 ; i < newH ; i++){
            for(int j = 0; j < newW ; j++){
                indexX = Math.floor(j * rate_x);
                indexY = Math.floor(i * rate_y);
                returnedMat[i][j] = image[(int)((indexY + WEIGHT)% HEIGHT)][(int)indexX];
            }
        }
        return returnedMat;
    }

    private Integer[][] bilinearZoom(Integer image[][], int zoom ){
        return null;
    }


    /**
     * This method make zoom according to the strategy and zoom factor.
     * @param image the matrix to be zoomed
     * @param zoom the zoom value.
     * @param strategy The strategy to be applied when zoom is making. (strategies : BICUBIC , NEAREST , BILINEAR )
     * @return the zoomed matrix
     * @throws Exception when matrix is non-positive , and zoom < 1.
     */
    public Integer[][] makeZoom(Integer image[][], int zoom  , String strategy) throws Exception {

        if(!pozitiveMat(image))
            throw new Exception("Non-Positive matrix!");

        if (zoom < 1)
            throw new Exception("The value of the zoom must be greater than 1!");

        if(strategy.compareTo(BICUBIC) == 0)
            return bicubicZoom(image ,  zoom);
        else if(strategy.compareTo(NEARESTNEIG) == 0)
            return nearestNeigborZoom(image ,  zoom );
        else if(strategy.compareTo(BILINEAR) == 0)
            return bilinearZoom(image ,  zoom );
        else
            throw new Exception("Unknown strategy for zooming!");
    }
}

