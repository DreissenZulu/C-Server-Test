# C Server Test
Test setup with live TCP server and client. The test was designed for use in a Windows environment, but (hopefully :pray:) should work on Linux and Mac environments too.

# Requirements
C Compiler (GNU C Compiler, MinGW, etc.)
Terminal (Command Line Interface, Powershell, etc.)

# Usage
This is a simple test consisting of a TCP server and client designed to interact with each other. The socket address has been configured to the localhost IP and is running on port 9002.
1. Compile tcp_server.c and tcp_client.c
2. In the terminal, execute the compiled tcp_server
3. In a separate terminal, execute the compiled tcp_client
4. A successful response should show "Connection established" in the server terminal, and the string "Heya. I got your request, but now I gotta go." in the client terminal.
5. tcp_server will remain open after successfully completing the client's connection request. Close the server with Ctrl+C
