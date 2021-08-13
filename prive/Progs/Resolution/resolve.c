/**
 * Displays ipv4 and ipv6 addresses of domain names
 * given as command line parameters.
 * 
 * m billaud, 2020
 */

#define _XOPEN_SOURCE 700

#include <stdio.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

void print_addresses(char *hostname);

int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++) {
        print_addresses(argv[i]);
    }
    return 0;
}

void print_addresses(char *hostname)
{
    // get list of results
    struct addrinfo hints = {
        .ai_family = AF_UNSPEC,       // ipv4 or IPv6
        .ai_socktype = SOCK_STREAM
    };

    struct addrinfo *results;
    printf("%s\n", hostname);
    int  s = getaddrinfo(hostname, NULL, &hints, &results);
    if (s != 0) {
        printf ("\tinconnu\n");
        return;
    }
    // display results
     for (struct addrinfo *ptr = results; ptr != NULL; ptr = ptr->ai_next) {
        char * family_name = "unknown";
        void * addr = NULL;

        switch (ptr->ai_family ) {
        case AF_INET :
            family_name = "IPv4";
            addr = &(((struct sockaddr_in *)(ptr->ai_addr)) ->sin_addr);
            break;
        case AF_INET6 :
            family_name = "IPv6";
            addr = &(((struct sockaddr_in6 *)(ptr->ai_addr)) ->sin6_addr);
            break;
        }  
        // inet_ntop converts address to textual numeric form
        char ip_as_string[100];
        inet_ntop(ptr->ai_family, addr, ip_as_string, sizeof(ip_as_string));
        printf("\t%s: %s\n", family_name, ip_as_string);

    }
    freeaddrinfo(results);
}
