import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.SocketException;

public class server {
    static ServerSocket ServerSocket;
    static DataInputStream dis;
    static DataOutputStream dos;

    public static void main(String[] args) throws SocketException{
        try {
            int a[] = {30,40,50,60,70,80,90,100};
            ServerSocket = new ServerSocket(8011);
            System.out.println("Waiting For Connection");
            Socket client = ServerSocket.accept();
            dis  = new DataInputStream(client.getInputStream());
            dos  = new DataOutputStream(client.getOutputStream());
            for (int i = 0; i < a.length; i++) {
                if (i==5) {
                    System.out.println("Acknowledgement Sent (Lost)");
                    java.lang.Thread.sleep(500);
                    
                }
                else{
                    System.out.println("Acknowledgement Sent for frame"+(i+1));
                    java.lang.Thread.sleep(500);
                }
            }
            System.out.println("Acknowledgement sent for frame 6");
            System.out.println("Number of packets sent are :"+a.length);
            int y = a.length;
            dos.write(y);
            dos.flush();
            for (int i = 0; i < a.length; i++) {
                dos.write(a[i]);
                dos.flush();
            }
            int k = dis.read();
            dos.write(a[k]);
            dos.flush();

        }catch (IOException e){
            System.out.println(e);
        }catch (InterruptedException e){
            System.out.println();
        }
        finally{
            try{
                dis.close();
                dos.close();
            }catch (IOException e){
                e.printStackTrace();
            }
        }
    }
}
