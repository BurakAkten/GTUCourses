#include <stdio.h>
#include <string.h>

/*
 *This function read the file byte by byte. İf this function find
 *the target in the file then print out this on the screen.
 *@param input the file pointer of the file.
 *@param target the word for seraching in the file.
 *@param the size of target.
 *@return the total occurences of the target in the file.
 */
int readCharbyChar(FILE* input , char* target , int targetSize);

/**
 *This structure for the collumn and row number when target is found.
 */
typedef struct {
    int col;
    int row;
}foundPlace;

int main(int argc , char* argv[]){

    /*File fointer for read file.*/
    FILE* input;
    /*total : total occurences of the target in file.*/
    int targetSize , total ;    
    
    /*Controlling for command line arguments. İf this format is wrong then error message
     *is printed out.
     */
    if(argc != 3){  	
   		fprintf(stderr, "Usage: %s targetString filename\n", argv[0]);
		return -1;
    }
    /*Calculating the size of target.*/
    targetSize  = strlen(argv[1]);

    /*Controoling the file is exist or not.*/
    if((input = fopen(argv[2] , "r")) == NULL){
        fprintf(stderr , "File is not exist!\n");
        return -1;
    }
    
    /*Reading file.*/
    total = readCharbyChar(input , argv[1] , targetSize);

    printf("Total %d  '%s' found.\n" , total , argv[1]);
    
    /*Closing file.*/
    fclose(input);

    return  0;
}

int readCharbyChar(FILE* input , char* target , int targetSize){

    /*The character that is read from file.*/
    char character;
    /*For controlling the reading*/
    int col = 1,     currentRow = 1 , foundByte = 0 ,newline = 0 ;
    /*for controlling loops*/
    int flag = 1, flag2 = 1 ;
    /*counter*/
    int count = 0 , i = 1;
    /*The place that target is found.*/
    foundPlace found;

    /*This loop read byte by byte the file till end of file. */
    for(character=fgetc(input); character != EOF && flag2 ;character=fgetc(input),col++){     
        /*control that the first character and the character that is read are same 
         *if they are then keep going to read.
         */
        if(character == target[0]){   
            /*initilazing the found place */       
            found.col = col;
            found.row = currentRow;
            foundByte = ftell(input) - 1;
            /*initilazing the control variable.*/
            flag = 1;
            i=1;
            /*In this while loop , the file still is reading but the space and tab ignored. And
             * when newline character is read then row updated(+1)
             */
            while(target[i] != '\0' && flag && character != EOF){
                   
                character = fgetc(input);
                col++;

                if(character == target[i])
                    i++;
                else if(character == ' ' || character == '\t' || character == '\n')
                {}
                else if (character != target[i]){
                    flag = 0;
                }
                    
                if(i >= targetSize){
                    printf("[%d , %d] konumunda ilk karakter bulundu.\n",found.row,found.col);
                    count++;
                }
            }
            /*going back to the found place from the file. and updating the column.*/
            fseek(input ,foundByte + 1, SEEK_SET);
            col = found.col ;
        }
        else if (character == '\n'){
        	newline += 1;
            col = 0;
        }
        else if (character == EOF){
            flag2 = 0;
        }

        /*row is updated.*/
        if(newline != 0){
            currentRow += newline ;
            newline = 0;
        }
    }

    return count;
}
