import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.Scanner;

/*
    Operating Systems- Assignment 1
    Written by: Edxio Kraudy Mora (110006224)
    Date: Thursday May 27, 2021
 */

/**
 * This class is responsible for copying source files
 * to a destination files in sequential order.
 */
public class SequentialCopy {

    public static void main (String[] args) throws IOException {

        int sourceCount = 0;
        Scanner in = new Scanner(System.in);

        //Acquire how many source files will be used and accept input
        System.out.println("How many source files will be used (n): ");
        sourceCount = in.nextInt();

        //Array of String objects to keep track of file names
        String[] fileNames = new String[sourceCount];

        //Loop to acquire the names of the input files
        for (int x = 0; x < sourceCount; x++) {
            System.out.println("Enter the name of the file to be read: ");
            fileNames[x] = in.next();

            File input = new File(fileNames[x]);

            if (!input.exists()) {
                System.out.println("This source file does not exist, exiting...");
                System.exit(0);
            }
        }

        //Acquire name of destination file and accept input
        System.out.println("Enter the name of the output/destination file: ");
        String destinationFile = in.next();

        try {

            //Create File object for destination file
            File output = new File(destinationFile);

            //If output file exists then abort, else create file
            if (output.createNewFile()) {
                System.out.println("The file " + destinationFile + " has been created!");
            }

            else {
                System.out.println("This output file already exists, exiting...");
                System.exit(1);
            }

            FileOutputStream outputStream = new FileOutputStream(destinationFile);

            for (int x = 0; x < sourceCount; x++) {

                int read;
                byte[] bytes = new byte[1024];

                FileInputStream inputStream = new FileInputStream(fileNames[x]);
                System.out.println("Now reading " + fileNames[x]);

                //Read from inout file, write to output file
                while ((read = inputStream.read(bytes)) > 0) {
                    outputStream.write(bytes, 0, read);
                    System.out.println("Now writing " + fileNames[x] + " to " + destinationFile);
                }

                inputStream.close();

            }

            outputStream.close();

        }

        catch (IOException e) {
            e.printStackTrace();
        }

    }

}
