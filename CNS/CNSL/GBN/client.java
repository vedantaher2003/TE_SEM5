import java.util.*;
import java.net.*;
import java.io.*;
import java.math.*;

public class client {

    public static void main(String[] args) throws IOException {

        InetAddress addr = InetAddress.getByName("Localhost");
        System.out.println(addr);

        Socket connection = new Socket(addr, 500);
        BufferedInputStream in = new BufferedInputStream(connection.getInputStream());
        DataOutputStream out = new DataOutputStream(connection.getOutputStream());
        Scanner scr = new Scanner(System.in);

        System.out.println("------Client------");
        System.out.println("Connect");
        System.out.println("Enter number of frames to be requested from the server");
        int c = scr.nextInt();

        out.write(c);
        out.flush();

        System.out.println("Enter the type of transmission (with error: (1) and without error: (0))");
        int choice = scr.nextInt();
        out.write(choice);

        int check = 0, i = 0, j = 0;

        if (choice == 0) {

            for (int j2 = 0; j2 < c; j2++) {
                i = in.read();
                System.out.println("Received frame number " + i);
                System.out.println("Sending acknowledgemeent for frame number " + i);
                out.write(i);
                out.flush();
            }
            out.flush();
        } else {
            for (int j2 = 0; j2 < c; j2++) {
                i = in.read();
                if (i == check) {
                    System.out.println("i: " + i + " check: " + check);
                    System.out.println("Received frame number " + i);
                    System.out.println("Sending acknowledgement for frame number " + i);
                    out.write(i);
                    ++check;
                } else {
                    --j;
                    System.out.println("Discarded frame number " + i);
                    System.out.println("Sending Negative Acknowledgement");
                    out.write(-1);
                }
                out.flush();
            }

        }

        in.close();
        out.close();
        System.out.println("Quitting...");

    }
}