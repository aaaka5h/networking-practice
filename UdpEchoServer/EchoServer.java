import java.net.*;
import java.io.*;

public class EchoServer {
    DatagramSocket socket;

    void echo() throws IOException {
        byte[] buf = new byte[256];
        DatagramPacket packet = new DatagramPacket(buf, buf.length);
        socket.receive(packet);

        // Uncomment for verbose server
        // System.out.println("Received from client: " + new String(buf, 0, packet.getLength()));
        
        InetAddress address = packet.getAddress();
        int port = packet.getPort();
        int length = packet.getLength();
        packet = new DatagramPacket(buf, length, address, port);
        socket.send(packet);
    }

    public static void main(String[] args) throws IOException {
        new EchoServer().run(args);
    }

    private void run(String[] args) {

        if (args.length != 1) {
            System.err.println("Usage: java EchoServer <port number>");
            System.exit(1);
        }

        int portNumber = Integer.parseInt(args[0]);

        try {
            socket = new DatagramSocket(portNumber);
            while (true) {
                echo();
            }
        } catch (IOException e) {
            System.out.println("Exception caught on port " + portNumber);
            System.out.println(e.getMessage());
        }
    }
}
