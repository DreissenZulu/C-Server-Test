// We want a flow of socket() -> connect() -> recv() for the client application
#include "commonhead.h"

int main()
{
    if (SYSTEM == "Windows")
    {
        WORD versionWanted = MAKEWORD(2, 2);
        WSADATA wsaData;
        WSAStartup(versionWanted, &wsaData);
    }

    // Create a socket
    SOCKET network_socket;
    // SOCK_STREAM means we'll be using TCP. 0 means we're using the default protocol
    network_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (network_socket == INVALID_SOCKET)
    {
        printf("Failed to create socket\n");
    }
    else
    {
        printf("Socket successfully created!\n");
    }

    // Specify an address for the socket
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_address.sin_port = htons(9002);
    // server_address.sin_addr.s_addr = INADDR_ANY;
    // server_address.sin_port = htons(8080); // htons converts integer to appropriate data format to read the port

    // connect returns an integer that tells us if the connection was successful or not
    // 0 = OK, -1 = some kind of error
    if (connect(network_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
    {
        printf("Failed to establish connection to the remote socket.\n\n");
        return 1;
    }

    printf("Connection established at port %d\n", ntohs(server_address.sin_port));
    // We send or receive data on establishing a successful connection

    char message[32] = "GET / HTTP/1.1\r\n\r\n";
    send(network_socket, message, strlen(message), 0);

    char server_response[256];
    int recv_size;
    recv_size = recv(network_socket, server_response, sizeof(server_response), 0);

    // After receiving data, insert a terminating character and print out the response...
    server_response[recv_size] = '\0';
    printf("Server responded with the following data:\n%s\n", server_response);

    // and close connection to server as there's no need to keep it open after data received
    if (SYSTEM == "Windows")
    {
        closesocket(network_socket);
        WSACleanup();
    }
    else
    {
        close(network_socket);
    }

    return 0;
}