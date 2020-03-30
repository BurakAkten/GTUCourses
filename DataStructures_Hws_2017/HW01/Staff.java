import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.lang.Error;
import java.util.Scanner;
/**
 * 
 * @author Burak Akten
 */
public class Staff extends LibrarySystem{
    
    /**
     * This variable holds the name of the file that contains staff password.
     */
    private final String FILEOFSTAFF = "staff.csv";
    /**
     * this variable holds staff password.
     */
    private String passwordOfStaff ;
    /**
     * if this is true then the system user is staff.
     */
    private boolean isStaff = true;
    /**
     * By using this function , staff can add book.
     * @throws Error when inner function throws any error.
     */
    private void addBook()throws Error{
        /*
         * By using this function name of book and author of book can be set.
         */
        setter();
        /**
         * this variable holds the book and author name to write the book file.
         */
        String line = getBookName() +","+ getAuthorName();
        super.writeLine(line,FILEOFBOOKS , true);
        System.out.println("You have added a book!");
    }
    /**
     * This function remove book from the file(library).
     * @throws Error when inner function throws any error.
     */
    private void removeBook()throws Error{
        /*
         * Book file is read to array.
         */
        readFiletoArray(FILEOFBOOKS);
        /*
         *By using this function name of book and author of book can be set.
         */
        setter();
        /**
         * this variable holds the book and author name to remove the book file.
         */
        String line = super.getBookName() + "," + super.getAuthorName();
        /**
         * this variable holds the index of the line if it exist , If doesn't exist then it value will be -1.
         */
        int foundwhere = search(line);
        
        if( foundwhere == -1)
            System.out.println("Sorry! This book is't in the library to remove!");
        else{
            super.fileArray.remove(foundwhere);      
            super.writeLine(fileArray.get(0) , FILEOFBOOKS , false);
            for(int i = 1 ; i < fileArray.size() ; ++i)
                super.writeLine(fileArray.get(i) , FILEOFBOOKS , true);
       }
       System.out.println("You have removed a book!");
    }
    /**
     * This function take name and ID of user to register the user.
     * @throws Error when inner function throws any error. 
     */
    private void registerNewUser()throws Error{
        /**
         * This object for taking input from user. 
         */
        Scanner input = new Scanner(System.in);
        
        System.out.println("Please enter the name  and the ID of the new user to register.");
        System.out.println("Please do not use Turkish character.");
        
        System.out.printf("User Name : ");
        setUserName(input.nextLine().toLowerCase());
        System.out.printf("User ID : ");
        setUserID(input.next().toLowerCase());
        setUserStatus("");
        String line = super.getIdOfUser()+","+getUserName()+","+getUserStatus();
        super.writeLine(line,FILEOFUSERS , true);
        System.out.println("You have added a user!");
    }
    /**
     * When program run for staff for the first time , this constructor will ask the staff password to use after that. 
     * @throws IOException when file processing is failed. 
     * 
     */
    public Staff() throws IOException{
        /*This try-catch part firstly look that "staff.csv" is exist or not in try part. İf it does
        not exist then ask the password and write this password to the file in catch part.*/
        try {
            /**
             * This object for taking input from user.
             */
            Scanner inputPassword = new Scanner(System.in);
            try( 
                /**
                  *This object for read "staff.csv"
                  */ 
                Scanner staffFile = new Scanner(new File(FILEOFSTAFF))) {
                passwordOfStaff = staffFile.nextLine().split(",")[1];
                System.out.printf("Enter Staff Password to continue : ");
                isStaff = passwordOfStaff.equals(inputPassword.nextLine());
            }
        } catch (FileNotFoundException ex) {
            /**
             * This object for writing the password to "staff.csv".
             */
            FileWriter fileOfStaff = new FileWriter(FILEOFSTAFF , true);
            /**
             * For take the password  from user.
             */
            Scanner input = new Scanner(System.in);
            System.out.printf("Please create a password for logging in as staff: ");
            passwordOfStaff = input.nextLine();
            fileOfStaff.write( "StaffPassword"+ "," + passwordOfStaff);
            fileOfStaff.write("\n");
            fileOfStaff.close();
        }
    }
    /**
     * Control the user of the system is staff or not.
     * @return True for staff , false for notStaff.
     */
    public boolean isStaff(){return isStaff;}
    /**
     * This function sets the name of book and the name of the author of the book.
     */
    @Override
    protected void setter(){
        /**
         * This object for taking input from user.
         */
        Scanner input = new Scanner(System.in);
        
        System.out.println("Please enter the name of the book and the name of Author of the book.");
        System.out.println("Please do not use Turkish character.");
        /*Asking for book name and author name.*/
        System.out.printf("Book Name : ");
        super.setBookName(input.nextLine().toLowerCase());
        System.out.printf("Author Name : ");
        super.setBookAuthor(input.nextLine().toLowerCase());        
    }
    /**
     * 
     * @param choice the user choice for adding book(1) , removing book(2) and registering user(3).
     * @throws Error when any error showed up throwing Error exception.
     */
    @Override
    public void run(int choice)throws Error{
        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                removeBook();
                break;
            case 3:
                registerNewUser();
                break;
            default:
                throw new Error("You made wrong choice for staff part!!");           
        }
    }

    @Override
    public String toString(){

    	return String.format("Staff password is : " , passwordOfStaff);
    }


}
