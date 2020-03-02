#include "commonhead.h"
#include <string.h>
#include <ws2tcpip.h>

int main()
{
    if (SYSTEM == "Windows")
    {
        WORD versionWanted = MAKEWORD(2, 2);
        WSADATA wsaData;
        WSAStartup(versionWanted, &wsaData);
    }

    // Read and put the html page, index.html, into memory
    FILE *html_page = fopen("./index.html", "r");
    char html_string[1024];
    char http_header[2048] = "HTTP/1.1 200 OK\r\n"
                             "Content-Type: text/html; charset=UTF-8\r\n\r\n";
    fgets(html_string, sizeof(html_string), html_page);

    // Response header tells the client that the request was received successfully
    // We make the header large so that we can hold the html_string too
    strcat(http_header, html_string);

    SOCKET server_socket;
    struct sockaddr_in server_address;
    int addr_len = sizeof(server_address);
    int client_socket;

    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
    {
        printf("Failed to create server socket\n");
        return 1;
    }
    else
    {
        printf("Socket created.\n");
    }

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(8080);

    bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address));

    listen(server_socket, 3);

    // The last two parameters in accept are set to NULL since we don't need to save the client's address
    while (1)
    {
        if ((client_socket = accept(server_socket, (struct sockaddr *)&server_address, (socklen_t *)&addr_len)) < 0)
        {
            printf("Connection failed.\n");
            return 1;
        }

        printf("Connection established at %d\n", ntohs(server_address.sin_port));
        // Send the server_message string to the client at client_socket
        send(client_socket, http_header, strlen(http_header), 0);

        printf("Data sent to client\n");
        closesocket(client_socket);
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