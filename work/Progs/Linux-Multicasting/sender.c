#define _XOPEN_SOURCE 700

#include <stdio.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

int main(int argc, char *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "usage: %s addr port", argv[0]);
    }
    char *node = argv[1];
    char *service = argv[2];
    // récupérer l'adresse
    struct addrinfo *first_addr;
    struct addrinfo hints = {
        .ai_flags = AI_ADDRCONFIG,
        .ai_family = AF_UNSPEC,
        .ai_socktype = SOCK_DGRAM,

    };
    int r = getaddrinfo(node, service, &hints,  &first_addr);
    if (r != 0) {
        perror("getaddrinfo");
    }
    int s = -1;
    for (struct addrinfo *p = first_addr; p != NULL; p = p->ai_next) {

        s = socket(p->ai_family, p->ai_socktype, 0);
        if (s != -1) {
            char hostname[256];
            char service[256];
            getnameinfo(p->ai_addr, p->ai_addrlen,      // adresse
                        hostname, sizeof(hostname),
                        service, sizeof(service),                    // tampon port
                        NI_NUMERICHOST | NI_NUMERICSERV) ;
            printf("ADDRESS = %s SERVICE = %s \n", hostname, service) ;
            setsockopt(s, IPPROTO_IP)
            break;
        }
    }

    freeaddrinfo(first_addr);
    close(s);
}