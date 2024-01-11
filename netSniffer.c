#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <winsock2.h>

int main(int argc, char *argv[]) {
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (result != 0) {
        printf("Winsock initialization failed with error: %d\n", result);
        return 1;
    }

    // Check for correct number of arguments
    if (argc != 4) {
        printf("Usage: %s <IP address> <Start Port> <End Port>\n", argv[0]);
        WSACleanup();
        return 1;
    }

    char *ipAddress = argv[1];
    int startPort = atoi(argv[2]);
    int endPort = atoi(argv[3]);

    // Loop through the range of ports
    for (int port = startPort; port <= endPort; port++) {
        // Create socket
        SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock == INVALID_SOCKET) {
            printf("Could not create socket : %d\n", WSAGetLastError());
            continue;
        }

        // Set up the sockaddr_in structure
        struct sockaddr_in server;
        server.sin_addr.s_addr = inet_addr(ipAddress);
        server.sin_family = AF_INET;
        server.sin_port = htons(port);

        // Connect to the port
        if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
            printf("Port %d: Closed or filtered\n", port);
        } else {
            printf("Port %d: Open\n", port);
            closesocket(sock);
        }
    }

    WSACleanup();
    return 0;
}
