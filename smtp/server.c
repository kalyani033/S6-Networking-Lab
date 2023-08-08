#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#define port 8080
#define BUF_SIZE 256

int main() {
    

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1) {
        printf("Error creating socket\n");
        exit(1);
    }

    struct sockaddr_in server, client;
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port);

    if (bind(sockfd, (struct sockaddr *)&server, sizeof(server)) < 0) {
        printf("Error in bind()!\n");
        exit(1);
    }

    socklen_t client_len = sizeof(client);
    char str[BUF_SIZE], msg[BUF_SIZE];

    printf("Server waiting...\n");
    sleep(3);

    recvfrom(sockfd, str, BUF_SIZE, 0, (struct sockaddr *)&client, &client_len);
    printf("Got message from client: %s\n", str);

    strcpy(str, "220 127.0.0.1");
    sleep(10);
    sendto(sockfd, str, strlen(str), 0, (struct sockaddr *)&client, sizeof(client));
    sleep(3);

    recvfrom(sockfd, str, BUF_SIZE, 0, (struct sockaddr *)&client, &client_len);
    if (strncmp(str, "HELO", 4) != 0)
        printf("'HELO' expected from client....\n");
    printf("%s\n", str);

    strcpy(str, "250 ok");
    sendto(sockfd, str, strlen(str), 0, (struct sockaddr *)&client, sizeof(client));
    sleep(3);

    recvfrom(sockfd, str, BUF_SIZE, 0, (struct sockaddr *)&client, &client_len);
    if (strncmp(str, "MAIL FROM", 9) != 0)
        printf("MAIL FROM expected from client....\n");
    printf("%s\n", str);

    strcpy(str, "250 ok");
    sendto(sockfd, str, strlen(str), 0, (struct sockaddr *)&client, sizeof(client));
    sleep(3);

    recvfrom(sockfd, str, BUF_SIZE, 0, (struct sockaddr *)&client, &client_len);
    if (strncmp(str, "RCPT TO", 7) != 0)
        printf("RCPT TO expected from client....\n");
    printf("%s\n", str);

    strcpy(str, "250 ok");
    sendto(sockfd, str, strlen(str), 0, (struct sockaddr *)&client, sizeof(client));
    sleep(3);

    recvfrom(sockfd, str, BUF_SIZE, 0, (struct sockaddr *)&client, &client_len);
    if (strncmp(str, "DATA", 4) != 0)
        printf("DATA expected from client....\n");
    printf("%s\n", str);

    strcpy(str, "354 Go ahead");
    sendto(sockfd, str, strlen(str), 0, (struct sockaddr *)&client, sizeof(client));

    recvfrom(sockfd, msg, BUF_SIZE, 0, (struct sockaddr *)&client, &client_len);
    printf("Mail body received:\n%s\n", msg);

    recvfrom(sockfd, str, BUF_SIZE, 0, (struct sockaddr *)&client, &client_len);
    if (strncmp(str, "QUIT", 4) != 0)
        printf("QUIT expected from client....\n");
    printf("Sending quit...\n");

    strcpy(str, "221 OK");
    sendto(sockfd, str, strlen(str), 0, (struct sockaddr *)&client, sizeof(client));

    close(sockfd);
    return 0;
}
