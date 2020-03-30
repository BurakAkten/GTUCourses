import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Scanner;
/**
 *
 * @author aktenburakk
 */
public abstract class LibrarySystem implements LibraryManagmentSys {
    /**
     * the name of the file that records books information.
     */
    protected final String FILEOFBOOKS = "books.csv";
    /**
     * the name of the file that records users information.
     */
    protected final String FILEOFUSERS = "users.csv";
    /**
     * user or staff choice. 
     */
    protected int choice;
    /**
     * holds the records of book file or user file.
     */
    protected ArrayList<String> fileArray;
    /**
     * the name of the book that holds the book records.
     */
    private String nameOfBook;
    /**
     * the name of author of the book that holds the book records.
     */
    private String nameOfAuthor;
    
    /**
     * the name of user.
     */
    private String nameOfUser;
    /**
     * the ID of user.
     */
    private String idOfUSer;
    /**
     * The user status that holds user's book that borrowed. 
     */
    private String userStatus;
    
    /**
     * This function for removing spaces from end of any string.
     * @param str the string that will be updated.
     * @return the updated string.
     */
    private String removeSpacesFromFile(String str){
        
        if(str.endsWith(" "))
            return removeSpacesFromFile(str.substring(0, str.length() - 1));
        else
            return str;
    }
    /**
     * In this constructor , the .csv files are created with column names.
     * @throws Error if error showed up when reading and writing book then thrown.
     */
    public LibrarySystem()throws Error{
        try{
            /** 
             * This object for writing to book file.
             */
            FileWriter outFile1 = new FileWriter(FILEOFBOOKS , true);
            /**
             * This object for writing to user file.
             */
            FileWriter outFile2 = new FileWriter(FILEOFUSERS , true);
            /**
             * This object for read to book file to control file empty or not.
             */
            Scanner bookfile = new Scanner(new File(FILEOFBOOKS));
            /**
             * This object for read to book file to control file empty or not.
             */
            Scanner userfile = new Scanner(new File(FILEOFUSERS));
            
            /*Controlling the files are empty or not. If they are then writing 
             the columns to the files.*/
            if(bookfile.hasNextLine()==false && userfile.hasNextLine()==false){
                outFile1.write("NameOfBook,NameOfAuthor");
                outFile1.write("\n");
                outFile2.write("User ID,User Name,Borrowed Book");
                outFile2.write("\n");
            }
            /*Then closing file.*/
            outFile1.close();
            outFile2.close();
            bookfile.close();
            userfile.close();
        }catch(IOException e){
            throw new Error("Error showed up when writing file!");
        }
    }
    /**
     * Setting userStatus.
     * @param status the status for setting.
     */
    public void setUserStatus(String status){userStatus = status;}
    /**
     * Setting nameOfUser.
     * @param userName represents the nameOfNewUSer
     */
    public void setUserName(String userName){
        this.nameOfUser = removeSpacesFromFile(userName);
    }
    /**
     * Setting userID.
     * @param userID represents the idOfNewUser
     */
    public void setUserID(String userID){
        idOfUSer = removeSpacesFromFile(userID); 
    }
    
    /**
     * Setting bookName.
     * @param bookName the name of the book
     */
    public void setBookName(String bookName){
        nameOfBook =  removeSpacesFromFile(bookName);
    }
    /**
     * Setting nameOfAuthor.
     * @param bookAuthor the name of the author of the book
     */
    public void setBookAuthor(String bookAuthor){
        nameOfAuthor = removeSpacesFromFile(bookAuthor);
    }
    /**
     * @return the userStatus
     */
    public String getUserStatus(){return userStatus;}
    /**
     * @return the name of the book
     */
    public String getBookName(){return nameOfBook; }
    /**
     * @return the name of the author of the book
     */
    public String getAuthorName(){return nameOfAuthor; }
    /**
     * @return the name of user
     */
    public String getUserName(){return nameOfUser;}
    /**
     * @return id of user.
     */
    public String getIdOfUser(){return idOfUSer;}
    
    /**
     * 
     * @param line the line for writing to file
     * @param fileName the name of the file.
     * @param append to append(true) the file or notappend(false).
     * @throws Error if any error showed up then throws Error.
     */
    protected void writeLine(String line , String fileName , boolean append) throws Error{
        try{
            /**
             * This object for writing to file.
             */
            FileWriter outFile = new FileWriter(fileName , append);
            outFile.write(line);
            outFile.write("\n");
            outFile.close();
        }catch(IOException e){
            throw new Error("Error showed up when writing file!");
        }  
    }
    /**
     * This function update the book and user file when borrowing and returning book.
     * @throws Error when any error showed up.
     */
    protected void updateBookInfo()throws Error{
        writeLine(fileArray.get(0) , FILEOFBOOKS , false);
        for(int i = 1 ; i < fileArray.size() ; ++i)
            writeLine(fileArray.get(i) , FILEOFBOOKS , true);
    }
    /**
     * This function update the book and user file when borrowing and returning book.
     * @throws Error when any error showed up.
     */
    protected void updateUserInfo()throws Error{
        if(readFiletoArray(FILEOFUSERS)==1){
            /**
             * This string object for being writing to file.
             */
            String line = getIdOfUser() +","+getUserName()+","+getUserStatus();
            /**
             * This variable holds the index of user if user in the file as user.
             */
            int whereUserFound = search(line);
            
            /*firstly removing the line then updating line and adding again.*/
            
            fileArray.remove(whereUserFound);
            
            line = getIdOfUser() +","+getUserName()+","+getUserStatus();
            /*adding updated line*/
            fileArray.add(whereUserFound , line);
            
            writeLine(fileArray.get(0) , FILEOFUSERS , false);
            for(int i = 1 ; i < fileArray.size() ; ++i)
                writeLine(fileArray.get(i) , FILEOFUSERS , true);
        }
    }
    /**
     * This function read a file to arraylist.
     * @param filename the file name of the file that reading into arraylist.
     * @return  1 when successful , -1 when file empty.(after first line)
     * @throws Error when any error showed up.
     */
    protected int readFiletoArray(String filename)throws Error{        
        /*Reading file into arraylist.*/
        fileArray = new ArrayList<String>();
        try {
            /**
             * This object for reading file.
             */
            Scanner input = new Scanner(new File(filename));
            //reading first line
            String firstLine = input.nextLine();
            
            //if file is empty retuen 1.
            if(!input.hasNextLine()) 
                return -1;
            else{
                fileArray.add(firstLine);
                while(input.hasNextLine())
                    fileArray.add(input.nextLine());
            }
        }
        catch (FileNotFoundException ex) {
            throw new Error("Error showed up when read the file!");
        }
        
        return 1;
    }
    /**
     * 
     * @param target the target to searching in from arraylist.
     * @return index if target is in arraylist otherwise -1.
     */
    protected int search(String target){
        /**
         * This array holds the target as splited(with ",")
         */
        String[] splitedTarget = target.split(",");
        /*Then seraching algorithm works.*/
        for(int i = 1 ; i < fileArray.size() ; ++i)
            if(target.equals(fileArray.get(i)))
               return i;
            else if(splitedTarget[0].equals(fileArray.get(i).split(",")[0]) &&
                    splitedTarget[1].equals(fileArray.get(i).split(",")[1]))
                return i;
       return -1;
    }
    /**
     * Abstract function will inherit.
     */
    protected abstract void setter();
    
    @Override
    public abstract void run(int choice);   
}
