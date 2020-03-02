#include "commonhead.h"

int main()
{
    if (SYSTEM == "Windows")
    {
        WORD versionWanted = MAKEWORD(2, 2);
        WSADATA wsaData;
        WSAStartup(versionWanted, &wsaData);
    }

    char *server_message;

    // Create server socket
    SOCKET server_socket, client_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == INVALID_SOCKET)
    {
        printf("Failed to create socket\n");
    }
    else
    {
        printf("Socket created successfully!\n");
    }

    // Define server address
    struct sockaddr_in server_address, client_address;
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_address.sin_port = htons(9002);

    // Bind the socket to our specified IP and port
    bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address));

    // Listen will listen to any incoming connections and can allow you to set
    // the maximum number of connections to listen to
    listen(server_socket, 5);
    printf("Awaiting connections on %d...\n", ntohs(server_address.sin_port));

    // When a connection is accepted we can get the client's socket for manipulation
    int c = sizeof(struct sockaddr_in);

    while ((client_socket = accept(server_socket, (struct sockaddr *)&client_address, &c)) != INVALID_SOCKET)
    {
        printf("Connection established\n");
        // Send the server_message string to the client at client_socket
        server_message = "Heya. I got your request, but now I gotta go.\n";
        send(client_socket, server_message, strlen(server_message), 0);
    }

    if (client_socket == INVALID_SOCKET)
    {
        printf("Accept failed with error code %d\n", WSAGetLastError());
        return 1;
    }

    // Close the socket after sending the message
    if (SYSTEM == "Windows")
    {
        closesocket(server_socket);
        WSACleanup();
    }
    else
    {
        close(server_socket);
    }

    return 0;
}