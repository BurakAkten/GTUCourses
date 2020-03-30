import java.lang.Error;
import java.util.Scanner;
/**
 *
 * @author Burak Akten
 */
public class Users extends LibrarySystem{
    
    /**
     * By using this function user can borrow a book.
     */
    private void borrowBook(){
        /**
         *This variable holds the index of the user if user exists.
         */
        int userIndex = checkUser();
        /**
         * if user has already has book this variable's value will be true.
         */
        boolean isUserHasBook = (super.fileArray.get(userIndex).split(",").length == 3);
        
        /*
         * if user has book, he/she can not borrow a book.
         */
        if(isUserHasBook){
            System.out.println("Sorry! You've already borrowed a book!");
            System.out.println("You firstly have to return the book.!");
            return;
        }
        /*
         * Controlling  book file empty or not.
         */
        if(super.readFiletoArray(FILEOFBOOKS) == -1){
            System.out.println("Sorry! There is no book in library!");
            return;
        }
        /*
         * By using this function name of book and author of book can be set..
         */
        setter();    
        /*
         * Controlling the book in the file(library) or not. 
         * If book exists then it can be borrowed.
         */
        int foundwhere = search(super.getBookName()+","+super.getAuthorName()); 
       
        if( foundwhere == -1)
            System.out.println("Sorry! This book is't in the library rigth now!");
        else{
             super.fileArray.remove(foundwhere);          
             super.updateBookInfo();
             setUserStatus(getBookName()+"."+getAuthorName());
             super.updateUserInfo();
        }
        System.out.println("You have borrowed a book!");
    }
    /**
     * By this function user can return the book that borrowed. 
     */
    private void returnBook(){      
        /**
         * This variable holds the index of the user if user exists.
         */
        int userIndex = checkUser();
        /**
         * if user has already has book this variable's value will be true.
         */
        boolean isUserHasBook = (super.fileArray.get(userIndex).split(",").length == 3);
        
        /*
         * if user did not borrowed a book he/she can not return a book , this condition controls it.
         */
        if(!isUserHasBook){
            System.out.println("You've not borrow a book!\nFirstly you've get to borrow one.");
            return;
        }
        /**
         * This variable holds the name and author of book like that "bookname.bookauthor".
         */
        String bookThatUserHave = super.fileArray.get(userIndex).split(",")[2];
        super.readFiletoArray(FILEOFBOOKS);
        /*
         * Book name and author name is setting here.
         */
        setter();
        
        /*
         * Controlling the information of the returned and borrowed book, if they're same then returning happend. 
         */
        if(bookThatUserHave.equals(super.getBookName()+"."+super.getAuthorName()))
        {   
            /**
             *Hold the name  and author name of the returning book to add to in the books file again. 
             */
            String book = super.getBookName() + "," + super.getAuthorName();
            super.writeLine(book,FILEOFBOOKS , true);
            setUserStatus("");
            super.updateUserInfo();
        }
        else
            System.out.println("The book you've taken and you've returned is'nt same!");
        System.out.println("You have returned a book!");
    }
    /**
     * 
     * @return index of user if user name and id number is in the user file otherwise returns -1. 
     */
    public int checkUser(){
        /*
         * Firstly, users put on the array from file , then user checked and returning. 
         */
        super.readFiletoArray(FILEOFUSERS);
        return super.search(super.getIdOfUser()+","+super.getUserName());
    }
    
    /**
     *
     *This function sets the name of book and the name of the author of the book.
     */
    @Override
    protected void setter(){
       /**
        * This object for taking input from user.
        */
       Scanner input = new Scanner(System.in);       
       
       System.out.println("Please enter the name of the book and the name of Author of the book.");
       System.out.println("Please do not use Turkish character.");
       System.out.printf("Book Name : ");
       super.setBookName(input.nextLine().toLowerCase());
       System.out.printf("Author Name : ");
       super.setBookAuthor(input.nextLine().toLowerCase()); 
    }
    
    /**
     *
     * @param choice the user choice for returning(2) and borrowing(1).
     * @throws Error when any error showed up throwing Error exception.
     */
    @Override
    public void run(int choice)throws Error{
        if(choice > 2 && choice < 1)
            throw new Error("Wrong choice for user!!");
        switch (choice) {
            case 1:
                borrowBook();
                break;
            case 2:
                returnBook();
                break;
            default:
                throw new Error("You made wrong choice for user part!");
        }
    }

    @Override
    public String toString(){

    	return String.format("The name of user : %s\n The ID of user : %s.\n" ,super.getUserName() , super.getIdOfUser());
    }
}
