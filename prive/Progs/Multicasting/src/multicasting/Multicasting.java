package multicasting;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.InetAddress;
import java.net.MulticastSocket;

public class Multicasting {

    public static void main(String[] args) throws IOException {
        if (args.length == 0) {
            System.out.println("args : -s mcast-addr port message"
                    + " ou  -r mcast-addr port");
            System.exit(0);
        }
        switch (args[0]) {
            case "-s":
                envoyeur(args);
                break;
            case "-r":
                recepteur(args);
                break;
        }
        System.out.println("- Done");
    }

    private static void envoyeur(String[] args) throws IOException {
        if (args.length != 4) {
            System.out.println("envoyeur: mauvais nombre d'arguments");
        }
        String groupe = args[1];
        int port = Integer.parseInt(args[2]);
        String message = args[3];
        System.out.println("Sending");

        try (MulticastSocket socket = new MulticastSocket()) {
            byte[] contenu = message.getBytes();
            System.out.format("sending %d bytes\n", contenu.length);
            
            InetAddress adresse = InetAddress.getByName(groupe);
            DatagramPacket packet = new DatagramPacket(contenu, contenu.length, adresse, port);
            socket.send(packet);
            System.out.println("Sent");
        }
        System.out.println("Closed");
    }

    private static void recepteur(String[] args) throws IOException {
        if (args.length != 3) {
            System.out.println("récepteur: mauvais nombre d'arguments");
        }
        String groupe = args[1];
        int port = Integer.parseInt(args[2]);

        InetAddress adresse = InetAddress.getByName(groupe);

        try (MulticastSocket socket = new MulticastSocket(port)) {
            socket.joinGroup(adresse);
            while (true) {
                byte buffer[] = new byte[1000];
                DatagramPacket packet = new DatagramPacket(buffer, buffer.length);
                socket.receive(packet);
                System.out.format("packet received length %d...", packet.getLength());
                String message = new String(buffer, 0, packet.getLength());
                System.out.format("-> '%s'\n", message);
                System.out.format("l = %d\n", message.length());
                if (message.equals("stop")) {
                    System.out.println("stopping");
                    break;
                }
            }
            System.out.println("closing");
        }
    }
}
