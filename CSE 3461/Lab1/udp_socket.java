
//cse 3461 lab 1 socket programming
// author: patrick cheng

import java.io.File;
import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.util.Scanner;

public class udp_socket {

    public static void main(String[] args) {

        try {
            DatagramSocket ds = new DatagramSocket();
            byte buf[] = null;
            String next = null;
            byte data[];
            File file = new File("uuid");
            Scanner read = new Scanner(file);

            while (read.hasNextLine()) {
                next = read.nextLine();
                System.out.println(next);
            }
            data = next.getBytes();
            buf = next.getBytes();
            InetAddress address = InetAddress
                    .getByName("segmentationfault.coredumped.tech");
            DatagramPacket DpSend = new DatagramPacket(data, buf.length,
                    address, 54321);

            ds.send(DpSend);

            read.close();

            byte[] buffer = new byte[512];
            DatagramPacket income = new DatagramPacket(buffer, buffer.length);

            ds.receive(income);

            String incomeStr = new String(buffer, 0, income.getLength());
            System.out.println(incomeStr);

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

}
