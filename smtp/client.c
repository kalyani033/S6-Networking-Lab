#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define BUF_SIZE 256

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <server_ip> <port>\n", argv[0]);
        exit(1);
    }

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        printf("Error creating socket\n");
        exit(1);
    }

    struct sockaddr_in server;
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(argv[1]);
    server.sin_port = htons(atoi(argv[2]));

    char buffer[BUF_SIZE];

    // Connect to the server
    strcpy(buffer, "HELO 127.0.0.1");
    sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&server, sizeof(server));
    recvfrom(sockfd, buffer, BUF_SIZE, 0, NULL, NULL);

    // Specify the sender's email address
    printf("Enter FROM address: ");
    scanf("%s", buffer);
    snprintf(buffer, BUF_SIZE, "MAIL FROM:%s", buffer);
    sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&server, sizeof(server));
    recvfrom(sockfd, buffer, BUF_SIZE, 0, NULL, NULL);

    // Specify the recipient's email address
    printf("Enter TO address: ");
    scanf("%s", buffer);
    snprintf(buffer, BUF_SIZE, "RCPT TO:%s", buffer);
    sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&server, sizeof(server));
    recvfrom(sockfd, buffer, BUF_SIZE, 0, NULL, NULL);

    // Start sending the email data
    printf("Enter mail body (terminate with $):\n");
    while (1) {
        char c = getchar();
        if (c == '$') {
            break;
        } else if (c == '\n' || c == '\0') {
            continue;
        } else {
            buffer[0] = c;
            sendto(sockfd, buffer, 1, 0, (struct sockaddr *)&server, sizeof(server));
        }
    }

    // Signal the end of email data
    strcpy(buffer, "$");
    sendto(sockfd, buffer, 1, 0, (struct sockaddr *)&server, sizeof(server));

    // Quit the session
    strcpy(buffer, "QUIT");
    sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&server, sizeof(server));
    recvfrom(sockfd, buffer, BUF_SIZE, 0, NULL, NULL);

    close(sockfd);
    return 0;
}
