
//cse 3461 lab 1 socket programming
// author: patrick cheng

import java.io.BufferedReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.Socket;

public class tcp_socket {

    public static void main(String[] args) {

        try {
            System.out.println("Connecting");
            Socket socket = new Socket("segmentationfault.coredumped.tech",
                    12345);
            String name = "cheng.1317";
            System.out.println("Connected");
            OutputStream out = socket.getOutputStream();
            out.write(name.getBytes());
            out.flush();

            InputStream in = socket.getInputStream();
            BufferedReader read = new BufferedReader(new InputStreamReader(in));
            String next;
            FileWriter uuid = new FileWriter("uuid");

            while ((next = read.readLine()) != null) {
                uuid.write(next);
                System.out.println(next);
            }

            socket.close();
            in.close();
            out.close();
            read.close();
            uuid.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}