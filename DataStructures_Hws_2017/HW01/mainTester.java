import java.io.IOException;
import java.util.Scanner;

/**
 * This mainTester class for testing other classes.
 * @author Burak Akten
 */
public class mainTester {
    /**
     * holds the choice of staff.
     */
    private static Integer staffChoice;
    /**
     * holds the choice of user.
     */
    private static Integer userChoice;
    
    /**
     * @param args 
     */
    public static void main(String[] args) {
        /**
         * Holds the command line argument.
         */
        String choice;
        /**
         * This object for taking input from user.
         */
        Scanner input = new Scanner(System.in);
        System.out.print("Please Enter =>\n1 to log in as a staff\n2 to log in as a user.\n=>");
        
        choice = input.nextLine();
        int choiceAsInt;
        try{
            choiceAsInt = Integer.parseInt(choice);
            if(choiceAsInt != 2 && choiceAsInt != 1){
                System.err.println("You entered incompatible input.!");
                return ;
            }
        }catch(NumberFormatException e){
            System.err.println("You entered incompatible input.!");
            return;
                    
        }

        
        /*According to choice , calling staffPart or userPart functions.*/
        try{
            switch (choiceAsInt) {
                case 1:
                    staffPart();
                    break;
                case 2:
                    userPart();
                    break;
                default:
                    break;
            }
        }catch(Error e){
            System.err.printf("%s\n" , e.toString());
        }
    }
    /**
     * This function for make staff mission(addbook , removebook , registernewuser).
     */
    public static void staffPart(){  
        /**
         * This object for taking input from user.
         */
        Scanner input = new Scanner(System.in);
        System.out.println("You logged in this system as Staff.\n");
        /**
         * Staff object for make staff parts.
         */
        Staff staff;
        try {
            staff = new Staff();
        } catch (IOException ex) {
            throw new Error("IOException caught!");
        }
        /*Controling he/she is staff or not.*/
        if(!staff.isStaff()){
            System.out.println("You're not staff!");
            return;
        }
        
        System.out.println("Please make your choice according to these =>\n");
        System.out.printf("1 for Adding new book.\n2 for Removing book.\n3 for Registering new library user.\n");
        
        System.out.printf("Enter your choice : ");
        /*Here asking for staff choice.*/
        if(input.hasNextInt()){
            staffChoice = input.nextInt();    
            staff.run(staffChoice);
        }
        else
            throw new Error("Wrong Choice for Staff part!"); 
    }
    /**
     * This function for make user mission(borrowbook , returnbook).
     */
    public static void userPart(){
        /**
         * Staff object for make staff parts.
         */
        Scanner input = new Scanner(System.in);
    
        System.out.println("You logged in this system as Library User.\n");
        System.out.println("Please enter your name and your ID number.");
        
        /**
         * User object for making user part.
         */
        Users user = new Users();
        
        /*Asking user name and ID*/
        System.out.printf("User Name: ");
        user.setUserName(input.nextLine().toLowerCase());
        System.out.printf("User ID : ");
        user.setUserID(input.nextLine().toLowerCase());
        
        /*If this is user then she/he can make his/her staff.*/
        if(user.checkUser() != -1){        
            System.out.println("\nPlease make your choice according to these =>\n");
            System.out.printf("1 for Borrowing new book.\n2 for Returning book.\n");

            System.out.printf("Enter your choice : ");
            if(input.hasNextInt()){
                userChoice = input.nextInt();
                user.run(userChoice);
            }
            else
                throw new Error("Wrong Choice for User part!");     
        }else{
            System.out.println("You are not user of the library! You have to register.");
        }
    }
}
