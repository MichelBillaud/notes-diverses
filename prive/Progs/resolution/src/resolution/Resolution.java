package resolution;

import java.net.InetAddress;
import java.net.Inet4Address;
import java.net.Inet6Address;

import java.net.UnknownHostException;

public class Resolution {

    public static void main(String[] args) {
        for (String domainname : args) {
            print_addresses(domainname);
        }
    }

    private static void print_addresses(String name) {
        System.out.println(name);
        try {
            for (InetAddress address : InetAddress.getAllByName(name)) {
                String family
                        = address instanceof Inet4Address ? "IPv4"
                                : address instanceof Inet6Address ? "IPv6"
                                        : "other";
                System.out.format("\t%s: %s\n", family, address.getHostAddress());
            }
        } catch (UnknownHostException ex) {
            System.out.format("\tnot found");
        }
    }
}
