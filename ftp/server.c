#include <stdio.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    FILE *fp;
    int sd, newsd, ser, n, a, cli, pid, bd, port, clilen;
    char name[100], fname[100], rcv[100], fileread[100];
    struct sockaddr_in servaddr, cliaddr;

    printf("Enter the port address: ");
    scanf("%d", &port);

    sd = socket(AF_INET, SOCK_STREAM, 0);
    if (sd < 0) {
        printf("Can't create socket\n");
        exit(1);
    } else
        printf("Socket is created\n");

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port);

    a = sizeof(servaddr);
    bd = bind(sd, (struct sockaddr *)&servaddr, a);
    if (bd < 0) {
        printf("Can't bind\n");
        exit(1);
    } else
        printf("Binded\n");

    listen(sd, 5);
    clilen = sizeof(cliaddr);
    newsd = accept(sd, (struct sockaddr *)&cliaddr, &clilen);
    if (newsd < 0) {
        printf("Can't accept\n");
        exit(1);
    } else
        printf("Accepted\n");

    n = recv(newsd, rcv, 100, 0);
    rcv[n] = '\0';
    fp = fopen(rcv, "r");
    if (fp == NULL) {
        send(newsd, "error", sizeof("error"), 0);
        close(newsd);
    } else {
        while (fgets(fileread, sizeof(fileread), fp)) {
            if (send(newsd, fileread, strlen(fileread), 0) < 0) {
                printf("Can't send file contents\n");
                break;
            }
        }

        // When the file pointer reaches the end of the file, send "completed" message
        // to the accepted client connection using newsd.
        send(newsd, "completed", sizeof("completed"), 0);
        fclose(fp);
    }

    return 0;
}
