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

    SOCKET server_socket;
    struct sockaddr_in server_address;
    int addr_len = sizeof(server_address);
    int client_socket;
    long valread;

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
    printf("Awaiting connections on port %d...\n", ntohs(server_address.sin_port));

    // The last two parameters in accept are set to NULL since we don't need to save the client's address
    while (1)
    {
        if ((client_socket = accept(server_socket, (struct sockaddr *)&server_address, (socklen_t *)&addr_len)) < 0)
        {
            printf("Connection failed.\n");
            return 1;
        }

        printf("Connection established at %d\n", ntohs(server_address.sin_port));
        char buffer[2000] = {0};
        valread = recv(client_socket, buffer, 2000, 0);

        if (memcmp(buffer, "GET", 3) == 0)
        {
            char data_string[600] = {0};
            char http_header[2048] = "HTTP/1.1 200 OK\r\n";
            if (strstr(buffer, "text/css") != NULL)
            {
                printf("Requesting .css file!\n");
                FILE *css_style = fopen("./assets/style.css", "r");
                strcat(http_header, "Content-Type: text/css;\r\n\r\n");
                fgets(data_string, sizeof(data_string), css_style);

                strcat(http_header, data_string);
            }
            else if (strstr(buffer, "text/html") != NULL)
            {
                printf("Requesting .html file!\n");
                // Read and put the html page, index.html, into memory
                FILE *html_page = fopen("./index.html", "r");
                strcat(http_header, "Content-Type: text/html; charset: UTF-8\r\n\r\n");
                fgets(data_string, sizeof(data_string), html_page);

                // Response header tells the client that the request was received successfully
                // We make the header large so that we can hold the html_string too
                strcat(http_header, data_string);
            }
            else
            {
                printf("No compatible file requested...");
            }
            // Send the server_message string to the client at client_socket
            send(client_socket, http_header, strlen(http_header), 0);
            printf("Data sent to client\n");
        }

        shutdown(client_socket, SD_SEND);
    }

    // Close the server socket if the loop ever exits
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