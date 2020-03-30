#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/wait.h>
#include <math.h>

typedef struct{
	int row;
	int col;
}Matrix;


/*
*This function find the inverse of a matrix.
*it is referenced a little from 
*http://bilgisayarkavramlari.sadievrenseker.com/2012/05/01/matrisin-determinanti-matrix-determinant/
*/
void findinverse(double** matrix , double** inverse , Matrix size);
/*
*This function calculate the determinant of a matrix
*it is referenced a little from 
*http://bilgisayarkavramlari.sadievrenseker.com/2012/05/01/matrisin-determinanti-matrix-determinant/ 
*/
double determinantOfMat(double **matrix , Matrix size);

Matrix Tranpose(double** matris , double** matrisT , Matrix size);

/*https://www.tarikbahar.com/iki-matrisin-carpimini-bulan-c-kodu/*/
Matrix matrixMultip(double** matris1 , double** matrix2  , double** result, Matrix size1 , Matrix size2);

void print_matrix2(double **m , Matrix size);