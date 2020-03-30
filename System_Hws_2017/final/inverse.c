#include "inverse.h"

double determinantOfMat(double **matrix , Matrix size){
	/*the result*/
	double determinant = 0.0;
	/*for the smaller matrix that is for calling the recursive matrix.*/
	double **smallMatrix;
	/*Counter.*/
	int i , j , k , l;
	Matrix newSize;
	/*Two base case condition*/
	if(size.row == 1 && size.col == 1)
		determinant += matrix[0][0];
	else if(size.row * size.col == 4)
		determinant += matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
	else{	

		/*The ecursive part is working here.*/
		for(i = 0 ; i < size.col ; i++){	
			
			/*tking place from the memory for the small matrix*/
			smallMatrix = (double**)malloc(sizeof(double*) * size.row - 1 );
	    	for (k = 0; k < size.row; ++k)
	    		smallMatrix[k] = (double*)malloc(sizeof(double) * size.col -1 );

	    	/*Then the matrix is making small*/
	    	for (j = 1; j < size.row ; ++j){
	    		for(l = 0; l < size.col ; l++){
	    			if(l > i)
	    				smallMatrix[j - 1][l - 1] = matrix[j][l];
	    			else
	    				smallMatrix[j - 1][l] = matrix[j][l];
	    		}
	    	}
	    	newSize.row = size.row -1;
	    	newSize.col = size.col - 1;
	    	/*calculating the determinant recursivly*/
	    	determinant += matrix[0][i] * pow(-1 , i) * determinantOfMat(smallMatrix , newSize);
		    /*free the memory*/
	    	for (i = 0; i < size.row; ++i)
	    		free(smallMatrix[i]);
	    	free(smallMatrix);

	    }
	}
	return determinant;
}

void findinverse(double** matrix , double** inverse , Matrix size){

	int i , j , k ;
	double x , y;

	/*Creating I matrix*/
	for(i = 0 ; i < size.row ; i++){
		for(j = 0 ; j < size.col ; j++){
			if(i != j)
				inverse[i][j] = 0;
			else
				inverse[i][j] = 1;
		}
	}
	
	/*Start to make matrix I then we have inverse matrix*/
	for (i = 0; i < size.row; ++i){
		x = matrix[i][i];
		for (j = 0; j < size.col; ++j){
			matrix[i][j] = matrix[i][j] / x;
			inverse[i][j] = inverse[i][j] / x;
		}

		for(k = 0 ; k < size.row ; k++){
			if(k != i ){
				y = matrix[k][i];
				for(j = 0 ; j < size.col ; j++){
					matrix[k][j] = matrix[k][j] - (matrix[i][j] * y);
					inverse[k][j] = inverse[k][j] - (inverse[i][j] * y);
				}
			}
		}
	}
}

Matrix Tranpose(double** matris , double** matrisT , Matrix size){
	 int i = 0, j = 0;
	 Matrix newSize;
	 newSize.row = size.col;
	 newSize.col = size.row;

	 for(i=0; i<size.row; i++)
        for(j=0; j<size.col; j++)
            matrisT[j][i] = matris[i][j];
    return newSize;
}

Matrix matrixMultip(double** matris1 , double** matrix2  , double** result, Matrix size1 , Matrix size2){
	int i = 0  , j = 0 ,k = 0; 
	Matrix resultS;
	resultS.row = size1.row;
	resultS.col = size2.col;

	for(i = 0; i < size1.row ; i++){
		for(j = 0 ; j < size2.col ; j++){
			result[i][j] = 0;
			for(k = 0; k < size2.row ; k++){
				result[i][j] += matris1[i][k] * matrix2[k][j];
			}
		}
	}
	return resultS;
}


void print_matrix2(double **m , Matrix size) {
	int i = 0 , j = 0;
    

	for(i=0; i<size.row; i++){
        for(j=0; j<size.col; j++)
            printf("%f\t", m[i][j]);
        printf("\n");
	}
}