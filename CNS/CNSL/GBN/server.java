import java.net.*;
import java.io.*;
import java.util.*;

public class server {
    public static void main(String[] args) throws IOException {
        System.out.println("-------Server-------");
        System.out.println("Waiting For Connection...");
        InetAddress addr = InetAddress.getByName("Localhost");
        ServerSocket ss = new ServerSocket(500);

        Socket client = new Socket();
        client = ss.accept();

        BufferedInputStream in = new BufferedInputStream(client.getInputStream());
        DataOutputStream out = new DataOutputStream(client.getOutputStream());

        System.out.println("Received Request For Sending Frames");
        int p = in.read();

        boolean f[] = new boolean[p];
        int pc = in.read(); // choice error or non-error
        System.out.println("Sending...");

        if (pc == 0) {

            for (int i = 0; i < p; i++) {
                System.out.println("Sending Frame Number :" + i);
                out.write(i);
                out.flush();
                System.out.println("Waiting for acknowledgement");
                try {
                    Thread.sleep(7000);
                } catch (Exception e) {
                }

                int a = in.read();
                System.out.println("Received acknowledgement for frame " + i + " as " + a);
            }
            out.flush();
        } else {
            for (int i = 0; i < p; i++) {
                if (i == 2) {
                    System.out.println("Sending frame number " + i);
                } else {
                    System.out.println("Sending frame number " + i);
                    out.write(i);
                    out.flush();
                    System.out.println("Waiting for acknowledgement");
                    try {
                        Thread.sleep(4000);
                    } catch (Exception e) {
                    }

                    int a = in.read();

                    if (a != 255) {
                        System.out.println("Received acknowledgement for frame number " + i + " as " + a);
                        f[i] = true;

                    }
                }
            }

            for (int i = 0; i < p; i++) {
                if (f[i] == false) {
                    System.out.println("Resending Frame " + i);
                    out.write(i);
                    out.flush();
                    System.out.println("Waiting for acknowledgement");
                    try {
                        Thread.sleep(5000);
                    } catch (Exception e) {
                    }

                    int b = in.read();
                    System.out.println("Received acknowledgement for frame " + i + " as " + b);
                    f[i] = true;
                }
            }
            out.flush();
        }
        in.close();
        out.close();
        System.out.println("Quitting...");
    }
}
