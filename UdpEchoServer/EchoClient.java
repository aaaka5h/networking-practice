import java.io.*;
import java.net.*;

public class EchoClient {
    DatagramSocket socket;

    String ping(String hostname, int port, String msg) throws UnknownHostException, IOException {
        int bufferSize = 1024;

        InetAddress address = InetAddress.getByName(hostname);
        byte[] buf = msg.getBytes();
        DatagramPacket packetToSend = new DatagramPacket(buf, buf.length, address, port);
        socket.send(packetToSend);

        byte[] receiveBuf = new byte[bufferSize];
        DatagramPacket packetToReceive = new DatagramPacket(receiveBuf, receiveBuf.length);
        socket.receive(packetToReceive);

        byte[] receivedData = packetToReceive.getData();
        int receivedPacketLen = packetToReceive.getLength();
        return new String(receivedData, 0, receivedPacketLen);
    }

    public static void main(String[] args) throws IOException {
        new EchoClient().run(args);
    }

    private void run(String[] args) {
        if (args.length != 2) {
            System.err.println(
                    "Usage: java EchoClient <host name> <port number>");
            System.exit(1);
        }

        String hostName = args[0];
        int portNumber = Integer.parseInt(args[1]);

        try {
            socket = new DatagramSocket();
            for (int i = 0; i < 10; i++) {
                String ans = ping(hostName, portNumber, "hello " + i);
                System.out.println("Received: " + ans);
            }
        } catch (UnknownHostException e) {
            System.err.println("Don't know about host " + hostName);
            System.exit(1);
        } catch (IOException e) {
            System.err.println("Couldn't get I/O for the connection to " +
                    hostName);
            System.exit(1);
        }
    }
}



// To add a delay in the client:
// try {
//     Thread.sleep(1000);
// } catch (InterruptedException e) {
//     e.printStackTrace();
// }
